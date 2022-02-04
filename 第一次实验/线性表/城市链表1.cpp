#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ERROR 0
#define OK 1

typedef struct lnote {     //城市链表结构节点
	float x;
	float y;
	char name[100];
	struct lnote *next;
} *node, NODE;

typedef struct LIST {        //城市链表结构
	node head;
	node tail;
	int len;
} list;//城市链表的总表

void CreateList(list *p);                            //创建线性表
void InsertNode(list *p, char *a, float x, float y);   //添加节点
void GetPosition(list p, char *a);                     //查找节点
void SearchCity(float p_x, float p_y, float d, list p); //给定坐标找城市

int main() {
	FILE *data;           //文件之间
	list city;
	int sum;
	char judge;
	CreateList(&city);
	printf("'城市链表.txt.'文件已存在且格式如下：\n名称 坐标\n");
	printf("是否放入?(Y/N)\n");
	scanf("%c", &judge);
	while (judge != 'Y' && judge != 'y') {
		printf("请将数据放入文件'城市链表.txt.'\n");
		printf("是否放入?(Y/N)");
		getchar();
		scanf("%c", &judge);
	}
	if ((data = fopen("城市链表.txt", "rt")) == NULL) {
		exit(-1);
	}
	char a[50];
	for (; (fscanf(data, "%s", a)) != EOF;) {//fscanf读取txt文件
		float x, y;
		fscanf(data, "%f %f", &x, &y);
		InsertNode(&city, a, x, y);
		memset(a, 0, sizeof(a));
	}
	int select;
	printf("\n菜单索引:\n");
	printf("1.由城市名查找坐标\n");
	printf("2.给定坐标和距离查找相关城市\n");
	printf("3.退出系统\n");
	do {
		printf("\n请选择:");
		scanf("%d", &select);
		switch (select) {
			case 1:
				getchar();
				char a[30];
				printf("\n请输入城市名：");
				scanf("%s", &a[0]);
				GetPosition(city, a);
				break;
			case 2:
				float x, y, r;
				printf("请输入坐标：（如120 50）\n");
				scanf("%f %f", &x, &y);
				printf("请输入距离：\n");
				scanf("%f", &r);
				SearchCity(x, y, r, city);
				break;
			case 3:
				return 0;
			default:
				do {
					printf("您的输入有误，请重新输入！\n");
					break;
				} while (0);
		}
	} while (1);
	return 0;
}

void CreateList(list *p) {                         //创建线性表
	p->head = (node)malloc(sizeof(NODE));
	if (!p->head) {
		exit(ERROR);
	}
	p->head->next = NULL;
	p->tail = p->head;
	p->len = 0;
}

void InsertNode(list *p, char *a, float X, float Y) { //添加节点
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

void GetPosition(list p, char *a) {             //查找节点
	node q;
	q = p.head->next;
	for (int i = 0; ++i <= p.len; q = q->next) {
		if (!strcmp(q->name, a)) {//成功匹配函数值为0
			printf("位置（纬度 经度）：%f %f", q->x, q->y);
			break;
		}
	}
	if (!q) {
		printf("无");
	}
}

void SearchCity(float p_x, float p_y, float d, list p) { //给定坐标找城市
	node q;
	int judge = ERROR;
	q = p.head->next;
	for (int i = 0; ++i <= p.len; q = q->next) {
		if (((q->x - p_x) * (q->x - p_x) + (q->y - p_y) * (q->y - p_y) - d * d) <= 0) { //城市与坐标之间距离小于给定距离
			judge = OK;
			printf("%s ", q->name);
		}
	}
	if (!judge) {
		printf("无");
	}
}