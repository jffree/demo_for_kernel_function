#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/netlink.h>
#include <errno.h>
#include "netlink_demo.h"


int main(int argc, char *argv[]){

	struct sockaddr_nl src_addr, dst_addr;
	struct msghdr msg;
	struct nlmsghdr *nlhdr;
	struct iovec iov;
	int sock_fd, retval;
	int state_msg = 0;

	/* 填充目的地址结构 */
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid();        /*A 源端地址，以进程的ID号标识 */
	src_addr.nl_groups = 0;            /* 单播 */

	sock_fd = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_TEST);  /* 建立套接字 */
	if(0 > sock_fd) {
		printf("error getting socket: %s\n", strerror(errno));
		return -1;
	}

	retval = bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));  /* 绑定套接字与源地址 */
	if(0 > retval){
		printf("bind failed: %s", strerror(errno));
		close(sock_fd);
		return -1;
	}

    /* 设定目的地址 */
	memset(&dst_addr, 0, sizeof(dst_addr));
	dst_addr.nl_family = AF_NETLINK;
	dst_addr.nl_pid = 0;                      /*B 目的地址，以进程的ID号标识 */
	dst_addr.nl_groups = 0;                       /* 单播 */

    /* 填充消息头 */
	nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(TEST_DATA_LEN));    /* 为netlink消息头分配空间 */
	memset(nlhdr, 0, NLMSG_SPACE(TEST_DATA_LEN));
	nlhdr->nlmsg_len = NLMSG_LENGTH(TEST_DATA_LEN);   /* 消息载荷（加上消息头） */
	nlhdr->nlmsg_flags = NLM_F_REQUEST;    /* 设定消息为请求消息 */
	nlhdr->nlmsg_pid = getpid();    /*C 当前套接字所绑定的ID号（此处为本进程的PID），与你在上面监听的pid一致 */
	nlhdr->nlmsg_seq = 0;
	nlhdr->nlmsg_type = NLMSG_GETECHO;
	strcpy(NLMSG_DATA(nlhdr), TEST_DATA);   /* 填充netlink消息实际载荷（payload） */

	iov.iov_base = (void *)nlhdr;
	iov.iov_len = nlhdr->nlmsg_len;

	/* 填充数据消息结构 */
	memset(&msg, 0, sizeof(msg));
	msg.msg_name = (void *)&(dst_addr);
	msg.msg_namelen = sizeof(dst_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	printf("=======> send message <=======\n");
	state_msg = sendmsg (sock_fd, &msg, 0); 	/* 发送netlink消息 */
	if(state_msg < 0 ){
		printf("error sending message: %s\n", strerror(errno));
	}

	printf("=======> receiving message <=======\n");
	memset(nlhdr, 0 , NLMSG_SPACE(TEST_DATA_LEN));
	int state_recv = recvmsg(sock_fd, &msg, 0); /* 接收消息 */
	if(0 > state_recv){
		printf("receive message error!\n");
        close(sock_fd);
        return -1;
	}
	if (nlhdr->nlmsg_type == NLMSG_SETECHO){
		printf("Received message: %s\n", (char *)NLMSG_DATA(nlhdr));
	}

	close(sock_fd);
	return 0;
}
