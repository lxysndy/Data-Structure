#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>     //conio��Console Input/Output(����̨�������)�ļ�д�����ж�����ͨ������̨���������������������ĺ�����
//��Ҫ��һЩ�û�ͨ�������̲����Ķ�Ӧ����������getch()�����ȵȡ�
/*
5
12345 С�� 91 92 93
12346 С�� 98 80 98
12348 С�� 97 99 100
12349 С�� 95 94 93
12290 С�� 89 97 96 
*/ 
//�ɼ��ṹ��
struct score
{
	char snum[9];
	char sname[11];
	int chinese;
	int math;
	int english;
	int sumcj;//�ɼ����� 
	int rank;//���� 
};

//�������� 
void showmenu(void);//�˵� 
int xg(int);//�޸ĳɼ�   
void lr(int);//¼��ɼ� 
void cx(int);//��ѯ�ɼ� 
void xhcx(int);//ѧ�Ų�ѯ 
void xmcx(int n);//������ѯ
void allrankcx(int);//������ѯ 
void showcxmenu(void);//�����˵�����ѯ�˵� 
void xs(int);//�ɼ���ʾ 
void jspm(int);//�������� 
int sc(int);//ɾ���ɼ� 
void bccj(void);//����ɼ����˳� 

//main���� 
int main()
{
	int flag,n=0,count=0;//flag��־λ,count����,��ǰ������
	//-------------�ж��ļ������ж�������¼--------------------//
	FILE *fp;//�ļ�ָ�� 
	//��ʾfp��ָ��FILE�ṹ��ָ�������ͨ��fp�����Ҵ��ĳ���ļ���Ϣ�Ľṹ������
	//Ȼ�󰴽ṹ�����ṩ����Ϣ�ҵ����ļ���ʵʩ���ļ��Ĳ�����ϰ����Ҳ��ͳ�ذ�fp��Ϊָ��һ���ļ���ָ�롣
	fp=fopen("cj.txt","a+");//������ļ��������ļ����뻺���� 
	//"a+"���ɶ�/д���ݣ�ԭ�����ļ�����ɾȥ��λ��ָ���Ƶ��ļ�ĩβ 
	if(fp==NULL)      //�ļ�ָ��ָ��� 
	{
		printf("���ļ�ʧ��,�����ԣ�\n");
		getch(); 
		fclose(fp);  //fclose��һ���������������ǹر�һ������
		exit(0);
	} 
	int c = 0;
//	feof()�Ǽ�����ϵ��ļ��������ĺ���������ļ��������򷵻ط�0ֵ�����򷵻�0
//
//һ�����ļ��������о���ʹ��feof()�ж��ļ��Ƿ������
	while(!feof(fp))//������Ϊ�����ļ�βʱ��ִ�к�������
	{
		char cc = fgetc(fp);//��ȡ��һ���ַ� 
		if(cc==EOF)
        {
        	break;
        }
        //����ַ�
//        putchar(cc);
		c++;
	}
	count = c/14;//IO���Ķ�ȡ�ǰ��ַ����ģ�����������7+�ո�6+���з�1=14 
//	printf("%d", count); 
//	getch();
//fclose��һ���������������ǹر�һ������
//ע��:ʹ��fclose()�����Ϳ��԰ѻ����������ʣ�������������ں˻�������
//���ͷ��ļ�ָ����йصĻ�������
	fclose(fp);//����һ�����������ļ����������� 
	//---------------------------------//
	do
	{
		showmenu();
		scanf("%d",&flag);//ѡ����� 
		switch(flag)
		{
			case 1: printf("��������Ҫ¼���������");
					scanf("%d",&n);
				    lr(n);
					count += n;break;
			case 2: count=sc(count);break;
			case 3: xg(count);break;
			case 4: cx(count);break;
			case 5: jspm(count);break;
		    case 6: xs(count);break;
		    case 0: bccj();break; 
		    default:printf("������������ԣ�\n");getch();//getch()�û�����һ���ַ��������Զ���ȡ������Ҫ�س� 
		} 
	}while(flag!=0);
	getch();
	return 0;
}

//0��ʾ�˵�
void showmenu()
{
	system("cls"); 
	printf("*----------------------------------------------------*\n");
	printf("*               ��ӭʹ��**�ɼ�����ϵͳ               *\n");
	printf("*----------------------------------------------------*\n"); 
	printf("*               1�� ¼��ɼ�                         *\n");
	printf("*               2�� ɾ���ɼ�                         *\n");
	printf("*               3�� �޸ĳɼ�                         *\n");
	printf("*               4�� �ɼ���ѯ                         *\n");
	printf("*               5�� �ɼ����㲢����                   *\n");
	printf("*               6�� ��ʾ�ɼ���Ϣ                     *\n");
	printf("*               0�� ������Ϣ���˳�ϵͳ               *\n");
	printf("*----------------------------------------------------*\n");
	printf("ѡ�����<0-6>                                         \n");
	return;
}//չʾ���� 
 
