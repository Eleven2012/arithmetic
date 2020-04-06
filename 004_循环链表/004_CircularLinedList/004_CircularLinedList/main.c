//
//  main.c
//  004_CircularLinedList
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

#define MAXSIZE 20

typedef int KStatus;
typedef int KElementType;

//定义结点
typedef struct KNode{
    KElementType data;
    struct KNode *next;
}Node;

typedef struct KNode * LinkList;

//1. 创建循环链表
//2种情况:① 第一次开始创建; ②已经创建,往里面新增数据
/* 1. 判断是否第一次创建链表
   YES->创建一个新结点,并使得新结点的next 指向自身; (*L)->next = (*L);
   NO-> 找链表尾结点,将尾结点的next = 新结点. 新结点的next = (*L);
 */
KStatus createCircleList(LinkList *L) {
    
    int item;
    LinkList temp = NULL;
    LinkList target = NULL;
    
    printf("输入节点的值，输入0结束\n");
    while (1) {
        scanf("%d",&item);
        
        if(item == 0) break;
        
        //判断，如果输入的链表是空，则创建一个新结点，并且使其next指针指向自己  (*head)->next=*head;
        if(NULL == *L) {
            *L = (LinkList)malloc(sizeof(Node));
            if(!L) return ERROR;
            (*L)->data = item;
            (*L)->next = *L;
        } else {
            //如果输入的链表不为空，则寻找链表的尾结点，是尾结点的next=新节点。新节点的next指向头节点
            for (target = *L; target->next != *L; target = target->next);
            
            temp = (LinkList)malloc(sizeof(Node));
            if(!temp) return ERROR;
            
            //结点赋值，并插入尾部
            temp->data = item;
            //1.新节点指向头节点
            temp->next = *L;
            //2.尾节点指向新节点
            target->next = temp;
                
        }
    }
    
    return OK;
}

KStatus createCircleList2(LinkList *L) {
    
    int item;
    LinkList temp = NULL;
    //LinkList target = NULL;
    //增加一个赋值指针，指向尾结点
    LinkList r = *L;
    
    printf("输入节点的值，输入0结束\n");
    while (1) {
        scanf("%d",&item);
        
        if(item == 0) break;
        
        //判断，如果输入的链表是空，则创建一个新结点，并且使其next指针指向自己  (*head)->next=*head;
        if(NULL == *L) {
            *L = (LinkList)malloc(sizeof(Node));
            if(!L) return ERROR;
            (*L)->data = item;
            (*L)->next = *L;
            //记录尾结点
            r = *L;
        } else {
            //如果输入的链表不为空，则寻找链表的尾结点，是尾结点的next=新节点。新节点的next指向头节点
            //for (target = *L; target->next != *L; target = target->next);
            //这里已经用r指向了尾结点，不需要查找了。
            
            temp = (LinkList)malloc(sizeof(Node));
            if(!temp) return ERROR;
            
            //结点赋值，并插入尾部
            temp->data = item;
            //1.新节点指向头节点
            temp->next = *L;
            //2.尾节点指向新节点
            r->next = temp;
            
            //移动r指针，保存r指针一直指向尾结点
            r = temp;
                
        }
    }
    
    return OK;
}



// 2.遍历循环链表
void traverseCircleList(LinkList L) {
    //判断链表是否为空
    if(!L) {
        printf("链表为空！\n");
        return;
    }
    
    LinkList temp;
    temp = L;
    do {
        printf("%6d", temp->data);
        temp = temp->next;
    }while (temp != L) ;
    printf("\n");
}

