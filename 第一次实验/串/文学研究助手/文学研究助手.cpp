#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include"文章结构链表.h" 

#define size 100               //查找单词的大小 

void pretreatment(char a[],int b[])             //预处理 
{
	int c = strlen(a) - 1;                        //c为字符串最后一位 
	do
	{
		int d = c - 1;                            //d为字符串倒数第二位 
		for(;;)
		{
		    while(d >= 0&&a[c] != a[d])          //判断a[d]=a[c],不然就d--,再次判断，直至a[d]=a[c]或d<0 
		    {
		    	d--;
		    }
		    if(d >= 0)                          //d>=0说明啊a[d]=a[c] 
		    {
		    	char e[d+2],f[d+2];             //用于比较字符串 
		    	strncpy(e,&a[0],sizeof(e)-1);   //将a[0]到a[d]复制到e中 
		    	strncpy(f,&a[c-d],sizeof(f)-1); //将a[c-d]到a[c]复制到e中 
		    	e[d+1] = f[d+1] = '\0';         
		    	if(!strcmp(&e[0],&f[0]))        //如果f和e相同，说明匹配成功，令b[c]=d 
			    {
			    	b[c] = d;
			    	goto DONE;
		    	}
		    	else                            //否则继续d--,匹配 
		    	{
		    		d--;
				}
	    	}
	    	else                                //若d<0,说明a中没有与a[c]匹配的 
	    	{
	    		b[c] = -1;      
	    		goto DONE;
			}
		}
		DONE:                                    //对下一个进行匹配 
		c--;
	}while(c >= 0);                              //匹配直至c<0,即a中全部字符都匹配完成才结束 
}
void found(char a[],int b[],article art,FILE *w)    //kmp查找 
{
	int number = 0;                                 //number代表计数，用于统计查找到的个数 
	for(ROW *q = art.first;q != NULL;q = q->next)   
	{
		int n=0,row_number=0;                       //n代表字符匹配个数，row_number代表行计数，用于统计这一行查找到的个数 
		for(word *p = q->r.first->next;p != NULL;p = p->next)
		{
			if(p->letter == a[n])                   //如果匹配成功，继续下一位匹配 
			{
				n++;
			}
			else if(n == 0)                         //若匹配不成功，且匹配的是头一个字符，则继续匹配 
			{
				continue;
			}
			else if(b[n-1] == -1)                   //若预处理中发现不可拖动窗口，则直接继续匹配头一个字符 
			{
				n = 0; 
			}
			else
			{
				for(n = b[n-1] + 1;n != -1;n = b[n-1] + 1)     //拖动窗口再次进行比较 
				{
					if(p->letter == a[n])                      //匹配成功，继续下一个匹配 
			        {
				        n++;
						break;
			        }
				}
				if(b[n] == -1)                                 //匹配不成功，继续从头一个字符匹配 
			    {
				    n = 0; 
			    }
			}
			if(n > (strlen(a) - 1))         //全部字符匹配成功，计数加一，行计数加一 ，继续从头字符开始匹配 
			{
				number++;
				row_number++;
				n=0;
			}
		}
		if(row_number > 0)            //行计数大于0，即这一行有至少一个要查找的单词，则输出 
		{
    		fprintf(w,"第%d行有%d个\n",q->r.first->letter,row_number);
		}
	}
	fprintf(w,"共计有%d个。\n",number);
}
int main()
{
	FILE *r,*w;
	printf("请将文章放入文件‘英文小说.txt’中（放好请按ENTER键继续）");
	getchar();
	if((r = fopen("英文小说.txt","rt")) == NULL)
	{
		exit(-1); 
	}
	if((w = fopen("统计词汇的结果.txt","w")) == NULL)
	{
		exit(-1);
	}
	article english;         //english代表英语文章 
	create_article(&english);
	for(char ch;(fscanf(r,"%c",&ch)) != EOF;)
	{
		if(ch != '\n')        //添加字母 
		{
			add_word(&(english.last->r),ch);
		}
		else                 //添加行 
		{
			add_row(&english);
		}
	}
	printf("请输入要统计单词的个数：");
	int number;
	scanf("%d",&number);
	getchar();
	char search[size];           //search代表查找的单词 
	int result[size];            //result代表预处理结果           
	for(int n = 0;n < number;n++)
	{
		memset(search,0,sizeof(search));
		memset(result,0,sizeof(result));
		printf("请输入第%d个单词：",n+1);
		scanf("%s",&search[0]);
		pretreatment(search,result);
		fprintf(w,"第%d个单词%s统计结果：\n",n+1,search); 
		found(search,result,english,w); 
	}
	printf("查找结果放在文件“统计词汇的结果.txt”中");
	return 0;
}
