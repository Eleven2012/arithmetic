//
//  main.c
//  008_Stack
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
typedef int KStackElementType; /* KStackElementType类型根据实际情况而定，这里假设为int */

//顺序栈结构
typedef struct KSqueueStack{
    KStackElementType data[MAXSIZE];
    int top; //用于栈顶指针
}SqStack;

//1. 构建一个空栈S
KStatus initStack(SqStack *S) {
    S->top = -1;
    return OK;
}

//2. 将栈置空
KStatus clearStack(SqStack *S) {
    S->top = -1;
    return OK;
}

//3. 判断顺序栈是否为空
KStatus isEmpty(SqStack S) {
    return  S.top == -1 ;
}

//4. 获取栈长度
int getLength(SqStack S) {
    return S.top + 1;
}

//5. 获取栈顶
KStatus getTop(SqStack S, KStackElementType *e) {
    //栈空，则返回错误
    if (S.top == -1) return ERROR;
    *e = S.data[S.top];
    return OK;
}

//6. 压栈
KStatus push(SqStack *S, KStackElementType e) {
    //判断是否 栈满
    if (S->top == MAXSIZE -1) return ERROR;
    //1. 栈顶指针+1;
    //2. 将新插入的元素赋值给栈顶空间
    //S->top ++;
    //S->data[S->top] = e;
    S->data[++(S->top)] = e;
    return OK;
}

//7. 出栈
KStatus pop(SqStack *S, KStackElementType *e) {
    //判断是否栈空
    if(S->top == -1) return ERROR;
    //1. 将要删除的栈顶元素赋值给e
    //2. 栈顶指针--;
    //*e = S->data[S->top];
    //S->top--;
    *e = S->data[S->top--];
    return OK;
}

//8. 栈遍历
KStatus traverse(SqStack S) {
    int i = 0;
    printf("栈所有元素：");
    while (i < S.top) {
        printf("%d ",S.data[i++]);
    }
    printf("\n");
    return OK;
}

//9. 测试
void test() {
    SqStack S;
    int e;
    
    if (initStack(&S) == OK) {
        for (int j = 1 ; j < 10; j++) {
            push(&S, j);
        }
    }
    
    printf("顺序栈中元素为:\n");
    traverse(S);
    
    pop(&S, &e);
    printf("弹出栈顶元素为: %d\n",e);
    traverse(S);
    printf("是否为空栈:%d\n",isEmpty(S));
    getTop(S, &e);
    printf("栈顶元素:%d \n栈长度:%d\n",e,getLength(S));
    clearStack(&S);
    printf("是否已经清空栈 %d, 栈长度为:%d\n",isEmpty(S),getLength(S));
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    test();
    return 0;
}
