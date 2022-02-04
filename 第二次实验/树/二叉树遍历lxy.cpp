
#include <stdio.h>
#include <stdlib.h>
//�������ṹ�� 
/*����ʾ��ABC  DE G  F   */ 
typedef struct BiTreeNode
{
    char data;
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
}BiTreeNode,*BiTree;
 
//����ʽ���������� 
void CreateBiTree(BiTree *T) 
{
    char ch;
    scanf("%c",&ch);
 
    if(ch == ' ')
        (*T)= NULL;  //�˽ڵ�Ϊ�� 
 
    else
    {
        (*T) = (BiTree)malloc(sizeof(BiTreeNode));
        (*T)->data = ch;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
}
 
 
//
void PreOrder(BiTree T)
{
    if(T==NULL)
        return;
    printf("%c ",T->data);
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}
 
//������� 
void InOrder(BiTree T)
{
    if(T==NULL)
        return;
    InOrder(T->lchild);
    printf("%c ",T->data);
    InOrder(T->rchild);
}
 
//������� 
void PostOrder(BiTree T)
{
    if(T==NULL)
        return;
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    printf("%c ",T->data);
}
int main()
{
 
    BiTree T;
    T = (BiTree)malloc(sizeof(BiTreeNode));
 
    printf("�����������������ʽ�����������ֵ(�ս��Ϊ' '):\n");
    CreateBiTree(&T);
 
 
    printf("����ʽ���������\n");
    PreOrder(T);
    printf("\n");
 
    printf("����ʽ���������\n");
    InOrder(T);
    printf("\n");
 
    printf("����ʽ���������\n");
    PostOrder(T);
    printf("\n");
    return 0;
}

