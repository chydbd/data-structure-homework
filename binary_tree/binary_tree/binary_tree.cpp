#include <cstdio>
#include <iostream>
#define MAX 100
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int TElemtype;

typedef struct {
    int* base;
    int* top;
    int stacksize;
}SqStack;

int InitStack(SqStack& S) {
    S.base = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!S.base)exit(-2);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return 1;
}

int GetTop(SqStack S, int& e) {
    if (S.top == S.base)return 0;
    e = *(S.top - 1);
    return 1;
}

int Push(SqStack& S, int& e) {
    if (S.top - S.base >= S.stacksize) {
        S.base = (int*)realloc(S.base,
            (S.stacksize + STACKINCREMENT) * sizeof(int));
        if (!S.base)exit(-2);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return 1;
}

int Pop(SqStack& S, int e) {
    if (S.top == S.base)return 0;
    e = *--S.top;
    return 1;
}

typedef struct BiTNode {
	int data;
	struct BiTNode* lchild, * rchild;
}BiTNode, *BiTree;

int PreOrderTraverse(BiTree T, int (*Visit)(int e)) {
	if (T) {
		if (Visit(T->data))
			if (PreOrderTraverse(T->lchild, Visit))
				if (PreOrderTraverse(T->rchild, Visit)) return 1;
		return 0;
	}
	else return 1;
}

int InOrderTraverse(BiTree T, int (*Visit)(int e)) {
    SqStack S;
    InitStack(S); Push(S, T);

}