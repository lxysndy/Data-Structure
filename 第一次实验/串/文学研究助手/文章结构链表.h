
typedef struct WORD{
	char letter;
	struct WORD *next;
}word;                //���ʽڵ� 

typedef struct{
	word *first;
	word *last;
}row;                  //�нṹ�ڵ� 

typedef struct Row{
	row r;
	struct Row *next;
}ROW;                    //�нṹ 

typedef struct{
	ROW *first;
	ROW *last;
}article;            //���½ṹ 

void create_article(article *a)      //�������½ṹ 
{
	a->first = (ROW*)malloc(sizeof(ROW));
	a->last = a->first;
	a->first->next = NULL;
	a->first->r.first = (word*)malloc(sizeof(word));
	a->first->r.last = a->first->r.first;
	a->first->r.first->next = NULL;
	a->first->r.first->letter = 1; 
}

void add_row(article *a)       //����� 
{
	ROW *p;
	p = (ROW*)malloc(sizeof(ROW));
	p->next = NULL;
	p->r.first = (word*)malloc(sizeof(word));
	p->r.last = p->r.first;
	p->r.first->letter = a->last->r.first->letter+1;
	a->last->next = p;
	a->last = p;
}

void add_word(row *r,char ch)  //�����ĸ 
{
	word *p;
	p = (word*)malloc(sizeof(word));
	p->letter = ch;
	p->next = NULL;
	r->last->next = p;
	r->last = p;
}
