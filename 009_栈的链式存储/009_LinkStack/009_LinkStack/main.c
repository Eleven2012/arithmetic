//
//  main.c
//  009_LinkStack
//
//  Created by yulu kong on 2020/4/13.
//  Copyright © 2020 yulu kong. All rights reserved.
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
typedef int KStackElementType; /* SElemType类型根据实际情况而定，这里假设为int */

//链栈结点
typedef struct KStackNode {
    KStackElementType data;    //结点数据
    struct KStackNode *next;   //指向下一个结点的指针
}StackNode, *LinkStackPtr;

//链栈结构
typedef struct KLinkStack {
    LinkStackPtr top;   //栈顶结点
    int count;          //栈大小
}LinkStack;

//1. 构造一个空栈S
KStatus initStack(LinkStack *S) {
    S->top = NULL;
    S->count = 0;
    return OK;
}

//2. 链栈置空
KStatus clearStack(LinkStack *S) {
    LinkStackPtr p,q;
    //p指向栈顶结点
    p = S->top;
    while (p) {
        //保存要删除的结点p
        q = p;
        //然p指向它的下一个结点
        p = p->next;
        //删除 p结点
        free(q);
    }
    return OK;
}

//3. 判断栈是否为空
KStatus isEmpty(LinkStack S) {
    return S.count == 0;
}

//4. 获取栈长度
int getLength(LinkStack S) {
    return S.count;
}

//5. 获取栈顶元素
KStatus getTop(LinkStack S, KStackElementType *e) {
    //判断是否栈空
    if (S.top == NULL) return ERROR;
    *e = S.top->data;
    return OK;
}

//6. 压栈
KStatus push(LinkStack *S, KStackElementType e) {
    //1. 创建一个新结点，
    LinkStackPtr newNode = (LinkStackPtr)malloc(sizeof(StackNode));
    //2. 赋值给新结点
    newNode->data = e;
    
    //3. 插入新结点到栈顶结点后面
    //3.1 把当前的栈顶元素的结点指针指向直接后继结点
    newNode->next = S->top;
    //3.2 将新结点赋值给栈顶指针
    S->top = newNode;
    //栈大小+1
    S->count++;
    
    return OK;
}

//7. 出栈
KStatus pop(LinkStack *S, KStackElementType *e) {
    LinkStackPtr p;
    if (isEmpty(*S)) return ERROR;
    //1. 将栈顶元素赋值给*e
    *e = S->top->data;
    //2. 将栈顶结点赋值给p
    p = S->top;
    //3. 使得栈顶指针下移一位, 指向后一结点
    S->top = S->top->next;
    //4. 释放p结点
    free(p);
    //栈大小减1
    S->count--;
    
    return OK;
}

//8. 遍历栈
KStatus traverse(LinkStack S) {
    LinkStackPtr p = S.top;
    printf("遍历栈元素：");
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

//9. 单元测试
void test() {
    int j;
    LinkStack s;
    int e;
    if(initStack(&s)==OK)
        for(j=1;j<=10;j++)
            push(&s,j);
    printf("栈中元素依次为：");
    traverse(s);
    pop(&s,&e);
    printf("弹出的栈顶元素 e=%d\n",e);
    traverse(s);
    printf("栈空否：%d(1:空 0:否)\n",isEmpty(s));
    getTop(s,&e);
    printf("栈顶元素 e=%d 栈的长度为%d\n",e,getLength(s));
    clearStack(&s);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n",isEmpty(s));
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    test();
    return 0;
}
