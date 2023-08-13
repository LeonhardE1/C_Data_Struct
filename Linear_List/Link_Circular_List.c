//
// Created by lk129 on 2023/8/5.
// 关于循环链表的学习
//

#include "../All.h"

typedef struct CLNode
{
    ElemType data;
    struct CLNode *next;
} CLNode, *CircList;

// 初始化循环链表
void CreateCircularList(CircList *L) {
    *L = (CircList)malloc(sizeof(CLNode));
    (*L)->next = *L; // 初始时循环链表指向自身，形成一个空的循环链表
}

// 添加元素到循环链表尾部
Status AddElementToCircularList(CircList L, ElemType e) {
    CLNode *p = L;
    while (p->next != L) {
        p = p->next; // 找到尾结点
    }
    CLNode *newNode = (CLNode *)malloc(sizeof(CLNode));
    if (!newNode) return ERROR;
    newNode->data = e;
    newNode->next = L; // 新节点的next指针指向头结点，形成循环
    p->next = newNode; // 将新节点插入到尾结点后面
    return OK;
}

// 删除循环链表中第一个出现的元素e
Status DeleteElementFromCircularList(CircList L, ElemType e) {
    CLNode *p = L->next;
    CLNode *pre = L; // p的前驱指针
    while (p != L) {
        if (p->data == e) {
            pre->next = p->next; // 删除节点p
            free(p);
            return OK;
        }
        pre = p;
        p = p->next;
    }
    return ERROR; // 未找到要删除的元素
}

// 合并循环链表La和Lb，并将结果存储在循环链表Lc中
void MergeCircularList(CircList La, CircList Lb, CircList *Lc) {
    CLNode *pa = La->next;
    CLNode *pb = Lb->next;
    CLNode *pc = *Lc = La; // Lc指向La的头结点
    while (pa != La && pb != Lb) {
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
    // 处理剩余元素
    while (pa != La) {
        pc->next = pa;
        pc = pa;
        pa = pa->next;
    }
    while (pb != Lb) {
        pc->next = pb;
        pc = pb;
        pb = pb->next;
    }
    pc->next = La;// 形成循环链表
}

// 打印循环链表的所有元素
void PrintCircularList(CircList L) {
    CLNode *p = L->next;
    printf("Circular List elements: ");
    while (p != L) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    CircList L1, L2, L3;
    CreateCircularList(&L1);
    CreateCircularList(&L2);

    // 添加元素到循环链表L1和L2
    AddElementToCircularList(L1, 10);
    AddElementToCircularList(L1, 30);
    AddElementToCircularList(L1, 50);

    AddElementToCircularList(L2, 20);
    AddElementToCircularList(L2, 40);
    AddElementToCircularList(L2, 60);

    // 打印循环链表L1和L2
    PrintCircularList(L1);
    PrintCircularList(L2);

    // 删除循环链表L1中的元素30
    DeleteElementFromCircularList(L1, 30);

    // 打印删除元素后的循环链表L1
    PrintCircularList(L1);

    // 合并循环链表L1和L2，并将结果存储在L3中
    MergeCircularList(L1, L2, &L3);

    // 打印合并后的循环链表L3
    PrintCircularList(L3);

    return 0;
}