//1¼��ɼ� 
void lr(int n)
 {
 	struct score stu[100];
 	FILE *fp;
 	fp=fopen("cj.txt","a+");
 	if(fp==NULL)
 	{
		printf("���ļ�ʧ��,�����ԣ�\n");
		getch(); 
		fclose(fp);
		exit(0);
	}
 	printf("������ȫ��ѧ����ѧ�ţ����������ĳɼ�����ѧ�ɼ���Ӣ��ɼ���\n"); 
 	int i;
 	for(i=0;i<n;i++)
 	{	
 		printf("----��%d��ѧ��----\n", i+1);
		printf("ѧ��:");
		scanf("%s",&stu[i].snum);
		for(int k=0;k<i;k++)
		{
			if(strcmp(stu[i].snum,stu[k].snum)==0)
			{
			printf("ѧ���ظ������������룡");
		    scanf("%s",&stu[i].snum);
		}
		 } 
	
		printf("������");
		scanf("%s,",&stu[i].sname);
		
		printf("���ĳɼ���");
		scanf("%d",&stu[i].chinese);
		
		printf("��ѧ�ɼ���");
		scanf("%d",&stu[i].math);
		
		printf("Ӣ��ɼ���");
		scanf("%d",&stu[i].english);
		
		stu[i].sumcj=0;
		stu[i].rank=0;	//��ʱ�������к��ܳɼ�Ϊ�� 
		//д������ 
		fprintf(fp,"%s %s %d %d %d %d %d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);}
		//д���ļ� 
	 	fclose(fp);
	 	printf("���ѧ���ɹ�,�밴���������\n");
	 	getch();
 }
	
//2ɾ���ɼ�                                    
int sc(int n)
{
	struct score stu[100];
	struct score sub[99];//ɾ����Ľṹ������ 
	char stnum[9];//ѧ��
	int find=0;
	printf("��������Ҫɾ����ѧ��ѧ��:"); 
	scanf("%s", &stnum);
	FILE *fp;
	fp=fopen("cj.txt","r");//"r"��ֻ�ܴ��ļ��ж����ݣ����ļ������ȴ��ڣ������ʧ�� 
	if(fp==NULL)
	{
		printf("���ļ�ʧ��,����ϵ����Ա\n");
		getch(); 
		return -1;   
	}
	int c=0;
	int index=0;//���ڼ�¼Ŀ����� 
	while(!feof(fp))//��Ϊ��   ������Ϊ�����ļ�βʱ��ִ�к�������
	{ 
		fscanf(fp,"%s %s %d %d %d %d %d\n", &stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		if(strcmp(stnum,stu[c].snum)==0)//�ַ����Ƚϣ�����ѧ��һ���ģ� 
		{
			find = 1;//����ѧ�Ų��ң��ҵ���ֵΪ1 
			index = c;//��¼���
		} 
		c++;//����һ���򵥵�ѭ�������������� 
	}
	fclose(fp);
	if(n==0)
	{
		printf("�Ѿ�û��ѧ���ɼ���Ϣ��,�밴���������\n");
		getch();  
		showmenu();
		return n;
	}
	if(find==0)
	{
		printf("û�и�ѧ���ɼ���Ϣ,�밴���������\n");
		getch();  
		showmenu();
		return n;
	}
	else 
	{
		int i;
		//ɾ�� 
		for(i=0;i<c;i++) // 
		{
			if(i < index)
			{
				sub[i] = stu[i];//����ɾ����ѧ��ǰ��һһ��Ӧ
			}
			else
			{
				sub[i] = stu[i+1];//sub��ɾ����� 
			}//��ɾ����ѧ��֮����һ��λ�� 
		}
		
		fp=fopen("cj.txt","w");//"w"��ֻ�����ļ�д���ݣ���ָ�����ļ��������򴴽����������������ɾ�������ؽ�һ�����ļ�
		//д������ 
		for(i=0;i<c-1;i++)
		{
			fprintf(fp,"%s %s %d %d %d %d %d\n",sub[i].snum,sub[i].sname,sub[i].chinese,sub[i].math,sub[i].english,sub[i].sumcj,sub[i].rank); 	
		} 
		fclose(fp);//д��ɾ����ĳɼ��������������� 
		printf("ѧ��Ϊ%s��ѧ���ɼ�ɾ���ɹ�,�밴���������\n",stnum);
		getch();
		showmenu();
		return n-1;//ѧ������-1 
	}     
}
 
///3�޸ĳɼ�
int xg(int n) 
{	
	struct score stu[100];
 	FILE *fp;
 	char stnum[9];
 	int find=0;  
 	printf("������Ҫ�޸ĵ�ѧ��ѧ��:");
 	scanf("%s",stnum);
 	fp=fopen("cj.txt","r");
 	if(fp==NULL)
 	{
	  	printf("�ļ���ʧ��,����ϵ����Ա\n");
	  	getch();
	  	return -1;	
 	}
 	int c=0;
 	while(!feof(fp))
	{
//		fscanf λ��ͷ�ļ�<stdio.h>�У�����ԭ��Ϊ int fscanf(FILE * stream, const char * format, [argument...]); 
//�书��Ϊ�������ݸ�ʽ(format)��������(stream)�ж�������(�洢��argument);��fgets�Ĳ������:fscanf�����ո�ͻ���ʱ������ע��ո�ʱҲ������fgets�����ո񲻽�����
//

	 	fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
	 	if(strcmp(stnum,stu[c].snum)==0)	
		{
		 	find=1;
		 	//�޸Ĳ��� 
		 	printf("�ҵ���Ҫ�޸ĳɼ���ͬѧ,���������ĳɼ�:\n");
		 	printf("���ĳɼ�: %d,�³ɼ�Ϊ:",stu[c].chinese);
		 	scanf("%d",&stu[c].chinese);
		 	printf("��ѧ�ɼ�: %d,�³ɼ�Ϊ:",stu[c].math); 
		 	scanf("%d",&stu[c].math);
		 	printf("Ӣ��ɼ�: %d,�³ɼ�Ϊ:",stu[c].english);
		 	scanf("%d",&stu[c].english);
 		}
  		c++;	
 	}
	fclose(fp);
	if(find==0)
	{
		printf("û���ҵ�Ҫ�޸ĵ�ѧ����¼,�밴������˳�\n");
		getch(); 
	} 
	else
 	{
	  	fp=fopen("cj.txt","w");
	  	int i; 
	   	for(i=0;i<n;i++)
	   	{
	   		//�������� 
		    fprintf(fp,"%s %s %d %d %d %d %d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);	
	   	}
		fclose(fp);	 
		printf("ѧ��Ϊ%sͬѧ�ĳɼ��Ѿ��޸ĳɹ�,�밴���������",stnum);
 		getch(); 
 	}
  	showmenu();
  	return 1; 
}
   
//4�ɼ���ѯ
void cx(int n) //nȫ������ 
{
	int k;
	do
	{
		showcxmenu();
		scanf("%d",&k); 
		switch(k)
		{ 
			case 1:xhcx(n);break;//ѧ�Ų�ѯ 
			case 2:xmcx(n);break;//������ѯ 
			case 3:allrankcx(n);break;//ȫ��������ѯ
			case 0:break;
			default:printf("�������������ѡ��\n");getch();
		} 
	}while(k!=0);
	return;		
}

//4.0��ѯ�˵�
void showcxmenu() 
{
	system("cls");
	printf("*----------------------------------------------------*\n");
	printf("*                    �ɼ���ѯ�˵�                    *\n");
	printf("*----------------------------------------------------*\n"); 
	printf("*               1�� ��ѧ�Ų�ѯ                       *\n");
	printf("*               2�� ��������ѯ                       *\n");
	printf("*               3�� ȫ��������ѯ                     *\n");
	printf("*               0�� �˳���ѯϵͳ��������ϵͳ         *\n");
	printf("*----------------------------------------------------*\n");
	printf("ѡ�����<0-3>                                         \n");
}

//4.1ѧ�Ų�ѯ
void xhcx(int n)
{   
	struct score stu[100];
	char snum[9];
	printf("��������Ҫ��ѯѧ����ѧ�ţ�");
	scanf("%s",&snum);
	FILE *fp; 
	fp=fopen("cj.txt ","r");//"r"��ֻ�ܴ��ļ��ж����ݣ����ļ������ȴ��ڣ������ʧ�� 
	if(fp==NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
		getch();
		exit(0); 
	}
	int c = 0;
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		c++;
	}
	int i;
	for(i=0;i<n;i++)
	{
		if(strcmp(snum,stu[i].snum)==0)//������ȷ���0 
		{
			printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�ܷ�\t����\n");
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);
			printf("�����������\n");
			getch();
			fclose(fp);
			return;			
		}
	}
	printf("δ�ҵ�Ҫ��ѯѧ���ĳɼ��������ԣ�\n");
	getch();
	fclose(fp);
	return;
}  

//4.2������ѯ
void xmcx(int n)
{
  	struct score stu[100];	
	char sname[11];
	printf("��������Ҫ��ѯѧ����������");
	scanf("%s",&sname);
	FILE *fp; 
	fp=fopen("cj.txt ","r");
	if(fp==NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
		getch();
		exit(0); 
	}
	int c = 0;
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d %d %d\n\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		c++;
	}
	int i,p=0;
	for(i=0;i<n;i++)
	{
		if(strcmp(sname,stu[i].sname)==0)
		{
			p++;
			printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�ܷ�\t����\n");
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);
			printf("�����������\n");
			getch();
			fclose(fp);
		}
	}
	if(p!=0) return;
	printf("δ�ҵ�Ҫ��ѯѧ���ĳɼ��������ԣ�\n");
	getch();
	fclose(fp);
	return;     
}

