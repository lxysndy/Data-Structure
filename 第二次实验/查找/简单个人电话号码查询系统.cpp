#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*12334567890
С��
12345678@qq.com
С���ѱ���
19098079900
С��
1447689@qq.com*/
#include<iostream>
int d[50];/*��ɢ��*/
struct list
{
    char a[12];//�绰���� 
    char name[15];//���� 
    char add[20];//���� 
    int f=0;//����Ƿ���� 
};
struct sqstack
{
    struct list *base;
   int i;
};
struct sqstack S;
void store(char *a,char *name,char *add)
{
    int key;
    key=int(a[0])+int(a[3])+int(a[7]);/*�Ե绰����ĵ�1,4,8λ��Ϊ�ؼ��ֹ����ϣ����*/
    S.i=key%20;
    int j=1;
    while(true)
    {
    if((S.base+S.i)->f==0)
    {
        strcpy((S.base+S.i)->a,a);
        strcpy((S.base+S.i)->name,name);
        strcpy((S.base+S.i)->add,add);
        (S.base+S.i)->f=1;
        break;
    }
        S.i=(key%20+d[j])%20;
        j++;//�����ϣ��ͻ 
    }
 
}
void shuru()
{
void interface();
    printf("�����룺\n���磺\n15556931615\nС��\n12345678@qq.com\n����0����\n\n");
    char a[12];
    char name[15];
    char add[15];
   while(true)
   {
      scanf("%s",a);
      if(a[0]=='0')
        break;
      scanf("%s",name);
      scanf("%s",add);
      printf("%s�ѱ���\n",name);
      store(a,name,add);/*�����뱣�浽��ϣ��*/
   }
   interface();
}
void print()
{
    void interface();
    int i;
    printf("����   �绰����      ����\n");
    for(i=0;i<20;i++)
    {
        if((S.base+i)->f==1)
        {
            printf("%s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
        }
    }
    interface();
}
void search()
{
    void interface();
    int i;
    int ff=0;
    int b;
    char a[15];
    printf("����1���绰������ң�����2���������ң�����3���������\n");
    scanf("%d",&b);
    switch(b)
    {
        case 1:printf("������绰����\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->a)==0)
               {
                   printf("%s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
               if(ff==0)
                printf("�Ҳ������û�\n");
               break;
       case 2:printf("����������\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->name)==0)
               {
                   printf("%s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
                if(ff==0)
                printf("�Ҳ������û�\n");
               break;
        case 3:printf("����������\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->add)==0)
               {
                   printf("%s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
                if(ff==0)
                printf("�Ҳ������û�\n");
               break;
    }
    interface();
}
void del()
{
    void interface();
    int i;
    int ff=0;
    int b;
    char a[15];
    printf("����1���绰����ɾ��������2������ɾ��������3������ɾ��\n");
    scanf("%d",&b);
    switch(b)
    {
        case 1:printf("������绰����\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->a)==0)
               {
                   (S.base+i)->f=0;
                   printf("��ɾ����  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
               if(ff==0)
                printf("�Ҳ������û�\n");
               break;
       case 2:printf("����������\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->name)==0)
               {
                   (S.base+i)->f=0;
                   printf("��ɾ����  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
                if(ff==0)
                printf("�Ҳ������û�\n");
               break;
        case 3:printf("����������\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->add)==0)
               {
                   (S.base+i)->f=0;
                   printf("��ɾ����  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
                if(ff==0)
                printf("�Ҳ������û�\n");
               break;
    }
    interface();
}
void change()
{
    void interface();
    int i;
    int ff=0;
    int b;
    char a[15];
    printf("����������\n");
    scanf("%s",a);
    for(i=0;i<20;i++)
      if(strcmp(a,(S.base+i)->name)==0)
               {
                   printf("��Ҫ�޸ĵ��ǣ�  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   printf("����������Ϣ\n");
                   scanf("%s",(S.base+i)->a);
                   scanf("%s",(S.base+i)->name);
                   scanf("%s",(S.base+i)->add);
                   printf("���޸ĳɣ�  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                         ff=1;
               }
                if(ff==0)
                printf("�Ҳ������û�\n");
 
    interface();
}
void write()
{
    void interface();
    int i=0;
    FILE *fp;
    if((fp=fopen("ͨѶ¼.txt","wb"))==NULL)
{
printf("open file error\n");
exit(1);
}
    for(i=0;i<=20;i++)
    {
         int ch=32;
        if((S.base+i)->f==1)
        {
            fprintf(fp,"%s",(S.base+i)->name);fputc(ch,fp);
            fprintf(fp,"%s",(S.base+i)->a);fputc(ch,fp);
            ch=10;
            fprintf(fp,"%s",(S.base+i)->add);fputc(ch,fp);
        }
    }
     fclose(fp);
   interface();
}
void interface()
{
    int i;
    printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
    printf("\t\t\t\t\t�U             �˵�               �U\n");							
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         1--����ͨѶ¼          �U\n");							
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         2--��ʾͨѶ¼          �U\n");							
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         3--������ϵ��          �U\n");
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         4--ɾ����ϵ��          �U\n");
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         5--�޸���ϵ����Ϣ      �U\n");
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         6--���浽�ļ�          �U\n");
    printf("\t\t\t\t\t�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
    printf("\t\t\t\t\t�U         0--�˳�ϵͳ            �U\n");
    printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
    printf("���������ѡ��:\n");
    scanf("%d",&i);
    switch(i)
    {
        case 0:return ;break;
        case 1:shuru();break;
        case 2:print();break;
        case 3:search();break;
        case 4:del();break;
        case 5:change();break;
        case 6:write();break;
    };
}
int main()
{
    system("color F0"); //����д�� red ������ɫ��
    S.base=(struct list *)malloc(20*sizeof(struct list));
    printf("      				****************��ӭʹ��ͨѶ¼��ѯϵͳ*********************\n\n");
    system("date /T");
     system("TIME /T");
        int i;
        for(i=1;i<25;i++)
            d[2*i]=-1*i*i;
        for(i=1;i<25;i++)/*���������ɢ��*/
            d[i+i-1]=i*i;
    interface();
}
