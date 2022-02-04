#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Max_size 100
//使用类似头插建立双向链表后要注意，基本上的逻辑都是反过来的！！

/*测试样例
输入: 0; 0; 输出: 0
输入: -2345,6789; -7654,3211; 输出:-1,0000,0000
输入: -9999,9999; 1,0000,0000,0000; 输出: 9999,0000,0001
输入: 1,0001,0001; -1,0001,0001;  输出:0
输入： 1,0001,0001; -1,0000,0000;  输出:1
*/

//利用双向循环链表实现长整数的存储
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
	printf("输入第一个数（每四位用逗号隔开并在最后加上分号）: ");
	Readnumber(&L1);
	int len1 = Length(L1);
	printf("\n输入第二个数（每四位用逗号隔开并在最后加上分号）: ");
	Readnumber(&L2);
	int len2 = Length(L2);
	DoubleList L3 = InitList();
	printf("\n相加结果: ");
	int sign = Operation(L1, L2, &L3);
	if (sign == -1)
		printf("%c", '-');
	Print(L3);
	return 0;

}

//建立一个带有头结点的空循环双链表
DoubleList InitList() {
	DoubleList L = (DoubleList)malloc(sizeof(DoubleNode));
	L->prior = L;
	L->next = L;
	return L;
}

//插入结点时，让链表的高位在链表的尾部，低位在链表的头部，相当于头插
void Insert(DoubleList *L, int number) {
	DoubleNode *p = (DoubleNode *)malloc(sizeof(DoubleNode));
	p->data = number;
	p->next = (*L)->next;
	(*L)->next->prior = p;
	(*L)->next = p;
	p->prior = *L;
}

//读取输入的整数，每四个数字存放在一个节点中
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

//求表长
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

//将链表中对应结点的绝对值相加，先低后高
void Add(DoubleList L1, DoubleList L2, DoubleList *L3) {
	DoubleNode *p = L1->next, *q = L2->next;
	int res, carry = 0;//注意进位
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
	if (p == L1 && q != L2) {//p等于L1表示L1高位为空
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
	if (p != L1 && q == L2) {//与上相仿
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
	if (carry == 1) //最后最高位的进位有1则在头结点之后插入一个新结点
		Insert(L3, 1);
}

//比较两个链表中存储数据的绝对值的大小
//返回值为1: L1>L2  返回值为0: L1=L2  返回值为-1: L1<L2
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

//相减时，保证L1>=L2
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

//加法共有四种情况：正数加正数，正数加负数，负数加负数，负数加正数
int  Operation(DoubleList L1, DoubleList L2, DoubleList *L3) {
	if (L1->data == 1 && L2->data == 1) {//两正
		Add(L1, L2, L3);
		(*L3)->data = 1;
		return 1;
	} else if (L1->data == -1 && L2->data == -1) {//两负
		Add(L1, L2, L3);
		(*L3)->data = -1;
		return -1;
	} else if (L1->data == 1 && L2->data == -1) {
		if (Size(L1, L2) == 1) {//最终结果大于0
			Minus(L1, L2, L3);
			(*L3)->data = 1;
			return 1;
		} else if (Size(L1, L2) == -1) {//小于0
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

//从表头开始输出
void Print(DoubleList L) {
	DoubleNode *p = L->next;
	while (p->data == 0 && p->next != L)
		p = p->next;
	if (p->next == L) {
		printf("%d", p->data);
		return;
	}//p所指为最高位
	printf("%d", p->data);
	while (p->next != L) {//不是最高位
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