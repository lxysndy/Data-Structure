#include<stdio.h>
#include<stdlib.h>
//���ֲ��ҷǵݹ鷽ʽ
int HalfSearch(int a[],int low,int high,int key)
{
	int mid;
 while(low<=high)
 {
 mid=(low+high)/2;//���ֵ�
 if(a[mid]==key) return mid;
 else if(a[mid]<key) low=mid+1;
 else high=mid-1;
 }
 return -1;
}
//���ֲ��ҵݹ鷽ʽ
int HalfSearch1(int a[],int low,int high,int key)
{
 int mid;
 if(low>high) return -1;//û�ҵ����ݹ����
 else{
 mid=(low+high)/2;
 if(a[mid]==key) return mid;//�ҵ��ˣ��ݹ����
 else if(a[mid]<key) return HalfSearch(a,mid+1,high,key);//�ҵݹ�
 else return HalfSearch(a,low,mid-1,key);//��ݹ�
 }
}
int main(void)
{
 int a[10]={12,22,34,65,76,78,89,90,121,145};
 int n;
 int key;
 printf("enter data to key:\n");
 scanf("%5d",&key);
 n=HalfSearch1(a,0,9,key);//Ҳ����ʹ����һ������ 
 if(n==-1) printf("not found!\n");//û�ҵ�
 else printf("λ���ڣ�a[%d]",n);
 return 0;
}

