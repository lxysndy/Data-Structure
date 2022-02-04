# include <stdio.h>
# include <stdlib.h>

struct Stack {
	int id;
	int time;
	struct Stack *pre;
	struct Stack *next;
};//建立一个栈保存车的信息

struct Queue {
	int id;
	struct Queue *next;
};//建立一个队列保存停在便道的车的id，其余信息不需要

struct Stack *head1, *end1;
struct Stack *head2, *end2; //建立两个栈的头尾指针
struct Queue *head, *end; //队列的头尾指针
int stack1count, stack2count;
int queuecount;//元素总数

void Push(int flag, struct Stack *p) {
	struct Stack *temp;
	if (flag == 0) { //栈1进栈
		if (stack1count == 0) {
			head1 = (struct Stack *)malloc(sizeof(struct Stack));
			head1->id = p->id;
			head1->time = p->time;
			head1->next = NULL;
			head1->pre = NULL;
			end1 = head1;
		}//头尾指针相等并一起指向第一个元素
		else {
			temp = (struct Stack *)malloc(sizeof(struct Stack));
			temp->id = p->id;
			temp->time = p->time;
			end1->next = temp;
			temp->pre = end1;
			temp->next = NULL;
			end1 = temp;
		}
		stack1count++;
	}//尾指针后移
	else if (flag == 1) { //栈2进栈
		if (stack2count == 0) {
			head2 = (struct Stack *)malloc(sizeof(struct Stack));
			head2->id = p->id;
			head2->time = p->time;
			head2->next = NULL;
			head2->pre = NULL;
			end2 = head2;
		} else {
			temp = (struct Stack *)malloc(sizeof(struct Stack));
			temp->id = p->id;
			temp->time = p->time;
			end2->next = temp;
			temp->pre = end2;
			temp->next = NULL;
			end2 = temp;
		}
		stack2count++;
	}
}

struct Stack *Pops1(int id, int time) {
	struct Stack *temp;
	temp = (struct Stack *)malloc(sizeof(struct Stack));

	if (end1->id != id) {
		temp->id = end1->id;
		temp->time = end1->time;
		temp->pre = end1->pre;
		free(end1);
		end1 = temp->pre;
		end1->next = NULL;
		stack1count--;
	}//当出来的车不是目标车时，先取出
	else {
		temp->id = end1->id;
		temp->time = end1->time;
		temp->pre = end1->pre;
		printf("%d号汽车出停车场\n", id);
		printf("停车场停留时间: %d\n", time - temp->time);
		printf("应缴纳的费用为（单价5）：%d\n", 5 * (time - temp->time));
		free(end1);
		if (--stack1count == 0) {
			end1 = head1 = NULL;
		} else {
			end1 = temp->pre;
			end->next = NULL;
		}
		temp = NULL;
	}//当出来的车是目标车，直接按照格式输出，并置temp为0
	return temp;//作为返回值，当不是目标车是方便进栈2
}

struct Stack *Pops2() {
	struct Stack *temp;
	temp = (struct Stack *)malloc(sizeof(struct Stack));

	temp->id = end2->id;
	temp->time = end2->time;
	temp->pre = end2->pre;
	free(end2);
	end2 = temp->pre;
	stack2count--;
	return temp;
}//栈2中的车出栈（栈2是一个临时栈）

void enQueue(struct Stack *p) {
	struct Queue *qtemp;
	if (queuecount == 0) {
		head = (struct Queue *)malloc(sizeof(struct Queue));
		head->id = p->id;
		head->next = NULL;
		end = head;
	} else {
		qtemp = (struct Queue *)malloc(sizeof(struct Queue));
		qtemp->id = p->id;
		qtemp->next = NULL;
		end->next = qtemp;
		end = qtemp;
	}
	queuecount++;
}//当栈满时车进入便道

struct Stack *deQueue(int time) {
	struct Stack *temp;
	temp = (struct Stack *)malloc(sizeof(struct Stack));
	temp->id = head->id;
	temp->time = time;
	if (--queuecount == 0) {
		head = NULL;
		end = NULL;
	} else {
		head = head->next;
	}
	return temp;
}//便道的车出队

int main() {
	int n;
	char s;
	struct Stack *p;

	printf("输入停车场可停放汽车数量: ");
	scanf("%d", &n);
	getchar();
	stack1count = stack2count = queuecount = 0;
	p = (struct Stack *)malloc(sizeof(struct Stack));

	while (scanf("(%c,%d,%d)", &s, &p->id, &p->time) != EOF) {
		getchar();
		if (s == 'E')
			break;
		else if (s == 'A') {              /*汽车到达*/
			if (stack1count < n) {               /*栈未满，进栈操作*/
				Push(0, p);
				printf("%d号汽车进入停车场\n", end1->id);
				printf("进入停车场时间: %d\n", end1->time);
				printf("停车位置: %d\n", stack1count);
			} else {                            /*栈满，进队列操作*/
				enQueue(p);
				printf("%d号汽车进入便道\n", p->id);
				printf("进入便道时间: %d\n", p->time);
				printf("便道位置: %d\n", queuecount);
			}
		} else if (s == 'D') {            /*汽车离去*/
			struct Stack *temp;
			while ((temp = Pops1(p->id, p->time)) != NULL) {
				Push(1, temp);
			}//让栈1内为车让路的其他车先进栈2
			while (stack2count != 0) {
				Push(0, Pops2());
			}//目标车出栈后之前的车进栈
			if (queuecount != 0) {//便道内的车出队进栈
				Push(0, deQueue(p->time));
				printf("%d号汽车进入停车场\n", end1->id);
				printf("进入时间: %d\n", end1->time);
				printf("停车位置: %d\n", stack1count);
			}
		}
	}
	return 0;
}