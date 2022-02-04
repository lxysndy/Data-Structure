#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_size 100

/*����շ��������Ľṹ���������Ž���Ȩֵ���ַ���˫�ס����Ӻ��Һ���*/
typedef struct{
    float  weight;//Ȩֵ
    char ch;     //��Ÿýڵ���ַ�
    int parent, lchild, rchild;
}HTNode, *HuffmanTree;
typedef char **HuffmanCode; //ָ��շ��������ָ��

void welcome();    //��ӡ����ѡ�����
void Init(HuffmanTree &HT); //����n���ַ������Ӧ��Ȩֵ������Ȩֵ������������
void HuffmanCreat(HuffmanTree &HT, char *character, float *w, int n);//�����շ��������㷨
void select(HuffmanTree &HT, int j, int *s1, int *s2); //��Ŀǰ�ѽ��õĺշ�������ѡ��parentΪ0��weight��С���������
void EnCoding(HuffmanTree &HT); //����
void Decoding(HuffmanTree &HT); //����
void Print_code(); //��ӡ����õĴ����ļ�
void Print_tree(HuffmanTree &HT); //�԰�͹����ʽ��ӡ��������
int Read_tree(HuffmanTree &HT); //���ļ��ж���շ�����
void find(HuffmanTree &HT, char *code, char *text, int i, int m);//����ʱ����01�ַ���Ѱ����ӦҶ�ӽڵ�ĵݹ��㷨
void Convert_tree(HuffmanTree &HT,unsigned char T[100][100], int s, int *i, int j);//���ڴ��еĺշ�����ת���ɰ�͹����ʽ�ĺշ�����
int n = 0; //ȫ�ֱ�������źշ�����Ҷ�ӽ�����Ŀ

int main()
{
    char choice;
    HuffmanTree HT;
    while (1)
    {
        welcome();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:system("cls");Init(HT); break;
        case 2:system("cls");EnCoding(HT); break;
        case 3:system("cls");Decoding(HT); break;
        case 4:system("cls");Print_code(); break;
        case 5:system("cls");Print_tree(HT); break;
        case 0:exit(1);
        default:printf("Input error!\n");
        }
        getchar();
    }
    return 0;
}

void welcome()//��ӡѡ�����
{
    printf("\t\t\t\t\t\t          HuffmanCoding         \n\n");
    printf("\t\t\t\t\t\t1.��ʼ����������\n");
    printf("\t\t\t\t\t\t2.�Թ����������б���\n");
    printf("\t\t\t\t\t\t3.�Ա����������\n");
    printf("\t\t\t\t\t\t4.��ӡ����������\n");
    printf("\t\t\t\t\t\t5.��ӡ��������\n");
    printf("\t\t\t\t\t\t0.�˳�ϵͳ\n");
    printf("���������ѡ��");
}

/*��ʼ������������n���ַ������Ӧ��Ȩֵ������Ȩֵ������������������������ļ�hfmtree��*/
void Init(HuffmanTree &HT)
{
    FILE *fp;
    int i, n,num;
    float w[max_size]; //w������n���ַ���Ȩֵ
    char character[max_size]; //���n���ַ�
    HuffmanTree HTtest;
    printf("\n�����ַ����� n:");
    scanf("%d", &n);
    HTtest=(HuffmanTree)malloc((2*n-1)*sizeof(HTNode));
    printf("����%d���ַ������Ӧ��Ȩֵ:\n", n);
    for (i = 0; i < n; i++)
    {
        getchar();
        scanf("%c %f",&character[i],&w[i]);      //����n���ַ��Ͷ�Ӧ��Ȩֵ
    }
    HuffmanCreat(HT, character, w, n);    //�����շ�����
    if ((fp = fopen("hfmtree.txt", "w+")) == NULL)
       {
        printf("Open file hfmtree.txt error!\n");
        exit(1);
       }
    num=fwrite(HT+1,sizeof(HTNode),2*n-1,fp);//�������ĺշ����������ļ�������Ԫ������ 
    printf("\n%d\n",num);
    rewind(fp);//���´��ļ� 
    fread(HTtest+1,sizeof(HTNode),2*n-1,fp);//��ȡ 
    for (i=1;i<=2*n-1;i++)
    {
    printf("%c %.2f %d %d %d\n",HTtest[i].ch,HTtest[i].weight,HTtest[i].lchild,HT[i].rchild,HTtest[i].parent);
    }
    printf("\n�����շ������ɹ����ѽ�������ļ�hfmtree.txt��\n");
    fclose(fp);
}

/*�����շ��������㷨*/
void HuffmanCreat(HuffmanTree &HT, char *character, float *w, int n)
{
    int m, i, s1, s2;
    HuffmanTree p;
    if (n <= 1)
        return;
    m = 2 * n - 1;
    HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));
    for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++character, ++w)
    {
        p->ch = *character;
        p->weight = *w;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }//ǰ�漸���ڵ� 
    for (; i <= m; ++i, ++p)
    {
        p->ch = 0;
        p->weight = 0;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }
    for (i = n + 1; i <= m; ++i)
    {
        select(HT, i - 1, &s1, &s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].ch='#';
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }//�¹����ļ����ڵ㣬����˫�׽ڵ� 
}

