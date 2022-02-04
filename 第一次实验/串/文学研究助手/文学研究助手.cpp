#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include"���½ṹ����.h" 

#define size 100               //���ҵ��ʵĴ�С 

void pretreatment(char a[],int b[])             //Ԥ���� 
{
	int c = strlen(a) - 1;                        //cΪ�ַ������һλ 
	do
	{
		int d = c - 1;                            //dΪ�ַ��������ڶ�λ 
		for(;;)
		{
		    while(d >= 0&&a[c] != a[d])          //�ж�a[d]=a[c],��Ȼ��d--,�ٴ��жϣ�ֱ��a[d]=a[c]��d<0 
		    {
		    	d--;
		    }
		    if(d >= 0)                          //d>=0˵����a[d]=a[c] 
		    {
		    	char e[d+2],f[d+2];             //���ڱȽ��ַ��� 
		    	strncpy(e,&a[0],sizeof(e)-1);   //��a[0]��a[d]���Ƶ�e�� 
		    	strncpy(f,&a[c-d],sizeof(f)-1); //��a[c-d]��a[c]���Ƶ�e�� 
		    	e[d+1] = f[d+1] = '\0';         
		    	if(!strcmp(&e[0],&f[0]))        //���f��e��ͬ��˵��ƥ��ɹ�����b[c]=d 
			    {
			    	b[c] = d;
			    	goto DONE;
		    	}
		    	else                            //�������d--,ƥ�� 
		    	{
		    		d--;
				}
	    	}
	    	else                                //��d<0,˵��a��û����a[c]ƥ��� 
	    	{
	    		b[c] = -1;      
	    		goto DONE;
			}
		}
		DONE:                                    //����һ������ƥ�� 
		c--;
	}while(c >= 0);                              //ƥ��ֱ��c<0,��a��ȫ���ַ���ƥ����ɲŽ��� 
}
void found(char a[],int b[],article art,FILE *w)    //kmp���� 
{
	int number = 0;                                 //number�������������ͳ�Ʋ��ҵ��ĸ��� 
	for(ROW *q = art.first;q != NULL;q = q->next)   
	{
		int n=0,row_number=0;                       //n�����ַ�ƥ�������row_number�����м���������ͳ����һ�в��ҵ��ĸ��� 
		for(word *p = q->r.first->next;p != NULL;p = p->next)
		{
			if(p->letter == a[n])                   //���ƥ��ɹ���������һλƥ�� 
			{
				n++;
			}
			else if(n == 0)                         //��ƥ�䲻�ɹ�����ƥ�����ͷһ���ַ��������ƥ�� 
			{
				continue;
			}
			else if(b[n-1] == -1)                   //��Ԥ�����з��ֲ����϶����ڣ���ֱ�Ӽ���ƥ��ͷһ���ַ� 
			{
				n = 0; 
			}
			else
			{
				for(n = b[n-1] + 1;n != -1;n = b[n-1] + 1)     //�϶������ٴν��бȽ� 
				{
					if(p->letter == a[n])                      //ƥ��ɹ���������һ��ƥ�� 
			        {
				        n++;
						break;
			        }
				}
				if(b[n] == -1)                                 //ƥ�䲻�ɹ���������ͷһ���ַ�ƥ�� 
			    {
				    n = 0; 
			    }
			}
			if(n > (strlen(a) - 1))         //ȫ���ַ�ƥ��ɹ���������һ���м�����һ ��������ͷ�ַ���ʼƥ�� 
			{
				number++;
				row_number++;
				n=0;
			}
		}
		if(row_number > 0)            //�м�������0������һ��������һ��Ҫ���ҵĵ��ʣ������ 
		{
    		fprintf(w,"��%d����%d��\n",q->r.first->letter,row_number);
		}
	}
	fprintf(w,"������%d����\n",number);
}
int main()
{
	FILE *r,*w;
	printf("�뽫���·����ļ���Ӣ��С˵.txt���У��ź��밴ENTER��������");
	getchar();
	if((r = fopen("Ӣ��С˵.txt","rt")) == NULL)
	{
		exit(-1); 
	}
	if((w = fopen("ͳ�ƴʻ�Ľ��.txt","w")) == NULL)
	{
		exit(-1);
	}
	article english;         //english����Ӣ������ 
	create_article(&english);
	for(char ch;(fscanf(r,"%c",&ch)) != EOF;)
	{
		if(ch != '\n')        //�����ĸ 
		{
			add_word(&(english.last->r),ch);
		}
		else                 //����� 
		{
			add_row(&english);
		}
	}
	printf("������Ҫͳ�Ƶ��ʵĸ�����");
	int number;
	scanf("%d",&number);
	getchar();
	char search[size];           //search������ҵĵ��� 
	int result[size];            //result����Ԥ������           
	for(int n = 0;n < number;n++)
	{
		memset(search,0,sizeof(search));
		memset(result,0,sizeof(result));
		printf("�������%d�����ʣ�",n+1);
		scanf("%s",&search[0]);
		pretreatment(search,result);
		fprintf(w,"��%d������%sͳ�ƽ����\n",n+1,search); 
		found(search,result,english,w); 
	}
	printf("���ҽ�������ļ���ͳ�ƴʻ�Ľ��.txt����");
	return 0;
}
