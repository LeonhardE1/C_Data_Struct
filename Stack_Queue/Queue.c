//
// Created by lk129 on 2023/8/13.
//
#include "../All.h"


// 队列节点结构
typedef struct QNode {
    ElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

// 队列结构
typedef struct {
    QueuePtr front; // 队头指针
    QueuePtr rear;  // 队尾指针
} LinkQueue;

// 初始化队列
Status InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q->front) {
        exit(OVERFLOW); // 内存分配失败
    }
    Q->front->next = NULL;
    return OK;
}

// 判断队列是否为空
Status QueueIsEmpty(LinkQueue *Q) {
    return Q->front == Q->rear ? TRUE : FALSE;
}

// 入队操作
Status EnQueue(LinkQueue *Q, ElemType e) {
    QueuePtr new_node = (QueuePtr)malloc(sizeof(QNode));
    if (!new_node) {
        exit(OVERFLOW); // 内存分配失败
    }
    new_node->data = e;
    new_node->next = NULL;
    Q->rear->next = new_node;
    Q->rear = new_node;
    return OK;
}


// 出队操作
Status DeQueue(LinkQueue *Q, ElemType *e) {
    if (Q->front == Q->rear) {
        return ERROR; // 队列为空
    }
    QueuePtr temp = Q->front->next;
    *e = temp->data;
    Q->front->next = temp->next;
    if (Q->rear == temp) {
        Q->rear = Q->front; // 队列只有一个元素时，出队后更新 rear
    }
    free(temp);
    return OK;
}

// 获取队列长度
int QueueLength(LinkQueue *Q) {
    int length = 0;
    QueuePtr p = Q->front->next;
    while (p) {
        length++;
        p = p->next;
    }
    return length;
}

// 遍历队列
Status QueueTraverse(LinkQueue *Q) {
    QueuePtr p = Q->front->next;
    while (p) {
        // 遍历队列中的元素并处理
        // 这里可以根据实际需要进行操作
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

// 清空队列
Status ClearQueue(LinkQueue *Q) {
    while (Q->front->next) {
        QueuePtr temp = Q->front->next;
        Q->front->next = temp->next;
        free(temp);
    }
    Q->rear = Q->front; // 清空后队头和队尾相等
    return OK;
}

// 销毁队列
Status DestroyQueue(LinkQueue *Q) {
    ClearQueue(Q);
    free(Q->front);
    Q->front = Q->rear = NULL;
    return OK;
}

int main() {
    LinkQueue Q;
    InitQueue(&Q);

    // 入队操作
    for (ElemType ch = 'A'; ch <= 'E'; ch++) {
        EnQueue(&Q, ch);
        printf("Enqueued: %c\n", ch);
    }

    printf("Queue Length: %d\n", QueueLength(&Q));

    // 遍历并打印队列中元素
    printf("Queue Elements: ");
    QueueTraverse(&Q);

    // 出队操作
    ElemType dequeued_element;
    for (int i = 0; i < 3; i++) {
        if (DeQueue(&Q, &dequeued_element) == OK) {
            printf("Dequeued: %c\n", dequeued_element);
        } else {
            printf("Queue is empty\n");
        }
    }

    printf("Queue Length: %d\n", QueueLength(&Q));

    // 遍历并打印队列中元素
    printf("Queue Elements: ");
    QueueTraverse(&Q);

    // 清空队列
    ClearQueue(&Q);

    DestroyQueue(&Q);

    return 0;
}
