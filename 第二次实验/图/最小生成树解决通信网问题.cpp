
#include<stdio.h>
#include<stdlib.h>

#define MaxVertices 100
#define INF 65535
int graph[MaxVertices][MaxVertices];
//�����߱�
typedef struct node
{
	int adjvex;				//ָ��߱���
	struct node *nextarc;	//ָ����һ���ߣ�û����ΪNULL
	int info;				//Ȩֵ
}ArcNode;
//���������
typedef struct
{
	char data[MaxVertices];			//��������
	ArcNode *firstarc;		//ָ��ö���ĵ�һ���߱���
}VerNode;
//����ͼ
typedef struct
{
	VerNode adjlist[MaxVertices];//��������
	int n;						 //�ܶ���ĸ���
	int e;						 //�ܵı���
}ALGraph;

//�����ڽӱ�
void CrateGraph(ALGraph *G)
{
	int i,j, k;
	int v1, v2;									//�����������
	int weight;											//Ȩֵ
	printf("�������ڽӱ���ܶ������ͱ�����");
	scanf("%d %d", &G->n, &G->e);
	for (i = 1; i <= G->n; i++)				//prim��С��������ʼ��
	{
		for (j = 1; j <= G->e; j++)
		{
			graph[i][j] = INF;
		}
	}
	fflush(stdin);
	printf("�����붥�㣨�س�����һ�����룩\n");
	for (i = 0; i < G->n; i++)
	{
		gets(G->adjlist[i].data);
		G->adjlist[i].firstarc = NULL;					//��ͷ�����һ����Ϊ�� 
	}
	printf("����ݶ����λ�ô�1��ʼ�����������ڵıߺ�Ȩֵ(�м��ÿո����)\n");
	for (k = 0; k < G->e; k++)
	{
		fflush(stdin);//������뻺���� 
		printf("��%d�����ӵ㣺", k + 1);
		scanf("%d %d %d", &v1, &v2, &weight);			//�������ڵıߺ�Ȩֵ
		graph[v1][v2] = weight;
		graph[v2][v1] = weight;//�����ڹ����ڽӾ��� 
		v1--; v2--;										//�����������1��ʼ����ȥ1�����������
		ArcNode *s = (ArcNode *)malloc(sizeof(ArcNode));
		s->info = weight;
		s->adjvex = v2;
		s->nextarc = G->adjlist[v1].firstarc;
		G->adjlist[v1].firstarc = s;//�൱�������ڽӾ������ڽӱ� 
	}
}
//��ӡ�ڽӱ�
void DisGraph(ALGraph *G)
{
	int i;
	printf("���\t��������\t\t�߱�\n");
	for (i = 0; i < G->n; i++)
	{
		printf("%d\t", i+1);						//��ӡ���
		printf("%s\t\t->", G->adjlist[i].data);		//��ӡ����
		while (G->adjlist[i].firstarc)
		{
			printf("%d(%d)->", G->adjlist[i].firstarc->adjvex+1, G->adjlist[i].firstarc->info);
			G->adjlist[i].firstarc = G->adjlist[i].firstarc->nextarc;
		}
		printf("NULL\n");
	}
}
//prim��С������

int Prim(int graph[][MaxVertices], int n)
{
	int lowcost[MaxVertices], closest[MaxVertices];
	/*
	lowcost[i]��¼��iΪ�յ�ıߵ���СȨֵ����lowcost[i]=0ʱ��ʾ�յ�i����������
	closest[i]��¼��Ӧlowcost[i]����㣬��closest[i]=0ʱ��ʾ���i����������
	*/
	int i, j, min, minid, sum = 0;
	for (i = 2; i <= n; i++)				//Ĭ��ѡ��1�Žڵ��������������2�Žڵ㿪ʼ��ʼ��
	{
		lowcost[i] = graph[1][i];			//��̾����ʼ��Ϊ�����ڵ㵽1�Žڵ�ľ���
		closest[i] = 1;							//������нڵ������ΪĬ�ϵ�1�Žڵ�
	}
	closest[1] = 0;								//���1�Žڵ����������
	for (i = 2; i <= n; i++)				//n���ڵ�������Ҫn-1���߹�����С������
	{
		min = INF;
		for (j = 1; j <= n; j++)			 //��������������СȨֵ�ߵĽڵ�minid
		{
			if (lowcost[j] < min && lowcost[j] != 0)  //��Ȩֵ��С�Ҳ�����������
			{
				min = lowcost[j];
				minid = j;
			}
		}
		printf("��(%d,%d)��ȨΪ��%d\n", closest[minid], minid, min);  //����������ߵ���Ϣ:��㣬�յ㣬Ȩֵ
		sum += min;							//�ۼ�Ȩֵ
		lowcost[minid] = 0;					//��ǽڵ�minid����������

		for (j = 2; j <= n; j++)			//���µ�ǰ�ڵ�minid�������ڵ��Ȩֵ
		{
			if (graph[minid][j] < lowcost[j])  ///���ָ�С��Ȩֵ
			{
				lowcost[j] = graph[minid][j];  //����Ȩֵ��Ϣ
				closest[j] = minid;				//������СȨֵ�ߵ����
			}//�ı�U��U�����������Ȩֵ�����仯�����и��� 
		}
	}
	return sum;								//������СȨֵ��
}

int main()
{
	ALGraph G;
	CrateGraph(&G);
	printf("\n");
	DisGraph(&G);
	printf("\n��С��������Ȩֵ֮��:%d\n", Prim(graph, G.n));
	return 0;
}
/*��������ʾ����
8 11

a
b
c
d
e
f
g
h

1 2 8
1 3 3
2 4 2
3 4 1
4 5 6
4 6 14
5 6 4
5 7 12
6 8 9
6 7 2
7 8 11*/

