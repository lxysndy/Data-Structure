#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Max_size 100
//ʹ������ͷ�彨��˫�������Ҫע�⣬�����ϵ��߼����Ƿ������ģ���

/*��������
����: 0; 0; ���: 0
����: -2345,6789; -7654,3211; ���:-1,0000,0000
����: -9999,9999; 1,0000,0000,0000; ���: 9999,0000,0001
����: 1,0001,0001; -1,0001,0001;  ���:0
���룺 1,0001,0001; -1,0000,0000;  ���:1
*/

//����˫��ѭ������ʵ�ֳ������Ĵ洢
typedef struct Node {
	int data;
	struct Node *prior;
	struct Node *next;
} DoubleNode, *DoubleList;

DoubleList InitList();
void Insert(DoubleList *L, int number);
void Readnumber(DoubleList *L);
int Length(DoubleList L);
void Add(DoubleList L1, DoubleList L2, DoubleList *L3);
void Minus(DoubleList L1, DoubleList L2, DoubleList *L3);
int Operation(DoubleList L1, DoubleList L2, DoubleList *L3);
int Size(DoubleList L1, DoubleList L2);
void Print(DoubleList L);

int main(void) {
	DoubleList L1 = InitList();
	DoubleList L2 = InitList();
	printf("�����һ������ÿ��λ�ö��Ÿ������������Ϸֺţ�: ");
	Readnumber(&L1);
	int len1 = Length(L1);
	printf("\n����ڶ�������ÿ��λ�ö��Ÿ������������Ϸֺţ�: ");
	Readnumber(&L2);
	int len2 = Length(L2);
	DoubleList L3 = InitList();
	printf("\n��ӽ��: ");
	int sign = Operation(L1, L2, &L3);
	if (sign == -1)
		printf("%c", '-');
	Print(L3);
	return 0;

}

//����һ������ͷ���Ŀ�ѭ��˫����
DoubleList InitList() {
	DoubleList L = (DoubleList)malloc(sizeof(DoubleNode));
	L->prior = L;
	L->next = L;
	return L;
}

//������ʱ��������ĸ�λ�������β������λ�������ͷ�����൱��ͷ��
void Insert(DoubleList *L, int number) {
	DoubleNode *p = (DoubleNode *)malloc(sizeof(DoubleNode));
	p->data = number;
	p->next = (*L)->next;
	(*L)->next->prior = p;
	(*L)->next = p;
	p->prior = *L;
}

//��ȡ�����������ÿ�ĸ����ִ����һ���ڵ���
void Readnumber(DoubleList *L) {
	int number, i = 0;
	char c;
	scanf("%d%c", &number, &c);
	while (1) {
		if (number < 0 && i == 0) {
			(*L)->data = -1;
			number = abs(number);
			Insert(L, number);
		} else if (number >= 0 && i == 0) {
			(*L)->data = 1;
			Insert(L, number);
		} else if (number >= 0 && i != 0)
			Insert(L, number);
		if (c == ';') {
			i++;
			break;
		}
		scanf("%d%c", &number, &c);
		i++;
	}
}

//���
int Length(DoubleList L) {
	if (L == NULL || (L->next == L && L->prior == L))
		return 0;
	DoubleNode *p = L->next;
	int count = 0;
	while (p != L) {
		count++;
		p = p->next;
	}
	return count;
}

//�������ж�Ӧ���ľ���ֵ��ӣ��ȵͺ��
void Add(DoubleList L1, DoubleList L2, DoubleList *L3) {
	DoubleNode *p = L1->next, *q = L2->next;
	int res, carry = 0;//ע���λ
	while (p != L1 && q != L2) {
		res = p->data + q->data + carry;
		if (res >= 10000) {
			res = res % 10000;
			carry = 1;
		} else
			carry = 0;
		Insert(L3, res);
		p = p->next;
		q = q->next;
	}
	if (p == L1 && q != L2) {//p����L1��ʾL1��λΪ��
		while (q != L2) {
			res = q->data + carry;
			if (res >= 10000) {
				res = res % 10000;
				carry = 1;
			} else
				carry = 0;
			Insert(L3, res);
			q = q->next;
		}
	}
	if (p != L1 && q == L2) {//�������
		while (p != L1) {
			res = p->data + carry;
			if (res >= 10000) {
				res = res % 10000;
				carry = 1;
			} else
				carry = 0;
			Insert(L3, res);
			p = p->next;
		}
	}
	if (carry == 1) //������λ�Ľ�λ��1����ͷ���֮�����һ���½��
		Insert(L3, 1);
}

