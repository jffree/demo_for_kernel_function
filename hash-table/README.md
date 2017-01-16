#### 哈希表的简单使用

* 通过 hash 算法计算存储位置和进行查找

* 通过 hash list 来解决哈希冲突

#### demo 使用

```
make
sudo insmod hash_kern
dmesg
sudo rmmod hash_kern
dmesg
```

#### 参考

[linux 内核 hash table 的使用](http://yupeng0921.blogspot.com/2010/10/linux-hash-table.html?showComment=1350877062473#c3513363701255844366)

[Linux 内核 hlist 详解 ](http://blog.csdn.net/hs794502825/article/details/24597773)

[关于散列表的通俗易懂的一些列文章](http://www.nowamagic.net/academy/detail/3008010)

#### 其他

* 我的文章

[ kernel 中的 hash list  ](https://jffree.github.io/2017/01/08/kernel-%E4%B8%AD%E7%9A%84-hash-list/)

##### 二级指针的使用

* 若想改变指针的内容，则只需要使用一级指针

* 若想改变指针的指向，则需使用二级指针

```
#include "stdio.h"
#include "stdlib.h"

#define ERROR    -1
#define OK        1

typedef struct node
{
    int data;
    struct node *next;   
}Node,*LinkList;

/*构造一个空表*/
void Init_LinkList(LinkList *Head_pointer)
{
    *Head_pointer=NULL;    /*指针Head_pointer为二重指针，*Head_pointer=NULL表示结点为空*/   
}

void Init_LinkList2(Node *Head_pointer)
{
	printf("%d\n", Head_pointer);
    Head_pointer=NULL;    
	printf("%d\n", Head_pointer);
}

int main()
{
	LinkList test;
	printf("%d\n", test);
	Init_LinkList(&test);
	printf("%d\n", test);

	Node test1;
	printf("%d\n", &test1);
	Init_LinkList2(&test1);
	printf("%d\n", &test1);

	return 0;
}
```
