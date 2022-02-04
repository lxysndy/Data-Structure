#include<stdio.h>
#include<stdlib.h>
#define UNVISITED 0
#define VISITED 1
#define INFINITY INT_MAX
#define UNSELECTED 0
#define SELECTED 1

typedef struct
{
    int symbol;//�������
    const char *name;//��������
    const char *introduction;//������
}spot;          //��������

typedef struct
{
    spot v,w;   //�ߵĶ˵�
    int info;   //�Դ�Ȩͼ��ΪȨֵ���˴�Ϊ����
}ArcInfo;   //�洢����Ϣ

typedef struct
{
    spot *vexs;  //�������飬spot�Ǿ�������
    int **arcs;  //��ϵ���飬��ͼΪ��Ȩͼ����ΪȨֵ��INFINITY
    int n,e;     //�������ͱ���
    int *tags;   //��־���飬��������ͼ�ı����б�Ƕ���������
}MGraph;

typedef struct
{
    int prev;   //��ǰ���·���ϸö����ǰ�������λ��
    int lowcost;//��ǰ���·���ĳ���
}DistInfo;//V-U�ж���ĵ�ǰ���·����Ϣ


int LocateVex(MGraph G,spot v)//�Ҷ���λ�� 
{
    int i;
    for(i=0;i<G.n;i++)
        if(v.symbol==G.vexs[i].symbol) return i;
    return -1;
}

int  InitGraph(MGraph &G,spot *vexs,int n)
{
    //��ʼ����n���������ޱߵ�ͼG
    int i,j,info;
    if(n<0||(n>0&&vexs==NULL)) return 0;
    info=INFINITY;  //��Ȩͼ
    G.n = n;
    G.e = 0;  //�������ͱ���
    if(G.n==0) return 1;   //��ͼ
    if((G.vexs=(spot*)malloc(n*sizeof(spot)))==NULL) return 0;
    for(i=0;i<G.n;i++) G.vexs[i]=vexs[i];
    if((G.arcs=(int **)malloc(n*sizeof(int*)))==NULL) //����ָ������
        return 0;
    for(i=0;i<n;i++) //����ÿ��ָ����ָ�������
        if((G.arcs[i]=(int*)malloc(n*sizeof(int)))==NULL)
            return 0;
    if((G.tags=(int*)malloc(n*sizeof(int)))==NULL) return 0;
    for(i=0;i<n;i++){   //��ʼ����־����͹�ϵ����
        G.tags[i]=UNVISITED;
        for(j=0;j<n;j++) G.arcs[i][j]=info;
    }
    return 1;
}

int  CreateGraph(MGraph &G,spot *vexs,int n,ArcInfo *arcs,int e)
{
    //������n�������e���ߵ������ȨͼͼG��vexsΪ������Ϣ��arcsΪ����Ϣ
    if(n<0||e<0||(n>0&&vexs==NULL)||(e>0&&arcs==NULL)) return 0;
    int i,j,k;
    spot v,w;
    if(InitGraph(G,vexs,n)!=1) return 0;    //��ʼ��
    G.e = e;//����
    for(k=0;k<G.e;k++){//������ϵ����
        v=arcs[k].v; w=arcs[k].w;   //�����(v,w)
        i=LocateVex(G,v);j=LocateVex(G,w);//ȷ��v��w�ڶ��������е�λ��i��j
        if(i<0||j<0) return 0;
        G.arcs[i][j]=G.arcs[j][i]=arcs[k].info;
    }
    return 1;
}

int FirstAdjVex(MGraph G,int k)
{//��ͼG��k����ĵ�һ���ڽӶ����λ��
    int i;
    if(k<0||k>=G.n) return -1;
    for(i=0;i<G.n;i++){//���ҵ�һ��ֵ�����ҷ�INFINITY��Ԫ��
        if(G.arcs[k][i]!=0&&G.arcs[k][i]!=INFINITY) return i;
    }
    return -1;//k�������ڽӶ���
}

int NextAdjVex(MGraph G,int k,int m)
{
    //m����Ϊk������ڽӶ��㣬��ͼ��k���������m�������һ���ڽӶ����λ��
    int i;
    if(k<0||k>=G.n||m<0||m>=G.n) return 0;
    for(i=m+1;i<G.n;i++)
        if(G.arcs[k][i]!=0&&G.arcs[k][i]!=INFINITY)
            return i;
    return -1;
}

int  visit(int k,MGraph G)
{
    //���ʽ����Ϣ����ȡ������Ϣ��
    if(k<0||k>=G.n) return 0;
    printf("������ţ�%d\n",G.vexs[k].symbol);
    printf("�������֣�%s\n",G.vexs[k].name);
    printf("�����飺%s\n",G.vexs[k].introduction);
    return 1;
}


