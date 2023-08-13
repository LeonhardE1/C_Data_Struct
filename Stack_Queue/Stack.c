//
// Created by lk129 on 2023/8/12.
// 关于栈的学习
//

#include "../All.h"

// 栈结构
typedef struct {
    ElemType *base;
    ElemType *top;
    int stack_size;
} SqStack;

// 初始化栈
Status InitStack(SqStack *S) {
    S->base = (ElemType *) malloc ( STACK_INIT_SIZE * sizeof(ElemType) );
    if (!S->base) {
        exit(OVERFLOW); // 内存分配失败
    }
    S->top = S->base;
    S->stack_size = STACK_INIT_SIZE;
    return OK;
}

// 销毁栈
Status DestroyStack(SqStack *S) {
    free(S->base);
    S->base = S->top = NULL;
    S->stack_size = 0;
    return OK;
}

// 清空栈
Status ClearStack(SqStack *S) {
    S->top = S->base; // 栈顶指针回到栈底
    return OK;
}

// 获取栈的长度
int StackLength(SqStack *S) {
    return S->top - S->base;
}

// 获取栈顶元素
Status GetTop(SqStack *S, ElemType *e) {
    if (S->top == S->base) {
        return ERROR; // 栈空
    }
    *e = *(S->top - 1);
    return OK;
}

// 入栈
Status Push(SqStack *S, ElemType e) {
    if (S->top - S->base >= S->stack_size) {
        // 栈满，需要扩容
        S->base = (ElemType *)realloc(S->base, (S->stack_size + STACK_INCREMENT) * sizeof(ElemType));
        if (!S->base) {
            exit(ERROR); // 内存分配失败
        }
        S->top = S->base + S->stack_size;
        S->stack_size += STACK_INCREMENT;
    }
    *(S->top++) = e;
    return OK;
}

// 出栈
Status Pop(SqStack *S, ElemType *e) {
    if (S->top == S->base) {
        return ERROR; // 栈空
    }
    *e = *(--S->top);
    return OK;
}

// 遍历栈
Status StackTraverse(SqStack *S) {
    ElemType *p = S->base;
    while (p < S->top) {
        // 遍历栈中的元素并处理
        // 这里可以根据实际需要进行操作
        printf("%d ", *p);
        p++;
    }
    printf("\n");
    return OK;
}


int main() {
    SqStack S;
    InitStack(&S);

    // 入栈操作
    for (ElemType ch = 'A'; ch <= 'E'; ch++) {
        printf("Pushed: %c\n", ch);
        Push(&S, ch);
    }

    printf("Stack Length: %d\n", StackLength(&S));

    // 遍历并打印栈中元素
    printf("Stack Elements: ");
    StackTraverse(&S);

    // 出栈操作
    ElemType popped_element;
    for (int i = 0; i < 3; i++) {
        if (Pop(&S, &popped_element) == OK) {
            printf("Popped: %c\n", popped_element);
        } else {
            printf("Stack is empty\n");
        }
    }

    printf("Stack Length: %d\n", StackLength(&S));

    // 遍历并打印栈中元素
    printf("Stack Elements: ");
    StackTraverse(&S);

    // 清空栈
    ClearStack(&S);

    DestroyStack(&S);

    return 0;
}
