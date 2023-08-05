//
// Created by lk129 on 2023/8/5.
//
#include "All.h"

typedef struct DuLNode {
    ElemType data;
    struct DuLNode * prior;
    struct DuLNode * next;
} DuLNode, *DuLinkList;

// 链表初始化
Status InitList(DuLinkList *L) {
    *L = (DuLinkList)malloc(sizeof(DuLNode));
    if (!(*L)) return ERROR;
    (*L)->prior = NULL;
    (*L)->next = NULL;
    return OK;
}

// 添加元素到双向链表尾部
Status AddElementToEnd(DuLinkList L, ElemType e) {
    DuLNode *p = L;
    while (p->next != NULL) {
        p = p->next; // 找到尾结点
    }
    DuLNode *newNode = (DuLNode *)malloc(sizeof(DuLNode));
    if (!newNode) return ERROR;
    newNode->data = e;
    newNode->prior = p; // 新节点的prior指针指向尾结点
    newNode->next = NULL; // 新节点的next指针指向NULL，即为尾节点
    p->next = newNode; // 将新节点插入到尾结点后面
    return OK;
}

// 删除双向链表中第一个出现的元素e
Status DeleteElement(DuLinkList L, ElemType e) {
    DuLNode *p = L->next;
    while (p != NULL) {
        if (p->data == e) {
            if (p->prior != NULL) {
                p->prior->next = p->next;
            }
            if (p->next != NULL) {
                p->next->prior = p->prior;
            }
            free(p);
            return OK;
        }
        p = p->next;
    }
    return ERROR; // 未找到要删除的元素
}

// 合并双向链表La和Lb，并将结果存储在双向链表Lc中
Status MergeLists(DuLinkList La, DuLinkList Lb, DuLinkList *Lc) {
    if (La == NULL || Lb == NULL) return ERROR;
    DuLNode *pa = La->next;
    DuLNode *pb = Lb->next;
    DuLNode *pc = *Lc = La; // Lc指向La的头结点
    while (pa != NULL && pb != NULL) {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pa->prior = pc;
            pc = pa;
            pa = pa->next;
        } else {
            pc->next = pb;
            pb->prior = pc;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = NULL;
    if (pa != NULL) {
        pc->next = pa;
        pa->prior = pc;
    }
    if (pb != NULL) {
        pc->next = pb;
        pb->prior = pc;
    }
    return OK;
}

// 打印双向链表的所有元素
void PrintList(DuLinkList L) {
    DuLNode *p = L->next;
    printf("List elements: ");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    DuLinkList L1, L2, L3;
    InitList(&L1);
    InitList(&L2);

    // 添加元素到双向链表L1和L2
    AddElementToEnd(L1, 10);
    AddElementToEnd(L1, 30);
    AddElementToEnd(L1, 50);

    AddElementToEnd(L2, 20);
    AddElementToEnd(L2, 40);
    AddElementToEnd(L2, 60);
    AddElementToEnd(L2, 70);

    // 打印双向链表L1和L2
    PrintList(L1);
    PrintList(L2);

    // 删除双向链表L1中的元素30
    DeleteElement(L1, 30);

    // 打印删除元素后的双向链表L1
    PrintList(L1);

    // 合并双向链表L1和L2，并将结果存储在L3中
    MergeLists(L1, L2, &L3);

    // 打印合并后的双向链表L3
    PrintList(L3);

    return 0;
}