int Dijkstra(MGraph G,int i,DistInfo* &Dist)
{
    //��ͼG�д�i���㵽�������ж�������·��������Dist����
    //�Ͻ�˹�����㷨
    int j,m,k,min,p;
    Dist = (DistInfo*)malloc(G.n*sizeof(DistInfo));
    for(j=0;j<G.n;j++){
        //��ʼ��
        Dist[j].lowcost = INFINITY;
        G.tags[j] = UNSELECTED;
    }
    for(j=0;j<G.n;j++){
        //Դ��i���������л�����Ϣ����Dist
        if(G.arcs[i][j]!=INFINITY){
            Dist[j].prev=i;
            Dist[j].lowcost=G.arcs[i][j];
        }
    }
    Dist[i].prev=-1;Dist[i].lowcost=0;//Դ��i��Ϣ����Dist
    G.tags[i]=SELECTED;//��ʼ����U����Դ��i

    for(m=1;m<G.n;m++){ //��·����������������Դ�㵽������������·��
        min=INFINITY;k=0;
        for(j=0;j<G.n;j++)
            {
            if(UNSELECTED==G.tags[j]&&Dist[j].lowcost<min)
            {
                k=j;
                min=Dist[k].lowcost;        //�˴������V-U�����е����·��
            }
        }
        G.tags[k]=SELECTED; //��k������뼯��U
        for(p=FirstAdjVex(G,k);p>=0;p=NextAdjVex(G,k,p)){    //����Dist���飬��������һ�����Ż������ô�0��ʼѭ�� 
            if(UNSELECTED==G.tags[p]&&Dist[k].lowcost+G.arcs[k][p]<Dist[p].lowcost){
                Dist[p].lowcost = Dist[k].lowcost+G.arcs[k][p];     //k����ڽӵ��о�����С�ĵ�p
                Dist[p].prev=k;
            }
        }
    }
    return 1;
}

void Dispath(MGraph G,DistInfo *Dist,int k)
{
    //��Dist�����prev�򣬿ɵݹ���Դ�㵽k��������·��
    if(k==-1) return ;
    Dispath(G,Dist,Dist[k].prev);//����ݹ���·���ϵĶ���
    printf("%d.%s  ",G.vexs[k].symbol,G.vexs[k].name);    //���������ǰ·���ϵĶ���
}



void initdata(spot *vexs,ArcInfo *arcs)
{

    vexs[0].symbol=1;
    vexs[0].name="����";
    vexs[0].introduction="��԰�����ţ���ΰ׳�۵Ĵ���ʯ�����ţ������˹�԰�ĺ�ΰ׳��";

    vexs[1].symbol=2;
    vexs[1].name="�ɻ���";
    vexs[1].introduction="һ�����գ����صĺɻ���������";

    vexs[2].symbol=3;
    vexs[2].name="������";
    vexs[2].introduction="�����������ںɻ������룬�οͿ������Ͻ������ͻ�";

    vexs[3].symbol=4;
    vexs[3].name="����ͤ";
    vexs[3].introduction="���ںɻ������룬�����ο�ͣ����Ϣ";

    vexs[4].symbol=5;
    vexs[4].name="���ֳ�";
    vexs[4].introduction="����������ʩ��ȫ���ɹ��ο;�����ˣ���ͷ�����";

    vexs[5].symbol=6;
    vexs[5].name="������";
    vexs[5].introduction="���Ǽ������ļ�������������ɫ��������";

    vexs[6].symbol=7;
    vexs[6].name="�۾�̨";
    vexs[6].introduction="�۾�̨�ǵ��ƹ�԰��ߵĵط����ڴˣ��������������԰�ķ羰";

    vexs[7].symbol=8;
    vexs[7].name="����";
    vexs[7].introduction="�������и���ʳ���Ϊ�οͽ�ʳ伢";

    vexs[8].symbol=9;
    vexs[8].name="��Ϣ��";
    vexs[8].introduction="�䱸���䣬�ο��������ڴ���Ϣ";

    vexs[9].symbol=10;
    vexs[9].name="���г���";
    vexs[9].introduction="�и��ֿ�ʽ�����г���Ҳ��ר�ŵ����г���������1����";

    vexs[10].symbol=11;
    vexs[10].name="�δ���";
    vexs[10].introduction="��˫�ˡ����˸��ŷ��δ��������ο;��������ˮ�ϵĿ���ʱ��";

    //����Ϣ
    arcs[0].v=vexs[0];
    arcs[0].w=vexs[1];
    arcs[0].info=1;

    arcs[1].v=vexs[1];
    arcs[1].w=vexs[2];
    arcs[1].info=3;

    arcs[2].v=vexs[1];
    arcs[2].w=vexs[3];
    arcs[2].info=4;

    arcs[3].v=vexs[2];
    arcs[3].w=vexs[3];
    arcs[3].info=6;

    arcs[4].v=vexs[3];
    arcs[4].w=vexs[4];
    arcs[4].info=1;

    arcs[5].v=vexs[1];
    arcs[5].w=vexs[5];
    arcs[5].info=4;

    arcs[6].v=vexs[2];
    arcs[6].w=vexs[5];
    arcs[6].info=4;

    arcs[7].v=vexs[3];
    arcs[7].w=vexs[5];
    arcs[7].info=5;

    arcs[8].v=vexs[3];
    arcs[8].w=vexs[6];
    arcs[8].info=6;

    arcs[9].v=vexs[2];
    arcs[9].w=vexs[7];
    arcs[9].info=7;

    arcs[10].v=vexs[5];
    arcs[10].w=vexs[6];
    arcs[10].info=9;

    arcs[11].v=vexs[5];
    arcs[11].w=vexs[7];
    arcs[11].info=6;

    arcs[12].v=vexs[5];
    arcs[12].w=vexs[8];
    arcs[12].info=4;

    arcs[13].v=vexs[5];
    arcs[13].w=vexs[9];
    arcs[13].info=6;

    arcs[14].v=vexs[3];
    arcs[14].w=vexs[9];
    arcs[14].info=7;

    arcs[15].v=vexs[6];
    arcs[15].w=vexs[10];
    arcs[15].info=3;

    arcs[16].v=vexs[7];
    arcs[16].w=vexs[8];
    arcs[16].info=4;

    arcs[17].v=vexs[8];
    arcs[17].w=vexs[9];
    arcs[17].info=5;

    arcs[18].v=vexs[9];
    arcs[18].w=vexs[10];
    arcs[18].info=5;

}

