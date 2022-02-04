# include <stdio.h>
# include <stdlib.h>
# define MaxSize 50
//����

typedef struct LNode {
	int data;
	struct LNode *next;
} LinkNode;

void CreateListR(LinkNode *&L, int a[], int n) {
	LinkNode *s, *r;
	L = (LinkNode *)malloc(sizeof(LinkNode));
	r = L;
	for (int i = 0; i < n; i++) {
		s = (LinkNode *)malloc(sizeof(LinkNode));
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = NULL;
}//β�巨

void InitList(LinkNode *&L) {
	L = (LinkNode *)malloc(sizeof(LinkNode));
	L->next = NULL;
} //��ʼ��

void DestroyList(LinkNode *&L) {
	LinkNode *pre = L, *p = L->next;
	while (p != NULL) {
		free(pre);
		pre = p;
		p->next;
	}
	free(pre);
}//�������Ա�

void DispList(LinkNode *L) {
	LinkNode *p = L->next;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
} //���

int GetElem(LinkNode *L, int i) {
	int e;
	int j;
	LinkNode *p = L;
	if (i <= 0)
		return 0;
	while (j < i && p != NULL) {
		j++;
		p = p->next;
	}
	if (p == NULL) {
		return 0;
	} else {
		e = p->data;
	}
	return e;
} //��ĳ��Ԫ��ֵ

int LocateElem(LinkNode *L, int e) {
	int i = 1;
	LinkNode *p = L->next;
	while (p != NULL && p->data != e) {
		p = p->next;
		i++;
	}
	if (p == NULL) {
		return 0;
	} else
		return i;
}//��Ԫ��ֵ����

bool ListInsert(LinkNode *&L, int e, int i) {
	int j = 0;
	LinkNode *p = L, *s;
	if (i <= 0)
		return false;
	while (j < i - 1 && p != NULL) {
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else {
		s = (LinkNode *)malloc(sizeof(LinkNode));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return true;
	}
}//��������Ԫ��

bool ListDelete(LinkNode *&L, int &e, int i) {
	int j = 0;
	LinkNode *p = L, *q;
	if (i <= 0)
		return false;
	while (j < i - 1 && p != NULL) {
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else {
		q = p->next;
		if (q == NULL)
			return false;
		e = q->data;
		p->next = q->next;
		free(q);
		return true;
	}
}//ɾ������Ԫ��

int main() {
	LinkNode *test;
	InitList(test);
	printf("�����˵���\n");
	printf("            		1.β�彨��������\n");
	printf("			2.������\n");
	printf("			3.ɾ�����\n");
	printf("			4.��Ԫ��ֵ����\n");
	printf("			5.��ָ��λ��Ԫ��ֵ\n");
	printf("			6.��ӡ����\n");
	printf("			7.���������˳�\n");
	do {
		printf("��ѡ���ܣ�\n");
		int i, j, k, s[MaxSize], t, a, b, c, d, e, f;
		scanf("%d", &i);
		switch (i) {
			case 1:
				printf("�����뵥��������Ҫ��Ԫ�ظ�����\n");
				scanf("%d", &t);
				printf("����������Ԫ�أ�\n");
				for (int u = 0; u < t; u++) {
					scanf("%d", &s[u]);
				}
				CreateListR(test, s, t);
				break;
			case 2:
				printf("������Ҫ����Ľ��ֵ�Լ�λ�ã�\n");
				scanf("%d%d", &j, &k);
				if (ListInsert(test, j, k))
					printf("���\n");
				else
					printf("�������ݲ�����Ҫ��\n");
				break;
			case 3:
				printf("������Ҫɾ���Ľ��ֵ�Լ�λ�ã�\n");
				scanf("%d%d", &a, &b);
				if (ListDelete(test, a, b))
					printf("���\n");
				else
					printf("�������ݲ�����Ҫ��\n");
				break;
			case 4:
				printf("������Ҫ���ҵ�Ԫ��ֵ:\n");
				scanf("%d", &c);
				d = LocateElem(test, c);
				printf("λ��Ϊ��%d\n", d);
				break;
			case 5:
				printf("������Ԫ������λ�ã�\n");
				scanf("%d", &f);
				e = GetElem(test, f);
				printf("Ԫ��ֵ��%d\n", e);
				break;
			case 6:
				printf("���Ա����£�\n");
				DispList(test);
				break;
			case 7:
				DestroyList(test);
				printf("���ٳɹ���");
				break;
		}
	} while (1);
	return 0;
}
