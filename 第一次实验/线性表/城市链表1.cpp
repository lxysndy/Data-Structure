#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ERROR 0
#define OK 1

typedef struct lnote {     //��������ṹ�ڵ�
	float x;
	float y;
	char name[100];
	struct lnote *next;
} *node, NODE;

typedef struct LIST {        //��������ṹ
	node head;
	node tail;
	int len;
} list;//����������ܱ�

void CreateList(list *p);                            //�������Ա�
void InsertNode(list *p, char *a, float x, float y);   //��ӽڵ�
void GetPosition(list p, char *a);                     //���ҽڵ�
void SearchCity(float p_x, float p_y, float d, list p); //���������ҳ���

int main() {
	FILE *data;           //�ļ�֮��
	list city;
	int sum;
	char judge;
	CreateList(&city);
	printf("'��������.txt.'�ļ��Ѵ����Ҹ�ʽ���£�\n���� ����\n");
	printf("�Ƿ����?(Y/N)\n");
	scanf("%c", &judge);
	while (judge != 'Y' && judge != 'y') {
		printf("�뽫���ݷ����ļ�'��������.txt.'\n");
		printf("�Ƿ����?(Y/N)");
		getchar();
		scanf("%c", &judge);
	}
	if ((data = fopen("��������.txt", "rt")) == NULL) {
		exit(-1);
	}
	char a[50];
	for (; (fscanf(data, "%s", a)) != EOF;) {//fscanf��ȡtxt�ļ�
		float x, y;
		fscanf(data, "%f %f", &x, &y);
		InsertNode(&city, a, x, y);
		memset(a, 0, sizeof(a));
	}
	int select;
	printf("\n�˵�����:\n");
	printf("1.�ɳ�������������\n");
	printf("2.��������;��������س���\n");
	printf("3.�˳�ϵͳ\n");
	do {
		printf("\n��ѡ��:");
		scanf("%d", &select);
		switch (select) {
			case 1:
				getchar();
				char a[30];
				printf("\n�������������");
				scanf("%s", &a[0]);
				GetPosition(city, a);
				break;
			case 2:
				float x, y, r;
				printf("���������꣺����120 50��\n");
				scanf("%f %f", &x, &y);
				printf("��������룺\n");
				scanf("%f", &r);
				SearchCity(x, y, r, city);
				break;
			case 3:
				return 0;
			default:
				do {
					printf("���������������������룡\n");
					break;
				} while (0);
		}
	} while (1);
	return 0;
}

void CreateList(list *p) {                         //�������Ա�
	p->head = (node)malloc(sizeof(NODE));
	if (!p->head) {
		exit(ERROR);
	}
	p->head->next = NULL;
	p->tail = p->head;
	p->len = 0;
}

void InsertNode(list *p, char *a, float X, float Y) { //��ӽڵ�
	node q;
	q = (node)malloc(sizeof(NODE));
	q->x = X;
	q->y = Y;
	strcpy(q->name, a);
	q->next = NULL;
	p->tail->next = q;
	p->tail = q;
	p->len++;
}

void GetPosition(list p, char *a) {             //���ҽڵ�
	node q;
	q = p.head->next;
	for (int i = 0; ++i <= p.len; q = q->next) {
		if (!strcmp(q->name, a)) {//�ɹ�ƥ�亯��ֵΪ0
			printf("λ�ã�γ�� ���ȣ���%f %f", q->x, q->y);
			break;
		}
	}
	if (!q) {
		printf("��");
	}
}

void SearchCity(float p_x, float p_y, float d, list p) { //���������ҳ���
	node q;
	int judge = ERROR;
	q = p.head->next;
	for (int i = 0; ++i <= p.len; q = q->next) {
		if (((q->x - p_x) * (q->x - p_x) + (q->y - p_y) * (q->y - p_y) - d * d) <= 0) { //����������֮�����С�ڸ�������
			judge = OK;
			printf("%s ", q->name);
		}
	}
	if (!judge) {
		printf("��");
	}
}