//ͼ�Ľ����ͱ���
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*��������������5 8
  ������5 
���Ծ���0 1 0 1 1
			1 0 1 1 0
			0 1 0 1 1
			1 1 1 0 1
			1 0 1 1 0*/ 
#define MAXV 100 
#define INF 9999
#define MaxSize 100
typedef struct ANode{
	int adjvex;//�ڽӵ�
	struct ANode *nextarc;//ָ����һ����ָ�� 
	int weight; //Ȩֵ 
}ArcNode;//�߽�� 
typedef struct VNode{
	int data;//����ֵ 
	ArcNode *firstarc;//ָ���һ���߽�� 
}VNode;//ͷ��� 
typedef struct{
	VNode adjlist[MAXV];//�ڽӱ��ͷ�������
	int n,e;//������n�ͱ���e 
}AdjGraph;//������ͼ�ڽӱ�����  
typedef struct {
	int data[MaxSize];
	int front, rear;
} SqQueue;

void InitQueue(SqQueue *&q) {
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;
}

bool QueueEmpty(SqQueue *q) {
	return (q->front == q->rear);
}

bool enQueue(SqQueue *&q, int e) {
	if ((q->rear + 1) % MaxSize == q->front)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(SqQueue *&q, int &e) {
	if (q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

void CreatAdj(AdjGraph*& G,int A[MAXV][MAXV],int n,int e){
	int i,j;ArcNode *p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for(i=0;i<n;i++)
		G->adjlist[i].firstarc = NULL;
	for(i=0;i<n;i++)
		for(j=n-1;j>=0;j--)//�����ڽӾ���
			if(A[i][j]!=0&&A[i][j]!=INF){
				p = (ArcNode*)malloc(sizeof(ArcNode));//�����߽�� 
				p->adjvex = j;
				p->weight = A[i][j];
				p->nextarc = G->adjlist[i].firstarc;//ͷ�巨
				G->adjlist[i].firstarc = p; 
			}
	G->n = n;
	G->e = e; 
}
int visited1[MAXV]={0};
void DFS(AdjGraph* G,int v){//������ȱ��� 
	ArcNode *p;
	visited1[v] = 1;//����ѱ����ʵĶ��� 
	printf("%d ",v);//����ѱ����ʶ���ı�� 
	p = G->adjlist[v].firstarc;
	while(p!=NULL){
		if(visited1[p->adjvex]==0){
			DFS(G,p->adjvex);
		}
		p = p->nextarc; 
	}
}
int visited[MAXV] = {0};
void BFS(AdjGraph *G,int v){//������� ���� 
	int w,i;
	ArcNode *p;
	SqQueue *qu;
	InitQueue(qu);
	int visted[MAXV];
	for(i=0;i<G->n;i++)
		visited[i] = 0;//���ʱ�������ʼ�� 
	printf("%d ",v);//��������ʶ���ı�� 
	visited[v] = 1;//����ѱ����ʵĶ��� 
	enQueue(qu,v);
	while(!QueueEmpty(qu)){
		deQueue(qu,w);//����һ������
		p = G->adjlist[w].firstarc;//ָ���һ���߽��
		while(p!=NULL){
			if(visited[p->adjvex]==0){
				printf("%d ",p->adjvex);
				visited[p->adjvex] = 1;
				enQueue(qu,p->adjvex);//���ʺ�ö������ 
			}
			p = p->nextarc;
		} 
	}
	printf("\n");
}

void printDgraph(AdjGraph *G)
{
    int i;ArcNode *p;
    for(i=0;i<G->n;i++){
    	p = G->adjlist[i].firstarc;
    	printf("%3d: ",i);
    	while(p!=NULL){
    		printf("%3d[%d]->",p->adjvex,p->weight);
    		p = p->nextarc;
		}
		printf("��\n");
	}
}

void welcome()//��ӡѡ�����
{
    printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
    printf("\t\t\t\t\t�U             MENU               �U\n");
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         1--Create Graph        �U\n");
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         2--DFS    Graph        �U\n");
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         3--BFS    Graph        �U\n");
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         0--Exit                �U\n");
    printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
    printf("���������ѡ��:\n");
}
int main(){
	AdjGraph *g;
	int A[MAXV][MAXV];
	int n,e,choice,row;
	int a,b;
	while(1){
		welcome();
		scanf("%d",&choice);
		switch(choice){
		case 1:
			system("cls");
			printf("������ͼ�Ķ������ͱ�����");
			scanf("%d%d",&n,&e);
			printf("�������ڽӾ����������");
			scanf("%d",&row);
			printf("��������Ԫ��ֵ��(9999��Ϊ�����)\n");
			for(int i=0;i<row;i++)
				for(int j=0;j<row;j++)
					scanf("%d",&A[i][j]);
			CreatAdj(g,A,n,e);
			printf("�����ɹ���ͼ���£�\n");
			printDgraph(g);
			break;
		case 2:
			system("cls");
			printf("������ָ���������㣺");
			scanf("%d",&a);
			printf("���ѽ�����£�\n");
			DFS(g,a);
			for(int i=0;i<MAXV;i++) visited1[i] = 0;
			break;
		case 3:
			system("cls");
			printf("������ָ���������㣺");
			scanf("%d",&b);
			printf("���ѽ�����£�\n");
			BFS(g,b);
			for(int i=0;i<MAXV;i++) visited[i] = 0;
			break;
		case 0:exit(1);
		default:printf("��������");break;
		}
	}	
	return 0;
} 