// 3. 循环链表插入元素
// L : 链表指针
// place: 要插入的位置
// data : 要插入的数据
KStatus insertElement(LinkList *L, int place, int data) {
    
    LinkList temp, target;
    int i;
    
    //先判断位置是否为首结点，在首结点需要单独处理
    if (place == 1) {
        //1. 创建一个新结点
        temp = (LinkList)malloc(sizeof(Node));
        //判断内存是否分配成功
        if (! temp) return ERROR;
        //赋值
        temp->data = data;
        
        //2. 找到链表的最后一个结点，尾结点
        for(target = *L; target->next != *L ; target = target->next);
        
        //3.找到尾结点，插入到尾结点后面
        //3.1 让新结点的next,指向新的头结点
        temp->next = *L;
        //3.2 让尾结点的next指向新的结点，这样新的结点成了新的尾结点。
        target->next = temp;
        //3.3 让头指针指向新的尾结点
        *L = temp;
        
    } else { //其他位置
        //1. 创建一个新结点
        temp = (LinkList)malloc(sizeof(Node));
        //判断内存是否分配成功
        if (! temp) return ERROR;
        //赋值
        temp->data = data;
        
        //2. 找到链表的第place - 1 的位置
        for(i = 1, target = *L; target->next != *L && i != place - 1 ; target = target->next, i++);
        
        //3. 指向插入操作，将新结点插入到place位置
        //3.1 新结点的next 指向target原来的next位置 ;
        temp->next = target->next;
        //3.2 插入结点的前驱指向新结点
        target->next = temp;
    }
    return OK;
}


// 4. 循环链表删除元素
// 删除第place位置的元素
// L : 链表指针
// place: 要删除的位置
KStatus deleteElement(LinkList *L, int place) {
    
    LinkList temp, target;
    int i;
    //temp 指向链表首元结点
    temp = *L;
    //如果为空链表，则结束
    if (!temp) return ERROR;
    
    //判断是否是首节点，如果是首结点需要单独特殊处理
    if (place == 1) {
         //①.如果删除到只剩下首元结点了,则直接将*L置空;
        if((*L)->next == (*L)) {
            *L = NULL;
            return OK;
        }
        
        //②.链表还有很多数据,但是删除的是首结点;
        // 2.1 先要找到尾结点，
        for (target = *L; target->next != *L; target = target->next) ;
        // 2.2 使得尾结点next 指向头结点的下一个结点 target->next = (*L)->next;
        temp = *L;
        *L = (*L)->next;
        // 2.3 新结点做为头结点,则释放原来的头结点
        target->next = *L;
        //释放资源
        free(temp);
    } else { //其他位置，统一处理
        //遍历找到第place-1个位置
        for (i = 1, target = *L; target->next != *L && i != place - 1; target = target->next, i++) {
            //找到删除结点前一个结点target
            //用temp指向要删除的元素，第place位置
            temp = target->next;
            //使得target->next 指向下一个结点
            target->next = temp->next;
            
            //释放内存
            free(temp);
        }
    }
    return OK;
}

//5. 循环列表查询
// 返回位置的索引值
int queryValue(LinkList L , int value) {
    int i = 1;
    LinkList p = L;
    
    //寻找链表中的结点 data == value
    while (p->data != value) {
        i++;
        p = p->next;
    }
    //当尾结点指向头结点就会直接跳出循环,所以要额外增加一次判断尾结点的data == value;
    if (p->next == L && p->data != value) return -1; //没有找到
    //找到了元素，返回下标
    return i;
}

// 6. 单元测试
void test() {
       LinkList head;
        int place,num;
        int iStatus;
        
        iStatus = createCircleList(&head);
        //iStatus = createCircleList2(&head);
        printf("原始的链表：\n");
        traverseCircleList(head);
        
    //    printf("输入要插入的位置和数据用空格隔开：");
    //    scanf("%d %d",&place,&num);
    //    iStatus = insertElement(&head,place,num);
    //    traverseCircleList(head);

        printf("输入要删除的位置：");
        scanf("%d",&place);
        deleteElement(&head,place);
        traverseCircleList(head);
        
        
        printf("输入你想查找的值:");
        scanf("%d",&num);
        place = queryValue(head,num);
        if(place!=-1)
            printf("找到的值的位置是place = %d\n",place);
        else
            printf("没找到值\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    test();
    return 0;
}
