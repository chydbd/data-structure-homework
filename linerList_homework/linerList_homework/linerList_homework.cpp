#include <cstdlib>
#include <cstdio>
#include <iostream>

#define LIST_INIT_SIZE 10

typedef struct {
	int* elem;
	int length;
	int listsize;
}SqLinerList;

typedef struct LNode {
	int data;
	struct LNode* next;
}LNode, * LinkList;

bool initList(SqLinerList& L) {
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem)return false;
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return true;
}

void CreateList_L(LinkList& L, int n) {
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;

	LinkList p = (LinkList)malloc(sizeof(LNode));
	p->data = n;
	p->next = L->next;
	L->next = p;

}

int insertList(SqLinerList& L, int i, int e) {
	if (i < 1 || i > L.length + 1) return -1;
	if (L.length >= L.listsize) {
		int* newbase = (int*)realloc(L.elem,
			(L.listsize + 10) * sizeof(int));
		if (!newbase)return -2;
		L.elem = newbase;
		L.listsize += 10;
	}
	int* q = &(L.elem[i - 1]);
	for (int* p = &(L.elem[L.length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++L.length;
	return e;
}

int ListInsert_L(LinkList& L, int i, int e) {
	LinkList p = L;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!p || j > i - 1) return -1;
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return e;
}

int deleteListElem(SqLinerList& L, int i) {
	if (i < 1 || i > L.length) return -1;
	int* p = &(L.elem[i - 1]);
	int& e = *p;
	int* q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L.length;
	return e;
}

int ListDelete_L(LinkList& L, int i) {
	LinkList p = L;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!p || j > i - 1) return -1;
	LinkList q = p->next;
	p->next = q->next;
	int e = q->data;
	free(q);
	return e;
}

void mergeList(SqLinerList La, SqLinerList Lb, SqLinerList& Lc) {
	int* pa = La.elem;
	int* pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	int* pc = Lc.elem = (int*)malloc(Lc.listsize * sizeof(int));
	if (!Lc.elem)exit(-2);
	int* pa_last = La.elem + La.length - 1;
	int* pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa <= *pb) *pc++ = *pa++;
		else *pc++ = *pb++;
	}
	while (pa <= pa_last) *pc++ = *pa++;
	while (pb <= pb_last) *pc++ = *pb++;
}

void mergeList_Link(LinkList& La, LinkList& Lb, LinkList& Lc) {
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc;
	Lc = pc = La;
	while (pa && pb) {
		if (pa->data <= pb->data) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
		pc->next = pa ? pa : pb;
		free(Lb);
	}
}

int main()
{
	SqLinerList l;
	SqLinerList l2;
	SqLinerList Lmerged;
	initList(l);
	initList(l2);
	initList(Lmerged);
	for (int i = 1; i < 10; i++) {
		insertList(l, i, i);
	}
	for (int i = 1; i < 10; i++) {
		insertList(l2, i, 10 - i);
	}
	printf("删除第五个元素\n");
	deleteListElem(l, 5);
	for (int i = 0; i < l.length; i++) {
		printf("%d\n", l.elem[i]);
	}
	mergeList(l, l2, Lmerged);
	printf("\n合成后\n");
	for (int i = 0; i < Lmerged.length; i++) {
		printf("%d\n", Lmerged.elem[i]);
	}
	std::cin.ignore();
	std::cin.get();
	return 0;
}

