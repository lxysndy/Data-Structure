
#include <stdio.h>
#include <stdlib.h>
//二叉树结构体 
/*输入示例ABC  DE G  F   */ 
typedef struct BiTreeNode
{
    char data;
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
}BiTreeNode,*BiTree;
 
//先序方式建立二叉树 
void CreateBiTree(BiTree *T) 
{
    char ch;
    scanf("%c",&ch);
 
    if(ch == ' ')
        (*T)= NULL;  //此节点为空 
 
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
 
//中序遍历 
void InOrder(BiTree T)
{
    if(T==NULL)
        return;
    InOrder(T->lchild);
    printf("%c ",T->data);
    InOrder(T->rchild);
}
 
//后序遍历 
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
 
    printf("请给二叉树按照先序方式依次输入结点的值(空结点为' '):\n");
    CreateBiTree(&T);
 
 
    printf("先序方式遍历结果：\n");
    PreOrder(T);
    printf("\n");
 
    printf("中序方式遍历结果：\n");
    InOrder(T);
    printf("\n");
 
    printf("后序方式遍历结果：\n");
    PostOrder(T);
    printf("\n");
    return 0;
}

