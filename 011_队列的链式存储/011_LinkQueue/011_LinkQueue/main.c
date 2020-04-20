//
//  main.c
//  011_LinkQueue
//
//  Created by 孔雨露 on 2020/4/18.
//  Copyright © 2020 Apple. All rights reserved.
//

/*
 链式 队列的基本操作实现
 */

#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int KStatus;
typedef int KQueueElementType;

//结点结构
typedef struct KQueueNode{
    KQueueElementType data;
    struct KQueueNode *next;
}KQNode, *KQueuePtr;

//队列的链表结构
typedef struct KLinkQueue {
    KQueuePtr front; //队头
    KQueuePtr rear;  //队尾
}KLQueue;

// 1. 初始化队列
KStatus initQueue(KLQueue *Q) {
    //1. 队列头指针和尾指针都只需新生成的结点
    Q->front = Q->rear = (KQueuePtr)malloc(sizeof(KQNode));
    //2. 判断结点是否创建成功
    if (!Q->front) return ERROR;
    //3. 队列头指针域置空
    Q->front->next = NULL;
    
    return OK;
}

// 2. 销毁队列
KStatus destoryQueue(KLQueue *Q) {
    //遍历整个队列，销毁每一个结点
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

// 3. 清空队列
KStatus clearQueue(KLQueue *Q) {
    KQueuePtr p,q;
    Q->rear = Q->front;
    p = Q->front->next;
    Q->front->next = NULL;
    while (p) {
        q = p->next;
        p = p->next;
        free(q);
    }
    return OK;
}

// 4. 队列判空
KStatus isEmpty(KLQueue Q) {
    return Q.front == Q.rear;
}


// 6. 获取对头元素
KStatus getHead(KLQueue Q, KQueueElementType *e){
    if (Q.front != Q.rear) {
        //返回队头元素的值,队头指针不变
        *e = Q.front->next->data;
        return TRUE;
    }
    
    return FALSE;
}

// 7. 获取队列长度
int getLength(KLQueue Q){
    int count = 0;
    KQueuePtr p = Q.front;
    while (Q.rear != p) {
        count++;
        p = p->next;
    }
    return count;
}


// 8. 入队
KStatus enQueue(KLQueue *Q, KQueueElementType e) {
    //为入队元素分配结点空间,用指针s指向;
    KQueuePtr s = (KQueuePtr)malloc(sizeof(KQNode));
    if (!s) return ERROR;
    //将新结点s指定数据域
    s->data = e;
    s->next = NULL;
    
    //将新结点插入到队列尾部
    Q->rear->next = s;
    //修改队尾指针
    Q->rear = s;
    
    return OK;
}

// 9. 出队
KStatus deQueue(KLQueue *Q, KQueueElementType *e) {
    KQueuePtr p;
    //判断队列是否为空
    if (isEmpty(*Q)) return ERROR;
    
    //将要删除的队头结点暂时存储在p
    p = Q->front->next;
    //将要删除的队头结点的值赋值给e
    *e = p->data;
    //将原队列头结点的后继p->next 赋值给头结点后继
    Q->front->next = p->next;
    
    //若队头就是队尾,则删除后将rear指向头结点.
    if(Q->rear == p) Q->rear = Q->front;
    
    //释放结点
    free(p);
    
    return OK;
}


// 10. 遍历队列
KStatus traverseQueue(KLQueue Q) {
    KQueuePtr p = Q.front->next;
    while (p) {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
    
    return OK;
}

// 11. 单元测试
void test() {
    printf("链队列的表示与操作!\n");
    
    KStatus iStatus;
    KQueueElementType d;
    KLQueue q;
    
    //1.初始化队列q
    iStatus = initQueue(&q);
    
    //2. 判断是否创建成
    if (iStatus) {
        printf("成功地构造了一个空队列\n");
    }
    
    //3.判断队列是否为空
    printf("是否为空队列?%d (1:是 0:否)\n",isEmpty(q));
    
    //4.获取队列的长度
    printf("队列的长度为%d\n",getLength(q));
    
    //5.插入元素到队列中
    enQueue(&q, -3);
    enQueue(&q, 6);
    enQueue(&q, 12);
    
    printf("队列的长度为%d\n",getLength(q));
    printf("是否为空队列?%d (1:是 0:否)\n",isEmpty(q));
    
    //6.遍历队列
    printf("队列中的元素如下:\n");
    traverseQueue(q);

    //7.获取队列头元素
    iStatus = getHead(q, &d);
    if (iStatus == OK) {
        printf("队头元素是:%d\n",d);
    }
    
    //8.删除队头元素
    iStatus = deQueue(&q, &d);
    if (iStatus == OK) {
        printf("删除了的队头元素为:%d\n",d);
    }
    
    //9.获取队头元素
    iStatus = getHead(q, &d);
    if (iStatus == OK) {
        printf("新的队头元素为:%d\n",d);
    }
    
    //10.清空队列
    clearQueue(&q);
    
    //11.销毁队列
    destoryQueue(&q);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    test();
    return 0;
}