void welcom()
{
    printf("\t\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
    printf("\t\t\t\t\t\t�U         ��԰����ϵͳ           �U\n");
    printf("\t\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t\t�U         1-�鿴������Ϣ         �U\n");
    printf("\t\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t\t�U         2-�鿴����������·�� �U\n");
    printf("\t\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t\t�U         3-�˳�ϵͳ             �U\n");
    printf("\t\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");

}

void spotList()
{
    printf("\t\t\t\t\t\t***********�����б�************     \n");
    printf("\t\t\t\t\t   ------------------------------------------\n");
    printf("\t\t\t\t\t   1.����     2.�ɻ���    3.������   4.����ͤ\n");
    printf("\t\t\t\t\t   5.���ֳ�   6.������    7.�۾�̨   8.���� \n");
    printf("\t\t\t\t\t   9.��Ϣ��   10.���г��� 11.�δ���        \n");
    printf("\t\t\t\t\t   ------------------------------------------\n");

}


int main()
{
    int n=11,e=19,sum=0,flag=0;
    spot *vexs;
    ArcInfo *arcs;
    int *path;      //���ڴ洢·��
    int length;     //��ǰ·������
    int choice=INFINITY,i,j;
    vexs=(spot*)malloc(n*sizeof(spot));         //����ռ�
    arcs=(ArcInfo*)malloc(e*sizeof(ArcInfo));
    path=(int*)malloc(e*sizeof(int));
    length=0;
    MGraph G;
    DistInfo *Dist; //��������
    initdata(vexs,arcs);
    CreateGraph(G,vexs,n,arcs,e);
    while(1)
    {
        welcom();
        spotList();
        printf(" \n| ��ѡ����  |\n");
        scanf("%d",&choice);
        switch(choice)
        {
          case 1:
          	system("cls");
          	spotList();
            printf("����鿴�ĸ��������Ϣ��1-%d����\n",G.n);
            scanf("%d",&i);
            while(i<=0||i>G.n)
            {
             printf("����������ݲ��Ϸ�������������\n");
             scanf("%d",&i);
            }
             visit(i-1,G);
             break;
         case 2:
            system("cls");
            spotList();
            for(i=0;i<n;i++)
            {   //��ʼ����־����
             G.tags[i]=UNVISITED;
            }
             printf("�����һ�������ţ�1-%d��\n",G.n);      //�����·��
             scanf("%d",&i);
            while(i<=0||i>G.n)
            {
             printf("����������ݲ��Ϸ�������������\n");
             scanf("%d",&i);
            }
             printf("����ڶ��������ţ�1-%d��\n",G.n);
             scanf("%d",&j);
            while(j<=0||j>G.n)
            {
             printf("����������ݲ��Ϸ�������������\n");
             scanf("%d",&j);
            }
             Dijkstra(G,i-1,Dist);   //�Ͻ�˹�����㷨���Dist����
            if(Dist[j-1].lowcost==INFINITY)
            {
             printf("û����ͨ\n");
             break;
            }
            else
            {
                printf("·�ߣ�");
                Dispath(G,Dist,j-1); //�ݹ����
                printf("\n");
                printf("·������Ϊ:%d��\n",Dist[j-1].lowcost*100);
                break;
            }
        case 3:exit(1);
        default:system("cls");printf("�������ݲ��Ϸ���������ѡ��\n");
      }
    }
    return 0;
}