/*��HT[1]��HT[j]��ѡ��parentΪ0��weight��С��������㣬��s1��s2���������*/
void select(HuffmanTree &HT, int j, int *s1, int *s2)
{
    int i;
    //��weight��С�Ľ��
    for (i = 1; i <= j; i++)
    {
    if (HT[i].parent == 0)
    {
        *s1 = i;
        break;
    }
    }
    for (; i <= j; i++)
    {
    if ((HT[i].parent == 0) && (HT[i].weight < HT[*s1].weight))
        *s1 = i;
    }
    HT[*s1].parent = 1;
    //��weight��С�Ľ��
    for (i = 1; i <= j; i++)
    if (HT[i].parent == 0)
    {
        *s2 = i; break;
    }
    for (; i <= j; i++)
    {
    if ((HT[i].parent == 0) && (i != *s1) && (HT[i].weight < HT[*s2].weight))
        *s2 = i;
    }
}

/*���ļ�tobetrans�е����Ľ��б��룬Ȼ�󽫽�������ļ�codefile��*/
void EnCoding(HuffmanTree &HT)
{
    FILE *fp, *fw;
    int i, f, c, start;
    char *cd;
    HuffmanCode HC;
    if (n == 0)
        n = Read_tree(HT);//���ļ�hfmtree.txt�ж���շ�����,����Ҷ�ӽ����
    //���³������շ������и�Ҷ�ӽڵ���ַ���Ӧ�ĵı��룬������HCָ��Ŀռ���
    {
        HC = (HuffmanCode)malloc((n + 1)*sizeof(char*));
        cd = (char *)malloc(n*sizeof(char));
        cd[n - 1] = '\0';
        for (i = 1; i <= n; ++i)
        {
            start = n - 1;//��Ҷ�ӽڵ㵽�������� 
            for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else cd[--start] = '1';
            HC[i] = (char *)malloc((n - start+1)*sizeof(char));
            strcpy(HC[i], &cd[start]);
        }
        free(cd);
    }

    if ((fp = fopen("tobetrans.txt", "rb")) == NULL)
        printf("Open file tobetrans.txt error!\n");
    if ((fw = fopen("codefile.txt", "wb+")) == NULL)
        printf("Open file codefile.txt error!\n");
    char temp;
    fscanf(fp, "%c", &temp); //���ļ������һ���ַ�
    while (!feof(fp))
    {
        for (i = 1; i <= n; i++)
        if (HT[i].ch == temp) break;    //�ںշ������в����ַ����ڵ�λ��
        for (int r = 0; HC[i][r] != '\0'; r++) //���ַ���Ӧ�ı�������ļ�
            fputc(HC[i][r], fw);
        fscanf(fp, "%c", &temp);        //���ļ�������һ���ַ�
    }
    fclose(fw);
    fclose(fp);
    printf("\n���ļ�hfmtree.txt����ɹ�,����Ѵ���codefile.txt�С�\n\n");
}

/////////////////////////////////////////////////////////////////////////
/*���ļ�codefile�еĴ���������룬��������ļ�textfile��*/
void Decoding(HuffmanTree &HT)
{
    FILE *fp, *fw;
    int m, i;
    char *code, *text, *p;
    if (n == 0)
        n = Read_tree(HT);//���ļ�hfmtree.txt�ж���շ�����,����Ҷ�ӽ����
    if ((fp = fopen("codefile.txt", "rb+")) == NULL)
        printf("Open file codefile.txt error!\n");
    if ((fw = fopen("textfile.txt", "wb+")) == NULL)
        printf("Open file textfile.txt error!\n");
    code = (char *)malloc(sizeof(char));
    fscanf(fp, "%c", code);        //���ļ�����һ���ַ�
    for (i = 1; !feof(fp); i++)
    {
        code = (char *)realloc(code, (i + 1)*sizeof(char)); //���ӿռ�
        fscanf(fp, "%c", &code[i]);     //���ļ�������һ���ַ�
    }
    code[i - 1] = '\0';
    //����codefile.txt�ļ��е��ַ���ȫ�����룬�����code������
    text = (char *)malloc(100 * sizeof(char));
    p = text;
    m = 2 * n - 1;
    if (*code == '0')
        find(HT, code, text, HT[m].lchild, m);   //�Ӹ��ڵ��������ȥ��
    else
        find(HT, code, text, HT[m].rchild, m);   //�Ӹ��ڵ��������ȥ��
    for (i = 0; p[i] != '\0'; i++) //������õ��ַ������ļ�textfile.txt��
        fputc(p[i], fw);
    fclose(fp);
    fclose(fw);
    printf("\n��codefile.txt�ļ�����ɹ�������Ѵ���textfile.txt�ļ���\n\n");
}

