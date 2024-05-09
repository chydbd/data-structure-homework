#include <iostream>

typedef struct {
    char* ch;
    int length;
}HString;

int StrInsert(HString& S, int pos, HString T) {
    if (pos<1 || pos>S.length + 1) return 0;
    if (T.length) {
        if (!(S.ch = (char*)realloc(S.ch, (S.length + T.length) * sizeof(char))))
            exit(-2);
        for (int i = S.length - 1;i >= pos - 1;--i)
            S.ch[i + T.length] = S.ch[i];
        for (int i = 0; i < T.length; i++) {
            S.ch[pos - 1 + i] = T.ch[i];
        }
        S.length += T.length;
    }
    return 1;
}

int StrAssign(HString& T, char* chars) {
    int i;char* c;
    if (T.ch) free(T.ch);
    for (i = 0, c = chars;*c;++i, ++c);
    if (!i) {
        T.ch = NULL;
        T.length = 0;
    }
    else {
        if (!(T.ch = (char*)malloc(i * sizeof(char))))
            exit(-2);
        for (int j = 0;j < i;j++) {
            T.ch[j] = chars[j];
        }
        T.length = i;
    }
    return 1;
}

int StrCompare(HString S, HString T) {
    for (int i = 0;i < S.length && i < T.length;++i)
        if (S.ch[i] != T.ch[i])return S.ch[i] - T.ch[i];
    return S.length - T.length;
}

int ClearString(HString& S) {
    if (S.ch) {
        free(S.ch);
        S.ch = NULL;
    }
    S.length = 0;
    return 1;
}

int Concat(HString& T, HString S1, HString S2) {
    if (T.ch) free(T.ch);
    if (!(T.ch = (char*)malloc((S1.length + S2.length) * sizeof(char))))exit(-2);
    for (int i = 0;i < S1.length;i++) {
        T.ch[i] = S1.ch[i];
    }
    T.length = S1.length + S2.length;
    for (int i = 0;i < S2.length;i++) {
        T.ch[S1.length + i] = S2.ch[i];
    }
    return 1;
}

int SubString(HString& Sub, HString S, int pos, int len) {
    if (pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)return 0;
    if (Sub.ch)free(Sub.ch);
    if (!len) {
        Sub.ch = NULL;
        Sub.length = 0;
    }
    else {
        Sub.ch = (char*)malloc(len * sizeof(char));
        for (int i = 0;i < len;i++) {
            Sub[i] = S.ch[pos - 1 + i];
        }
        Sub.length = len;
    }
    return 1;
}

int main()
{
    std::cout << "Hello World!\n";
}

