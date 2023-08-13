//
// Created by lk129 on 2023/7/29.
// 关于单向链表的学习
//

#include "../All.h"

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, * LinkList;     //LinkList = LNode *;

// 链表初始化
Status InitList(LinkList *L) {
    *L = (LinkList)malloc(sizeof(LNode)); // 堆区开辟一个头结点，结点的数据类型为LNode
    if (!(*L)) exit(OVERFLOW);
    (*L)->next = NULL; // 空表，也就是说头结点的指针指向为空
    return OK;
}

// 头插法
void CreateList_H(LinkList *L, const ElemType a[], int n) {
    LNode *s;
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL; // 先建立一个带头结点的单链表
    for (int i = 0; i < n; i++) {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = a[i];
        s->next = (*L)->next; // 将s结点插入到头结点之后
        (*L)->next = s;
    }
}

// 尾插法
void CreateList_T(LinkList *L, const ElemType a[], int n) {
    LNode *s, *r;
    *L = (LinkList)malloc(sizeof(LNode));
    r = *L; // r始终指向尾结点，初始时指向头结点
    for (int i = 0; i < n; i++) {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = a[i];
        r->next = s; // 将s结点插入到尾结点之后
        r = s; // 更新尾结点为s
    }
    r->next = NULL; // 尾结点指针置空
}

// 在链表L的第pos个位置插入元素e
Status ListInsert(LinkList L, int pos, ElemType e) {
    LNode *p = L;
    int i = 0;
    while (p && i < pos - 1) {
        p = p->next; // 定位到插入位置的前一个结点
        i++;
    }
    if (!p || i > pos - 1) return ERROR; // 插入位置不合法
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next; // 插入结点s
    p->next = s;
    return OK;
}

// 删除链表L的第pos个位置的元素，并将其值存储到e中
Status ListDelete(LinkList L, int pos, ElemType *e) {
    LNode *p = L;
    int i = 0;
    while (p->next && i < pos - 1) {
        p = p->next; // 定位到删除位置的前一个结点
        i++;
    }
    if (!(p->next) || i > pos - 1) return ERROR; // 删除位置不合法
    LNode *q = p->next;
    p->next = q->next; // 删除结点q
    *e = q->data; // 将删除的元素值保存到e中
    free(q);
    return OK;
}

// 合并链表La和Lb，并将结果存储在链表Lc中
void MergeList(LinkList La, LinkList Lb, LinkList *Lc) {
    LNode *pa = La->next;
    LNode *pb = Lb->next;
    LNode *pc = *Lc = La; // Lc指向La的头结点
    while (pa && pb) {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb; // 插入剩余结点
    free(Lb); // 释放Lb的头结点
}

// 打印链表L的所有元素
void PrintList(LinkList L) {
    LNode *p = L->next;
    printf("List elements: ");
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    LinkList L = NULL;
    InitList(&L);

    // 头插法示例
    ElemType arr1[] = {10, 20, 30};
    int n1 = sizeof(arr1) / sizeof(ElemType);
    CreateList_H(&L, arr1, n1);
    PrintList(L);

    // 尾插法示例
    ElemType arr2[] = {40, 50, 60};
    int n2 = sizeof(arr2) / sizeof(ElemType);
    CreateList_T(&L, arr2, n2);
    PrintList(L);

    // 插入示例
    ListInsert(L, 2, 25);
    PrintList(L);

    // 删除示例
    ElemType deletedElem;
    ListDelete(L, 4, &deletedElem);
    printf("Deleted element: %d\n", deletedElem);
    PrintList(L);

    // 合并示例
    LinkList L2 = NULL;
    InitList(&L2);
    ElemType arr3[] = {15, 35, 45};
    int n3 = sizeof(arr3) / sizeof(ElemType);
    CreateList_T(&L2, arr3, n3);
    PrintList(L2);

    LinkList L3 = NULL;
    InitList(&L3);
    MergeList(L, L2, &L3);
    PrintList(L3);

    return 0;
}
