#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//二叉树结构体 
typedef struct BiTreeNode
{
    char data;
    int deep; 
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
}BiTreeNode,*BiTree;
//先序方式建立二叉树,注意深度的确定 
void CreateBiTree(BiTree *T,int d) 
{
    char ch;
    scanf("%c",&ch);
    
    if(ch == ' ')
        (*T)= NULL;  //此节点为空 
 
    else
    {
        (*T) = (BiTree)malloc(sizeof(BiTreeNode));
        (*T)->data = ch;
        (*T)->deep = d;
        CreateBiTree(&((*T)->lchild),d+1);//遍历到孩子节点，深度加一 
        CreateBiTree(&((*T)->rchild),d+1);
    }
}
/**这里使用中序遍历，但是和标准的相反，需要满足打印出来二叉树的要求，故实行更改。**/
//中序遍历采用“右根左”适合本题输出
void InOrderOpposite(BiTree T,void (*print)(BiTree T))
{
    if(T==NULL)
        return;
    InOrderOpposite(T->rchild,print);
    print(T);
    InOrderOpposite(T->lchild,print);
}
void print(BiTree t)         //打印二叉树 
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
	
	printf("输入需要打印的二叉树的结构：\n");
	CreateBiTree(&T,0);
	InOrderOpposite(T,print);
	return 0;
}
