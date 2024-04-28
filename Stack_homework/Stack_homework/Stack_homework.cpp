#include <cstdio>
#include <iostream>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct {
    int* base;
    int* top;
    int stacksize;
}SqStack;

int InitStack(SqStack& S) {
    S.base = (int*)malloc(STACK_INIT_SIZE * sizeof(int));

}

int main()
{
    
}

