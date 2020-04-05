//
//  main.c
//  003_LInkedStorage
//
//  Created by 孔雨露 on 2020/4/5.
//  Copyright © 2020 Apple. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define ERROR 0
#define TRUE 0
#define FALSE 0
#define OK 1

#define MAXSIZE 20

typedef int KStatus;
typedef int KElementType;

//定义结点
typedef struct KNodeInfo{
    KElementType data;
    struct KNodeInfo *next;
}Node;

typedef struct KNodeInfo *KLinkList;


//1. 初始化单链表
KStatus initList(KLinkList *L) {
    
    //生成头结点，并使用L指向此头结点
    *L = (KLinkList)malloc(sizeof(Node));
    //如果分配空间失败，直接退出
    if(*L == NULL) return ERROR;
    //将头结点的指针域置为空
    (*L)->next = NULL;
    
    return OK;
}

//2. 单链表插入
//初始条件:顺序线性表L已存在,1≤i≤ListLength(L);
//操作结果：在L中第i个位置之后插入新的数据元素e，L的长度加1;
KStatus insertElement(KLinkList *L, int i, KElementType e) {
    
    int j = 1;
    KLinkList p, s;
    p = *L;
    
    //寻找第i-1个结点
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    //判断第i个元素是否存在
    if(!p || j > i) return ERROR;
    
    //生成新结点s
    s = (KLinkList)malloc(sizeof(Node));
    //将e赋值给s的数值域
    s->data = e;
    //将p的后继结点赋值给s的后继
    s->next = p->next;
    //将s赋值给p的后继
    p->next = s;
    
    return OK;
}

//3. 单链表取值
//初始条件: 顺序线性表L已存在,1≤i≤ListLength(L);
//操作结果：用e返回L中第i个数据元素的值
KStatus getElement(KLinkList L, int i, KElementType *e) {
    int j = 1;
    //将结点p,指向链表L的第一个结点
    KLinkList p = L->next;
    
    //查找结点,p不为空,且计算j不等于i,则循环继续
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    //如果p为空或者j>i,则 返回error
    if(!p || j > i) return ERROR;
    
    *e = p->data;
    
    return OK;
}

//4. 单链表删除元素
//初始条件：顺序线性表L已存在，1≤i≤ListLength(L)
//操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1
KStatus deleteElement(KLinkList *L, int i, KElementType *e) {
    
    int j = 1;
    KLinkList p,q;
    p = (*L)->next;
    
    //查找第i-1个结点，p指向该结点
    while (p->next && j < (i-1)) {
        p = p->next;
        ++j;
    }
    
    //当i>n 或者 i<i 时，删除位置不合理
    if (!(p->next) || (j>i-1)) return ERROR;
    
    //q指向要删除的结点
    q = p->next;
    //将q的后继赋值给p的后继
    p->next = q->next;
    //将q结点中的数据赋值给e
    *e = q->data;
    //释放内存
    free(q);
    
    return OK;
}

//5. 遍历单链表
//初始条件：顺序线性表L已存在
//操作结果：依次对L的每个数据元素输出
KStatus traverseList(KLinkList L) {
    KLinkList p = L->next;
    while (p) {
        printf("%d\n",p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

//6. 清空单链表
//初始条件：顺序线性表L已存在。操作结果：将L重置为空表
KStatus clearList(KLinkList *L) {
    
    KLinkList p, q;
    //指向第一个结点
    p = (*L)->next;
    while (p) {
        //遍历删除每个结点，并释放内存
        q = p->next;
        free(p);
        p = q;
    }
    //头结点指针域赋值为空
    (*L)->next = NULL;
    
    return OK;
}

//7. 创建单链表：头插入法
//随机产生n个元素值,建立带表头结点的单链线性表L(前插法)
void createListByHeadInsert(KLinkList *L, int n) {
    KLinkList p;
    //建立1个带头结点的单链表
    *L = (KLinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    
    //循环前插入随机数据
    for (int i = 0; i < n; i++) {
        //生成新结点
        p = (KLinkList)malloc(sizeof(Node));
        //i赋值给新结点
        p->data = i;
        
        //将结点p插入到头结点之后
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

//8. 创建单链表：尾部插入法
//随机产生n个元素值,建立带表头结点的单链线性表L(后插法)
void createListByTailInsert(KLinkList *L, int n) {
    
    KLinkList p, r;
    
    //建立1个带头结点的单链表
    *L = (KLinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    
    //让r指针指向尾部结点
    r = *L;
    
    //循环创建链表结点，尾部插入
    for (int i = 0; i < n; i++) {
        //生成新结点
        p = (Node *) malloc(sizeof(Node));
        //赋值随机数i
        p->data = i;
        
        //尾部插入新结点
        //将表尾终端结点的指针指向新结点
        r->next = p;
        //将当前的新结点定义为表尾终端结点
        r = p;
    }
    
    //将尾部指针next=NULL
    r->next = NULL;
    
}

//9. 单元测试
void test() {
        KStatus iStatus;
        KLinkList L;
        KElementType e;
        
        //2.1 单链表初始化
        iStatus = initList(&L);
        printf("L 是否初始化成功?(0:失败,1:成功) %d\n",iStatus);
        
        //2.2 单链表插入数据
        for(int j = 1;j<=10;j++)
        {
            iStatus = insertElement(&L, 1, j);
        }
        printf("L 插入后\n");
        traverseList(L);
        
        //2.3 单链表获取元素
        getElement(L,5,&e);
        printf("第5个元素的值为：%d\n",e);
        
        //2.4 删除第5个元素
        iStatus = deleteElement(&L, 5, &e);
        printf("删除第5个元素值为:%d\n",e);
        traverseList(L);
        
        //3.1 前插法整理创建链表L
        iStatus = clearList(&L);
        createListByHeadInsert(&L, 20);
        printf("整理创建L的元素(前插法):\n");
        traverseList(L);
        
        //3.2 后插法整理创建链表L
        iStatus = clearList(&L);
        createListByTailInsert(&L, 20);
        printf("整理创建L的元素(后插法):\n");
        traverseList(L);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    test();
    return 0;
}
