#include <cstdlib>
#include <cstdio>
#include <iostream>

#define LIST_INIT_SIZE 10

typedef struct {
	int* elem;
	int length;
	int listsize;
}SqList;

bool initList(SqList& L) {
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem)return false;
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return true;
}

int insertList(SqList& L, int i, int e) {
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

int deleteListElem(SqList& L, int i) {
	if (i < 1 || i > L.length) return -1;
	int* p = &(L.elem[i - 1]);
	int& e = *p;
	int* q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L.length;
	return e;
}

void mergeList(SqList La, SqList Lb, SqList& Lc) {
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
int main()
{
	SqList l;
	SqList l2;
	SqList Lmerged;
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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