//4.3ȫ��������ѯ
void allrankcx(int n)
{
  	struct score stu[100];	
  	struct score temp;	
	FILE *fp; 
	fp=fopen("cj.txt ","r");
	if(fp==NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
		getch();
		exit(0); 
	}
	int c = 0;
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		c++;
	}
	int i,j;
	for(i=0;i<n;i++)
	{
		if(stu[i].rank == 0){
			printf("���Ƚ��гɼ����������������\n");
			getch();
			fclose(fp);
			return;	
		}
		stu[i].sumcj = stu[i].chinese + stu[i].math + stu[i].english;
		//ð�������㷨������ n-1 �ֱȽ�
	    for(i=0; i<n-1; i++){
	        //ÿһ�ֱȽ�ǰ n-1-i ����Ҳ����˵���Ѿ�����õ���� i �����ñȽ�
	        for(j=0; j<n-1-i; j++){
	            if(stu[j].sumcj > stu[j+1].sumcj){
	                temp = stu[j];
	                stu[j] = stu[j+1];
	                stu[j+1] = temp;
	            }
	        }
	    }
	    printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�ܷ�\t����\n");
	    for(i=0;i<n;i++)
	    {
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);
		}
		printf("�����������\n");
		getch();
		fclose(fp);
		return;
	}
	printf("��ѯʧ�ܣ������ԣ�\n");
	getch();
	fclose(fp);
	return;     
}

