# include <stdio.h>
# include <stdlib.h>

struct Stack {
	int id;
	int time;
	struct Stack *pre;
	struct Stack *next;
};//����һ��ջ���泵����Ϣ

struct Queue {
	int id;
	struct Queue *next;
};//����һ�����б���ͣ�ڱ���ĳ���id��������Ϣ����Ҫ

struct Stack *head1, *end1;
struct Stack *head2, *end2; //��������ջ��ͷβָ��
struct Queue *head, *end; //���е�ͷβָ��
int stack1count, stack2count;
int queuecount;//Ԫ������

void Push(int flag, struct Stack *p) {
	struct Stack *temp;
	if (flag == 0) { //ջ1��ջ
		if (stack1count == 0) {
			head1 = (struct Stack *)malloc(sizeof(struct Stack));
			head1->id = p->id;
			head1->time = p->time;
			head1->next = NULL;
			head1->pre = NULL;
			end1 = head1;
		}//ͷβָ����Ȳ�һ��ָ���һ��Ԫ��
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
	}//βָ�����
	else if (flag == 1) { //ջ2��ջ
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
	}//�������ĳ�����Ŀ�공ʱ����ȡ��
	else {
		temp->id = end1->id;
		temp->time = end1->time;
		temp->pre = end1->pre;
		printf("%d��������ͣ����\n", id);
		printf("ͣ����ͣ��ʱ��: %d\n", time - temp->time);
		printf("Ӧ���ɵķ���Ϊ������5����%d\n", 5 * (time - temp->time));
		free(end1);
		if (--stack1count == 0) {
			end1 = head1 = NULL;
		} else {
			end1 = temp->pre;
			end->next = NULL;
		}
		temp = NULL;
	}//�������ĳ���Ŀ�공��ֱ�Ӱ��ո�ʽ���������tempΪ0
	return temp;//��Ϊ����ֵ��������Ŀ�공�Ƿ����ջ2
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
}//ջ2�еĳ���ջ��ջ2��һ����ʱջ��

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
}//��ջ��ʱ��������

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
}//����ĳ�����

int main() {
	int n;
	char s;
	struct Stack *p;

	printf("����ͣ������ͣ����������: ");
	scanf("%d", &n);
	getchar();
	stack1count = stack2count = queuecount = 0;
	p = (struct Stack *)malloc(sizeof(struct Stack));

	while (scanf("(%c,%d,%d)", &s, &p->id, &p->time) != EOF) {
		getchar();
		if (s == 'E')
			break;
		else if (s == 'A') {              /*��������*/
			if (stack1count < n) {               /*ջδ������ջ����*/
				Push(0, p);
				printf("%d����������ͣ����\n", end1->id);
				printf("����ͣ����ʱ��: %d\n", end1->time);
				printf("ͣ��λ��: %d\n", stack1count);
			} else {                            /*ջ���������в���*/
				enQueue(p);
				printf("%d������������\n", p->id);
				printf("������ʱ��: %d\n", p->time);
				printf("���λ��: %d\n", queuecount);
			}
		} else if (s == 'D') {            /*������ȥ*/
			struct Stack *temp;
			while ((temp = Pops1(p->id, p->time)) != NULL) {
				Push(1, temp);
			}//��ջ1��Ϊ����·���������Ƚ�ջ2
			while (stack2count != 0) {
				Push(0, Pops2());
			}//Ŀ�공��ջ��֮ǰ�ĳ���ջ
			if (queuecount != 0) {//����ڵĳ����ӽ�ջ
				Push(0, deQueue(p->time));
				printf("%d����������ͣ����\n", end1->id);
				printf("����ʱ��: %d\n", end1->time);
				printf("ͣ��λ��: %d\n", stack1count);
			}
		}
	}
	return 0;
}