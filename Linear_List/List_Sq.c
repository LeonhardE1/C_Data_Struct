//
// Created by lk129 on 2023/7/14.
// 关于顺序线性表的学习
//
#include "../All.h"

//线性的动态分配顺序存储结构
typedef struct {
    ElemType *elem;
    int length;
    int listsize;
} SqList;

Status InitList_Sq(SqList *L){
    //构造一个空的线性表L
    L->elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof (ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

Status DestroyList_Sq(SqList *L) {
    // 销毁线性表L
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}

Status ListInsert_Sq(SqList *L, int pos, ElemType e) {
    // 在顺序表L的第pos个位置插入元素e
    if (pos < 1 || pos > L->length + 1) return ERROR; // 插入位置不合法
    if (L->length >= L->listsize) {
        // 当顺序表已满时，进行扩容
        ElemType *newElem = (ElemType *)realloc(L->elem, (L->listsize + LIST_INIT_SIZE) * sizeof(ElemType));
        if (!newElem) exit(OVERFLOW); // 扩容失败
        L->elem = newElem;
        L->listsize += LIST_INIT_SIZE;
    }
    for (int i = L->length - 1; i >= pos - 1; i--) {
        L->elem[i + 1] = L->elem[i]; // 向后移动元素
    }
    L->elem[pos - 1] = e; // 插入新元素
    L->length++;
    return OK;
}

Status ListDelete_Sq(SqList *L, int pos, ElemType *e) {
    // 删除顺序表L的第pos个位置的元素，并将其值存储到e中
    if (pos < 1 || pos > L->length) return ERROR; // 删除位置不合法
    *e = L->elem[pos - 1]; // 将删除的元素值保存到e中
    for (int i = pos; i < L->length; i++) {
        L->elem[i - 1] = L->elem[i]; // 向前移动元素
    }
    L->length--;
    return OK;
}

void MergeList_Sq(SqList *La, SqList *Lb, SqList *Lc) {
    // 合并顺序表La和Lb，并将结果存储在顺序表Lc中
    Lc->listsize = Lc->length = La->length + Lb->length;
    Lc->elem = (ElemType *)malloc(Lc->listsize * sizeof(ElemType));
    if (!Lc->elem) exit(OVERFLOW);
    int i = 0, j = 0, k = 0;
    while (i < La->length && j < Lb->length) {
        if (La->elem[i] <= Lb->elem[j]) {
            Lc->elem[k++] = La->elem[i++];
        } else {
            Lc->elem[k++] = Lb->elem[j++];
        }
    }
    while (i < La->length) {
        Lc->elem[k++] = La->elem[i++];
    }
    while (j < Lb->length) {
        Lc->elem[k++] = Lb->elem[j++];
    }
}
void PrintList_Sq(SqList *L) {
    // 打印顺序表L的所有元素
    printf("List elements: ");
    for (int i = 0; i < L->length; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

int main() {
    SqList L;
    InitList_Sq(&L);

    // 添加元素示例
    ListInsert_Sq(&L, 1, 10);
    ListInsert_Sq(&L, 2, 20);
    ListInsert_Sq(&L, 3, 30);

    // 删除元素示例
    ElemType deletedElem;
    ListDelete_Sq(&L, 2, &deletedElem);
    printf("Deleted element: %d\n", deletedElem);

    // 合并两个顺序表示例
    SqList La, Lb, Lc;
    InitList_Sq(&La);
    InitList_Sq(&Lb);
    ListInsert_Sq(&La, 1, 5);
    ListInsert_Sq(&La, 2, 15);
    ListInsert_Sq(&Lb, 1, 7);
    ListInsert_Sq(&Lb, 2, 12);
    MergeList_Sq(&La, &Lb, &Lc);

    // 打印顺序表示例
    PrintList_Sq(&L);
    PrintList_Sq(&La);
    PrintList_Sq(&Lb);
    PrintList_Sq(&Lc);

    // 销毁顺序表示例
    DestroyList_Sq(&L);
    DestroyList_Sq(&La);
    DestroyList_Sq(&Lb);
    DestroyList_Sq(&Lc);

    return 0;
}
