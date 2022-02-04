#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/timeb.h>

//#define MAX 25000  
#define MAX 25000

/*
n�����򷽷������ǴӴ�С����
û��̫�ο����˵ĳ��򣬴󲿷��Ǹ��ݶ�����ĥ��
������©����������ָ��
*/

//����������������������
void swap(int*a,int*p)
{
    int temp = *a;
    *a = *p;
    *p = temp;
}

//ð������
void bubbleSort(int* arr,int len)
{
    int i,j;
    //������Ͻ�
    for(i=0;i<len;i++)
    {
        //һ�㵼����i+1���Ժ��Ѿ��ź���
        for(j=1;j<len-i;j++)
        {
            //���һֱð�ݵ������ȥ
            if(arr[j-1]>arr[j])
            {
                swap(&arr[j-1],&arr[j]);
            }
        }
    }
}

//��������
//�ӵ�1������ʼ������ʼ��������i����һ��Ҫ�ŵ�ʹ��ǰi�������������ġ�
void insertSort(int* arr,int len)
{
    int i,j;
    for(i=0;i<len;i++)
    {
        for(j=i;j>0;j--)
        {
            if(arr[j]<arr[j-1])
            {
                swap(&arr[j],&arr[j-1]);
            }else
            {
                //�Ѿ������Ǹ�Ԫ��С�˾���ǰ�˳�
                break;
            }
        }
    }
}

//��������
void quickSort(int* arr,int start,int end)
{
    //�ݹ�����Ҫ�ľ��������˳�����������
    if(start>=end)
    {
        return;
    }
    int i = start;
    int j = end;
    int temp = arr[i];
    //�����ָ��jһֱûС����ָ��i��һֱ��
    while(i<j)
    {
        //�ȴ��ұ��ұȻ�׼С�ģ��ҵ��ͻ�׼��������Ҫ����jֵ
        while(i<j)
        {
            if(arr[j]<temp)
            {
                swap(&arr[j],&arr[i]);
                break;
            }
            j--;
        }

        //�ұ��ҵ�һ���Ȼ�׼С��֮���ֵ�����ұȻ�׼��ģ�Ȼ�������ճ���jλ�ý���
        while(i<j)
        {
            if(arr[i]>temp)
            {
                swap(&arr[j],&arr[i]);
                break;
            }
            i++;
        }

    }
    //�������
    quickSort(arr,start,i-1);
    //���Ұ���
    quickSort(arr,i+1,end);
}

