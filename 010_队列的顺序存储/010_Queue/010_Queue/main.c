//
//  main.c
//  010_Queue
//
//  Created by 孔雨露 on 2020/4/18.
//  Copyright © 2020 Apple. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int KStatus;
typedef int KQueueElementType; /* KQueueElementType类型根据实际情况而定，这里假设为int */

/* 循环队列的顺序存储结构 */
typedef struct KQueue
{
    KQueueElementType data[MAXSIZE];
    int front;        /* 头指针 */
    int rear;        /* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
}KQueue;

//1. 初始化一个队列
KStatus initQueue(KQueue *Q) {
    Q->front = Q->rear = 0;
    return OK;
}

//2. 将队列清空
KStatus clearQueue(KQueue *Q) {
    Q->front = Q->rear = 0;
    return OK;
}

//3. 队列判空
KStatus isEmpty(KQueue Q) {
    return Q.front == Q.rear ;
}

//4. 队列是否满了
KStatus isFull(KQueue Q) {
    return Q.front == (Q.rear + 1 ) % MAXSIZE;
}

//5. 查询队列长度
int getLength(KQueue Q) {
    return (Q.rear - Q.front + MAXSIZE)%MAXSIZE;
}

//6. 获取队头元素
//若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR;
KStatus getHead(KQueue Q, KQueueElementType *e) {
    //判断是否队列为空
    if (isEmpty(Q)) {
        return ERROR;
    }
    //取出元素值
    *e = Q.data[Q.front];
    return OK;
}

//7. 入队
// 若队列未满,则插入元素e为新队尾元素
KStatus enQueue(KQueue *Q, KQueueElementType e) {
    //判断队列是否满了
    if (isFull(*Q)) {
        return ERROR;
    }
    //将元素e赋值给队尾
    Q->data[Q->rear] = e;
    
    //rear指针向后移动一位，若到最后则转到数组头部
    Q->rear = (Q->rear + 1) % MAXSIZE;
    
    return OK;
}

//8. 出队
//若队列不空,则删除Q中队头的元素,用e返回值
KStatus deQueue(KQueue *Q, KQueueElementType *e) {
    if (isEmpty(*Q)) return ERROR;
    //从队头取出元素赋值给e
    *e = Q->data[Q->front];
    
    //front指针向后移动一位，删除对头元素
    Q->front = (Q->front + 1) % MAXSIZE;
    
    return OK;
}

//9. 遍历队列
KStatus traverseQueue(KQueue Q) {
    int i = Q.front;
    while ((i + Q.front) != Q.rear) {
        //从队头遍历到队尾，依次输出元素，i表示当前已经输出到第几个元素了
        //(i + Q.front) != Q.rear 表示 已经遍历到了队尾了，
        //由于我们不能修改front和rear指向，所以需要一个临时变量记录当前位置
        printf("%d  ", Q.data[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
    
    return OK;
}


//10. 单元测试
void test() {
    printf("循环队列操作单元测试\n");
    KStatus j;
    int i=0;
    KQueueElementType d;
    KQueue Q;
    initQueue(&Q);
    printf("初始化队列后，队列空否？%u(1:空 0:否)\n",isEmpty(Q));
    
    printf("入队:\n");
    while (i < 10) {
        enQueue(&Q, i);
        i++;
    }
    traverseQueue(Q);
    printf("队列长度为: %d\n",getLength(Q));
    printf("现在队列空否？%u(1:空 0:否)\n",isEmpty(Q));
    printf("出队:\n");
   
   //出队
    deQueue(&Q, &d);
    printf("出队的元素:%d\n",d);
    traverseQueue(Q);

    //获取队头
    j=getHead(Q,&d);
    if(j)
        printf("现在队头元素为: %d\n",d);
    clearQueue(&Q);
    printf("清空队列后, 队列空否？%u(1:空 0:否)\n",isEmpty(Q));

}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    test();
    return 0;
}
