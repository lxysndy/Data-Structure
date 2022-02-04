//ջ�ĸ��ֲ���ʵ��
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MaxSize 100

typedef struct {
	int data[MaxSize];
	int top;
} SqStack;

void InitStack(SqStack *&s) {
	s = (SqStack *)malloc(sizeof(SqStack));
	s->top = -1;
}

void DestroyStack(SqStack *&s) {
	free(s);
}

bool StackEmpty(SqStack *&s) {
	return (s->top == -1);
}

bool Push(SqStack *&s, int &e) {
	if (s->top == MaxSize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack *&s, int &e) {
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

bool GetTop(SqStack *s, int &e) {
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

int StackLength(SqStack *s) {
	return s->top + 1;
}

int main() {
	SqStack *s;
	InitStack(s);
	int i, k;
	if (StackEmpty(s))
		printf("ջ��\n");
	else
		printf("ջ����\n");

	printf("������ʮ�������ڲ��ԣ�\n");
	for (int j = 0; j < 10; j++) {
		scanf("%d", &i);
		Push(s, i);
	}
	i = 0;
	if (StackEmpty(s))
		printf("��ʱջ��\n");
	else
		printf("��ʱջ����\n");

	if (GetTop(s, k))
		printf("ջ��Ԫ�أ�%d\n", k);
	else
		printf("���ִ���\n");

	int n;
	int len = StackLength(s);
	printf("ջ����%d", len);
	printf("\n��Ҫ��ջԪ�ظ�����С��10����");
	scanf("%d", &n);
	int g;
	for (int j = 1; j <= n; j++) {
		Pop(s, g);
	}
	printf("��ʱջΪ��");
	for (int i = s->top ; i >= 0; i--) {
		printf("%d ", s->data[i]);
	}
	DestroyStack(s);
	return 0;
}