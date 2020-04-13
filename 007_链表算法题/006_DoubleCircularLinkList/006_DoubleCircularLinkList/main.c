//
//  main.c
//  006_DoubleCircularLinkList
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
#define TRUE 1
#define FALSE 0
#define OK 1

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int KStatus;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int KElementType;/* KElementType类型根据实际情况而定，这里假设为int */

//定义结点
typedef struct KNode{
    KElementType data;
    struct KNode *prior;
    struct KNode *next;
}KNode;

typedef struct KNode * LinkList;


//6.1 双向循环链表初始化
KStatus creatLinkList(LinkList *L){
    
    *L = (LinkList)malloc(sizeof(KNode));
    if (*L == NULL) {
        return ERROR;
    }
    
    (*L)->next = (*L);
    (*L)->prior = (*L);
    
    //新增数据
    LinkList p = *L;
    for(int i=0; i < 10;i++){
        
        //1.创建1个临时的结点
        LinkList temp = (LinkList)malloc(sizeof(KNode));
        temp->data = i;
        
        //2.为新增的结点建立双向链表关系
        //① temp 是p的后继
        p->next = temp;
        //② temp 的前驱是p
        temp->prior = p;
        //③ temp的后继是*L
        temp->next = (*L);
        //④ p 的前驱是新建的temp
        p->prior = temp;
        //⑤ p 要记录最后的结点的位置,方便下一次插入
        p = p->next;
        
    }
    
    return OK;
   
}

//6.2 双向循环链表插入元素
/*当插入位置超过链表长度则插入到链表末尾*/
KStatus LinkListInsert(LinkList *L, int index, KElementType e){
   
    //1. 创建指针p,指向双向链表头
    LinkList p = (*L);
    int i = 1;
    
    //2.双向循环链表为空,则返回error
    if(*L == NULL) return ERROR;
   
    //3.找到插入前一个位置上的结点p
    while (i < index && p->next != *L) {
        p = p->next;
        i++;
    }
    
    //4.如果i>index 则返回error
    if (i > index)  return ERROR;
    
    //5.创建新结点temp
    LinkList temp = (LinkList)malloc(sizeof(KNode));
    
    //6.temp 结点为空,则返回error
    if (temp == NULL) return ERROR;
    
    //7.将生成的新结点temp数据域赋值e.
    temp->data = e;
    
    //8.将结点temp 的前驱结点为p;
    temp->prior = p;
    //9.temp的后继结点指向p->next;
    temp->next = p->next;
    //10.p的后继结点为新结点temp;
    p->next = temp;
    
    //如果temp 结点不是最后一个结点
    if (*L != temp->next) {
        
        //11.temp节点的下一个结点的前驱为temp 结点
        temp->next->prior = temp;
    }else{

        (*L)->prior = temp;
        
    }
    
    return OK;
}


//6.3 遍历双向循环链表
KStatus Display(LinkList L){
    
    if (L == NULL) {
        printf("打印的双向循环链表为空!\n\n");
        return ERROR;
    }
    printf("双向循环链表内容:  ");
    
    LinkList p = L->next;
    while (p != L) {

        printf("%d  ",p->data);
        p = p->next;
    }
    printf("\n\n");
    return OK;
}

//6.4 双向循环链表删除结点
KStatus LinkListDelete(LinkList *L,int index,KElementType *e){
    
    int i = 1;
    LinkList temp = (*L)->next;
    
    if (*L == NULL) {
        return  ERROR;
    }
    
    //①.如果删除到只剩下首元结点了,则直接将*L置空;
    if(temp->next == *L){
        free(*L);
        (*L) = NULL;
        return OK;
    }
    
    //1.找到要删除的结点
    while (i < index) {
        temp = temp->next;
        i++;
    }

    //2.给e赋值要删除结点的数据域
    *e = temp->data;
    
    //3.修改被删除结点的前驱结点的后继指针 图1️⃣
    temp->prior->next = temp->next;
    //4.修改被删除结点的后继结点的前驱指针 图2️⃣
    temp->next->prior = temp->prior;
    //5. 删除结点temp
    free(temp);
    
    return OK;
    
}

void test() {
    LinkList L;
    KStatus iStatus;
    KElementType temp,item;
    
    iStatus = creatLinkList(&L);
    printf("双向循环链表初始化是否成功(1->YES)/ (0->NO):  %d\n\n",iStatus);
    Display(L);
    
    printf("输入要插入的位置和数据用空格隔开：");
    scanf("%d %d",&temp,&item);
    iStatus = LinkListInsert(&L,temp,item);
    Display(L);

    printf("输入要删除位置：");
    scanf("%d",&temp);
    iStatus = LinkListDelete(&L, temp, &item);
    printf("删除链表位置为%d,结点数据域为:%d\n",temp,item);
    Display(L);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    test();
    
    return 0;
}