//5������������ 
void jspm(int n)
{
	struct score stu[100];
	int i,j,temp;
	int count;
	FILE *fp;
	fp=fopen("cj.txt","r");
	if(fp==NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
		getch();
		exit(0);
	}
    int c = 0;
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		stu[c].sumcj = stu[c].chinese + stu[c].math + stu[c].english;
		c++;
	}
	fclose(fp);
	//�����������洢 
    for(i=0;i<n;i++)
    {
	    temp=1;//��1�� 
	    for(j=0;j<n;j++){
	    	if(stu[i].sumcj<stu[j].sumcj) temp++;//�����С�������½�1��
		} 
		stu[i].rank=temp;
    }
    //���¼�¼ 
    fp=fopen("cj.txt","w");
   	for(i=0;i<n;i++)
   	{
	    fprintf(fp,"%s %s %d %d %d %d %d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);	
   	}
	fclose(fp);
    printf("�������¼���������ɹ�,�밴������������˵���\n");
	getch();
    return;       
}

//6��ʾ�ɼ���Ϣ
void xs(int n) 
{
	struct score stu[100];
	int i;	
	printf("�ɼ���Ϣ���£�\n");
	FILE *fp;
	fp=fopen("cj.txt","r");
	if(fp==NULL)
	{
		printf("���ļ�ʧ��,�����ԣ�\n");
		getch(); 
		fclose(fp);  
		exit(0);
	} 
	printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�ܷ�\t����\n"); 
	int c = 0;
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		c++;
	}
	if(n!=0){//������Ϊ0 
		for(i=0;i<c;i++)
		{
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);
		}	
	}
	fclose(fp); 
	printf("��ʾ��� ,�밴���������\n");
	getch();
	return;
}

//0������Ϣ���˳�ϵͳ
void bccj()
{
	printf("��л����ʹ�ã���ӭ�´�ʹ��!\n");
	getch();	 
	return;
}


