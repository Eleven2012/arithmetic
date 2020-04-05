//
//  main.c
//  001_LinearList
//
//  Created by 孔雨露 on 2020/4/5.
//  Copyright © 2020 Apple. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//KElementType类型根据实际情况而定，这里假设为int
typedef int KElementType;
//KStatus是函数的类型,其值是函数结果状态代码，如OK等
typedef int KStatus;


//顺序表结构
typedef struct KSequenceList {
    KElementType *data;
    int length;
}KSList;

// 1 顺序表初始化
KStatus initSequenceList(KSList *L) {
    
    //为顺序表分配一个大小为MAXSIZE 的数组空间
    L->data = malloc(sizeof(KElementType) * MAXSIZE);
    //存储分配失败直接退出
    if(!L->data) return ERROR;
    //空表长度为0
    L->length = 0;
    
    return OK;
}

// 2 顺序表的插入
// 初始条件：顺序线性表L已存在,1≤i≤ListLength(L);
// 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1
KStatus insertElement(KSList *L, int i, KElementType e) {
    
    //边界条件判断
    //1.1 出入的索引 i 合法性判断, 不能超过链表总长度
    if((i < 1) || (i > L->length+1)) return ERROR;
    //1.2 存储空间是否已满
    if(L->length == MAXSIZE) return ERROR;
    
    //1.3 插入数据如果不在表尾部，则先往后移动腾出位置给要插入的元素
    if(i <= L->length) {
        for(int j = L->length-1; j >= i-1; j--) {
            //插入位置后面的元素都移动1个位置，让出第i个位置
            L->data[i+1] = L->data[i];
        }
    }
    
    //1.4 将新元素赋值到腾出的位置，完成插入
    L->data[i-1] = e;
    
    //1.5 链表长度增加1
    ++L->length;
    
    return OK;
}


// 3. 顺序表的取值
KStatus getElement(KSList L, int i, KElementType *e) {
    
    //边界条件判断，i不能超过总长度
    if(i < 1 || i > L.length) return ERROR;
    
    //直接取出第i个元素的值，索引下标对应为i-1 (下标默认从0开始)
    *e = L.data[i-1];
    
    return OK;
}

// 4. 顺序表删除
//初始条件：顺序线性表L已存在，1≤i≤ListLength(L)
//操作结果: 删除L的第i个数据元素,L的长度减1
KStatus deleteElement(KSList *L, int i) {
    
    //边界条件判断
    //线性表是否为空
    if(L->length == 0) return ERROR;
    //i值合法性判断
    if((i < 1) || (i > L->length+1)) return ERROR;
    
    for (int j = i; j < L->length; j++) {
        //被删除的元素后面的所有元素往前移动一个位置
        L->data[j-1] = L->data[j];
    }
    
    //表长度减1
    L->length--;
    
    return OK;
}

// 5. 清空顺序表
//初始条件：顺序线性表L已存在。操作结果：将L重置为空表
KStatus clearList(KSList *L) {
    L->length = 0;
    return OK;
}

// 6. 判断顺序表清空
//初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
KStatus isListEmpty(KSList L) {
    return L.length == 0 ;
}

// 7. 获取顺序表表长度
int getListLength(KSList L) {
    return L.length;
}

// 8. 遍历顺序表
//初始条件：顺序线性表L已存在
//操作结果：依次对L的每个数据元素输出
KStatus traverseList(KSList L) {
    for(int i = 0; i < L.length; i++) {
        printf("%d.\n",L.data[i]);
    }
    printf("\n");
    return OK;
}

// 9. 查找顺序表元素下标
//初始条件：顺序线性表L已存在
//操作结果：返回L中第1个与e满足关系的数据元素的位序。
//若这样的数据元素不存在，则返回值为0
int getElementIndex(KSList L, KElementType e) {
    //边界条件判断
    if (L.length == 0 ) return 0;
    
    //顺序查找
    int i = 0;
    for(i = 0; i < L.length; i++) {
        if (L.data[i] == e) {break;}
    }
    
    if (i >= L.length) return 0;
    
    return i;
}

// 10. 单元测试
void test() {
    KSList L1;
    //KSList L2;
    KElementType e;
    KStatus iStatus;
    
    //1.1 顺序表初始化
    iStatus = initSequenceList(&L1);
    printf("初始化L1后: L.Length = %d\n", L1.length);
    
    //1.2 顺序表数据插入
    for(int j=1; j <= 5;j++){
        iStatus = insertElement(&L1, 1, j);
    }
    printf("插入数据L1长度: %d\n",L1.length);
    
    //1.3 顺序表取值
    getElement(L1, 5, &e);
    printf("顺序表L1第5个元素的值为:%d\n",e);
    
    //1.4 顺序表删除第2个元素
    deleteElement(&L1, 2);
    printf("顺序表L1删除第%d元素,长度为%d\n",2,L1.length);
    
    //1.5 清空顺序表
    iStatus = clearList(&L1);
    printf("清空L1后,L.length = %d\n",L1.length);
    
    //1.6 判断List是否为空
    iStatus = isListEmpty(L1);
    printf("L1是否空：i=%d(1:是 0:否)\n",iStatus);
    
    //1.8 遍历打印顺序表
    for(int j=1; j <= 5;j++){
        iStatus = insertElement(&L1, 1, j);
    }
    traverseList(L1);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    test();
    return 0;
}