/*���ļ�codefi1e�Խ��ո�ʽ��ʾ���ն���,ÿ��50�����롣ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�codeprint�С�*/
void Print_code()
{
    FILE *fp, *fw;
    char temp;
    int i;
    if ((fp = fopen("codefile.txt", "rb")) == NULL)
        printf("Open file codefile.txt error!\n");
    if ((fw = fopen("codeprint.txt", "wb+")) == NULL)
        printf("Open file codeprint.txt error!\n");
    printf("\n�ļ�codefi1e�Խ��ո�ʽ��ʾ����:\n");
    fscanf(fp, "%c", &temp);        //���ļ�����һ���ַ�
    for (i = 1; !feof(fp); i++)
    {
        printf("%c", temp);
        if (i % 50 == 0) printf("\n");
        fputc(temp, fw);   //�����ַ������ļ�codeprint.txt��
        fscanf(fp, "%c", &temp);        //���ļ�����һ���ַ�
    }
    printf("\n\n���ַ���ʽ�ı�����д���ļ�codeprint.txt��.\n\n");
    fclose(fp);
    fclose(fw);
}

/*�������ڴ��еĹ���������ʾ����Ļ�ϣ�ͬʱ�����ַ���ʽ�Ĺ�������д���ļ�treeprint�С�*/
void Print_tree(HuffmanTree &HT)
{
    unsigned char T[100][100];
    int i, j, m = 0;
    FILE *fp;
    if (n == 0)
        n = Read_tree(HT);//���ļ�hfmtree.txt�ж���շ�����,����Ҷ�ӽ����

    Convert_tree(HT,T, 0, &m, 2 * n - 1); //���ڴ��еĺշ�����ת����������������T��
    if ((fp = fopen("treeprint.txt", "wb+")) == NULL)
        printf("Open file treeprint.txt error!\n");
    printf("\n��ӡ�շ�������\n");
    for (i = 1; i <= 2 * n - 1; i++)
    {
        for (j = 0; T[i][j] != 0; j++)
        {
            if (T[i][j] == ' ')
                {
                    printf("  ");
                    fputc(T[i][j],fp);
               }
            else
            {
                printf("%d", T[i][j]);
                fprintf(fp, "%d\n", T[i][j]);
            }
        }
        printf("\n");
    }
    fclose(fp);
    printf("\n���ַ���ʽ�Ĺ���������д���ļ�treeprint.txt��.\n\n");

}
//////////////////////////////////////////////////////////////////////////////////
/*���ļ�hfmtree.txt�ж���շ�����������Ҷ�ӽڵ���*/
int Read_tree(HuffmanTree &HT)
{
    FILE *fp;
    int i, n;
    HT = (HuffmanTree)malloc(sizeof(HTNode));
    if ((fp = fopen("hfmtree.txt", "r")) == NULL)
        printf("Open file hfmtree.txt error!\n");
    for (i = 1; !feof(fp); i++)
    {
        HT = (HuffmanTree)realloc(HT, (i + 1)*sizeof(HTNode)); //���ӿռ�
        fread(&HT[i], sizeof(HTNode), 1, fp); //����һ���ڵ���Ϣ
    }
    fclose(fp);
    n = (i - 1) / 2;
    return n;
}
////////////////////////////////////////////////////////////////
/*����ʱ����01�ַ���Ѱ����ӦҶ�ӽڵ�ĵݹ��㷨*/
void find(HuffmanTree &HT, char *code, char *text, int i, int m)
{

    if (*code != '\0') //������δ����
    {
        code++;
        if (HT[i].lchild == 0 && HT[i].rchild == 0)   //���ҵ�Ҷ�ӽڵ�
        {
            *text = HT[i].ch; //��Ҷ�ӽڵ���ַ�����text��
            text++;
            if ((*code == '0'))
                find(HT, code, text, HT[m].lchild, m); //�����Ӹ��ڵ����������
            else
                find(HT, code, text, HT[m].rchild, m); //�����Ӹ��ڵ����������
        }
        else   //�������Ҷ�ӽڵ�
        if (*code == '0')
            find(HT, code, text, HT[i].lchild, m);   //�Ӹýڵ��������ȥ��
        else
            find(HT, code, text, HT[i].rchild, m);   //�Ӹýڵ��������ȥ��

    }
    else
        *text = '\0'; //�������
}
////////////////////////////////////////////////////////////////////////
/*���ڴ��еĺշ�����ת���ɱ���ʽ�ĺշ�������ת���ɴ�ӡ�������Ǹ����������*/
void Convert_tree(HuffmanTree &HT,unsigned char T[100][100], int s, int *i, int j)
{
    int k, l;
    l = ++(*i);
    for (k = 0; k < s; k++)
        T[l][k] = ' ';
    T[l][k] = HT[j].weight;
    if (HT[j].lchild)
        Convert_tree(HT,T, s + 1, i, HT[j].lchild);
    if (HT[j].rchild)
        Convert_tree(HT,T, s + 1, i, HT[j].rchild);
    T[l][++k] = '\0';
}
