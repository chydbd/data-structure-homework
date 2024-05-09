#include <cstdio>
#include <iostream>
#define MAX 100
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char TElemtype;

typedef struct {
    BiTree* base;
    BiTree* top;
    int stacksize;
}SqStack;

int InitStack(SqStack& S) {
    S.base = (BiTree*)malloc(STACK_INIT_SIZE * sizeof(BiTree));
    if (!S.base)exit(-2);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return 1;
}

int GetTop(SqStack S, BiTree& e) {
    if (S.top == S.base)return 0;
    e = *(S.top - 1);
    return 1;
}

int Push(SqStack& S, BiTree& e) {
    if (S.top - S.base >= S.stacksize) {
        S.base = (BiTree*)realloc(S.base,
            (S.stacksize + STACKINCREMENT) * sizeof(BiTree));
        if (!S.base)exit(-2);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return 1;
}

int Pop(SqStack& S, BiTree e) {
    if (S.top == S.base)return 0;
    e = *--S.top;
    return 1;
}

int StackEmpty(SqStack& S) {
    if (S.base = S.top)return 1;
    else return 0;
}

typedef struct BiTNode {
	char data;
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
    InitStack(S); BiTree p = T;
    while (p || !StackEmpty(S)) {
        if (p) {
            Push(S, p);
            p = p->lchild;
        }
        else {
            Pop(S, p);
            if (!Visit(p->data))return 0;
            p = p->rchild;
        }
    }
    return 1;
}

int CreateBiTree(BiTree& T) {
    char ch;
    scanf(&ch);
    if (ch == ' ')T = NULL;
    else {
        if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))exit(-2);
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return 1;
}