//�Ƚ����������д洢���ݵľ���ֵ�Ĵ�С
//����ֵΪ1: L1>L2  ����ֵΪ0: L1=L2  ����ֵΪ-1: L1<L2
int Size(DoubleList L1, DoubleList L2) {
	DoubleNode *p = L1->next;
	DoubleNode *q = L2->next;
	int len1 = Length(L1);
	int len2 = Length(L2);
	if (len1 > len2)
		return 1;
	if (len1 < len2)
		return -1;
	//len1==len2
	while (p != L1 && q != L2) {
		if (p->data > q->data)
			return 1;
		if (p->data < q->data)
			return -1;
		p = p->next;
		q = q->next;
	}
	return 0;
}

//���ʱ����֤L1>=L2
void Minus(DoubleList L1, DoubleList L2, DoubleList *L3) {
	DoubleNode *p = L1->next, *q = L2->next;
	int res, borrow = 0;
	while (p != L1 && q != L2) {
		p->data = p->data + borrow;
		if (p->data >= q->data) {
			res = p->data - q->data;
			borrow = 0;
		} else {
			res = p->data + 10000 - q->data;
			borrow = -1;
		}
		Insert(L3, res);
		p = p->next;
		q = q->next;
	}
	if (p != L1 && q == L2) {

		while (p != L1) {
			p->data = p->data + borrow;
			if (p->data < 0) {
				res = p->data + 10000;
				borrow = -1;
				Insert(L3, res);
				p = p->next;
			}
			if (p->data == 0)
				return;
		}
	}
}

//�ӷ�������������������������������Ӹ����������Ӹ���������������
int  Operation(DoubleList L1, DoubleList L2, DoubleList *L3) {
	if (L1->data == 1 && L2->data == 1) {//����
		Add(L1, L2, L3);
		(*L3)->data = 1;
		return 1;
	} else if (L1->data == -1 && L2->data == -1) {//����
		Add(L1, L2, L3);
		(*L3)->data = -1;
		return -1;
	} else if (L1->data == 1 && L2->data == -1) {
		if (Size(L1, L2) == 1) {//���ս������0
			Minus(L1, L2, L3);
			(*L3)->data = 1;
			return 1;
		} else if (Size(L1, L2) == -1) {//С��0
			Minus(L2, L1, L3);
			(*L3)->data = -1;
			return -1;
		}
		Insert(L3, 0);
		return 1;
	} else if (L1->data == -1 && L2->data == 1) {
		if (Size(L1, L2) == 1) {
			Minus(L1, L2, L3);
			(*L3)->data = -1;
			return -1;
		} else if (Size(L1, L2) == -1) {
			Minus(L2, L1, L3);
			(*L3)->data = 1;
			return 1;
		}
		Insert(L3, 0);
		return 1;
	}
}

//�ӱ�ͷ��ʼ���
void Print(DoubleList L) {
	DoubleNode *p = L->next;
	while (p->data == 0 && p->next != L)
		p = p->next;
	if (p->next == L) {
		printf("%d", p->data);
		return;
	}//p��ָΪ���λ
	printf("%d", p->data);
	while (p->next != L) {//�������λ
		p = p->next;
		if (p->data < 10)
			printf(",000%d", p->data);
		else if (p->data < 100)
			printf(",00%d", p->data);
		else if (p->data < 1000)
			printf(",0d", p->data);
		else
			printf(",%d", p->data);
	}
}