void mergeSort(int* arr,int start,int end)
{
    if(start>=end)
    {
        return;
    }
    int i = start;
    int mid = (start+end)/2;
    int j = mid + 1;
    mergeSort(arr,i,mid);
    mergeSort(arr,j,end);

    //�ϲ�
    //��ʵ�Ҿ��ò����������Ŀռ�Ҳ�У���������������һ���ܼ��ٿռ䣬�����ٶȿ϶�����Ӱ��
    int* temp = (int*)malloc((end-start+1)*sizeof(int));
    int index = 0;
    //��ʼ�Ա����������У�ͷ����С���Ǹ����ŵ��¿ռ�
    while(i<=mid&&j<=end)
    {
        if(arr[i]<=arr[j])
        {
            temp[index++] = arr[i++];
        }else
        {
            temp[index++] = arr[j++];
        }
    }
    //����һ�������ǻ�û�з���ģ������ٱ���һ��û�����
    while(i<=mid)
    {
        temp[index++] = arr[i++];
    }
    while(j<=end)
    {
        temp[index++] = arr[j++];
    }
    //�����ٰ��¿ռ��Ԫ�طŻؾɿռ�
    int k = start;
    for(k;k<=end;k++)
    {
        arr[k] = temp[k-start];
    }
    free(temp);
}
//������ 
void adjust(int* arr,int len,int index)
{
    //�����������Ѻ��ӡ������е����ֵ�ŵ����׽ڵ�
    //indexΪ�������ڵ��±�,һ��ʼ�������
    int max = index;
    int left = 2*index+1;//����
    int right = 2*index+2;//�Һ���
    if(left<len && arr[left] > arr[max])
    {
        max = left;
    }
    if(right<len && arr[right] > arr[max])
    {
        max = right;
    }
    //������׽ڵ㲻�����
    if(max!=index)
    {
        //һ���ϲ�ڵ�Ӱ����ĳ�����ӽڵ㣬��Ҫ�۲���������ӽڵ�Ϊ���ڵ�������ǲ���Ҳ���Ǵ󶥶���
        swap(&arr[index],&arr[max]);
        //��Ϊ�����˽�������Ҫ���������ܵ�Ӱ��ĺ��ӽڵ�
        //***************************************
        adjust(arr,len,max);//��仰�ǳ��ǳ��ؼ�
        //***************************************
        /*
            ֻ�и��׺ͺ��ӽڵ㷢���˽��������м����������ӵı�Ҫ����������ڲ���������ݹ飬�������Ч�������ð�ݺõ���ȥ
            �����д���������棬��Ȼ����pk�������ţ����ô��Ϳ��ŵĲ��ֻ��С����λ��������������С��������ʱ��
            ������һ���ŵ��ǿռ临�Ӷ�Ҳ����
        */
    }
}
//��Ҫ���򲿷�
void heapSort(int* arr,int len)
{
    
    int i = len/2-1;
    for(i;i>=0;i--)
    {
        adjust(arr,len,i);
    }
    swap(&arr[0],&arr[len-1]);
    //�ڶ���֮��ֻ��Ҫ�Ӹ��ڵ���ϵ��µ���������û����������ֱ�ӿ����˳�ѭ����
    //΢���õ��󶥶ѣ���Ϊֻ�жѶ���������ѣ�
    int j = len -1; //ȥ��β�ڵ������鳤��
    //�����ֵ���������
    for(j;j>0;j--)
    {
        adjust(arr,j,0);
        swap(&arr[0],&arr[j-1]);
    }
}

//����ʱ�䣬��ȷ������
long getTime()
{
    struct timeb tb;
    ftime(&tb);//ȡ�õ�ǰ��ʱ�� 
    //ǰ���Ǻ��룬������΢��
    return tb.time*1000+tb.millitm;
}

//С��������
void test()
{
    int* a1 = (int*)malloc(MAX*sizeof(int));
    int* a2 = (int*)malloc(MAX*sizeof(int));
    int* a3 = (int*)malloc(MAX*sizeof(int));
    int* a4 = (int*)malloc(MAX*sizeof(int));
    int* a5 = (int*)malloc(MAX*sizeof(int));
    int i = 0;
    srand(time(NULL));
    for(i;i<MAX;i++)
    {
        int temp = rand()%(MAX+1);
//        int temp = i;//�������
//        int temp = MAX-i-1;//�������

        a1[i] = temp;
        a2[i] = temp; 
        a3[i] = temp; 
        a4[i] = temp; 
        a5[i] = temp; 
    }


    long t1 = getTime();


    //ð������
    bubbleSort(a1,MAX);
    long t2 = getTime();
    printf("ð��������%d��������ݺ�ʱ%ld����\n",MAX,t2-t1);

    //��������
    insertSort(a2,MAX);
    long t3 = getTime();
    printf("����������%d��������ݺ�ʱ%ld����\n",MAX,t3-t2);

    //��������
    quickSort(a3,0,MAX-1);
    long t4 = getTime();
    printf("����������%d��������ݺ�ʱ%ld����\n",MAX,t4-t3);

    //�鲢����
    mergeSort(a4,0,MAX-1);
    long t5 = getTime();
    printf("�鲢������%d��������ݺ�ʱ%ld����\n",MAX,t5-t4);

    //������
    heapSort(a5,MAX);
    long t6 = getTime();
    printf("��������%d��������ݺ�ʱ%ld����\n",MAX,t6-t5);
}

int main()
{
    test();
    return 0;
}

