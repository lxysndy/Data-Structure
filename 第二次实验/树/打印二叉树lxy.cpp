#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//�������ṹ�� 
typedef struct BiTreeNode
{
    char data;
    int deep; 
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
}BiTreeNode,*BiTree;
//����ʽ����������,ע����ȵ�ȷ�� 
void CreateBiTree(BiTree *T,int d) 
{
    char ch;
    scanf("%c",&ch);
    
    if(ch == ' ')
        (*T)= NULL;  //�˽ڵ�Ϊ�� 
 
    else
    {
        (*T) = (BiTree)malloc(sizeof(BiTreeNode));
        (*T)->data = ch;
        (*T)->deep = d;
        CreateBiTree(&((*T)->lchild),d+1);//���������ӽڵ㣬��ȼ�һ 
        CreateBiTree(&((*T)->rchild),d+1);
    }
}
/**����ʹ��������������Ǻͱ�׼���෴����Ҫ�����ӡ������������Ҫ�󣬹�ʵ�и��ġ�**/
//����������á��Ҹ����ʺϱ������
void InOrderOpposite(BiTree T,void (*print)(BiTree T))
{
    if(T==NULL)
        return;
    InOrderOpposite(T->rchild,print);
    print(T);
    InOrderOpposite(T->lchild,print);
}
void print(BiTree t)         //��ӡ������ 
{
	int i;
	for(i = 0;i <= t->deep;i++)
	{
		printf("   ");
	}
	printf("%c",t->data);
	printf("\n");
}
int main(){
	BiTree T;
	T = (BiTree)malloc(sizeof(BiTree));
	
	printf("������Ҫ��ӡ�Ķ������Ľṹ��\n");
	CreateBiTree(&T,0);
	InOrderOpposite(T,print);
	return 0;
}
