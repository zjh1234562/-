#define TRUE 1
#define m 3
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define OK 1
#define ERROR 0

typedef struct ReaderNode {//借阅者结构体
	int number;//借书号
	int dyear;  //截至日期
	int dmonth;
	int dday;
	ReaderNode *next;//下一个借阅的人
}ReaderNode, *ReaderType;
//书的结构体  
typedef struct BookNode {
	int key;   //图书的书号 
	char bname[20]; // 书名
	char writter[20];  //作者
	int left;  //存货
	int total;  //总量
	ReaderType reader;
}BookNode, *BookType;


typedef int KeyType;
typedef struct BTNode {
	int keynum;//结点中关键字个数
	KeyType key[m +1];   //关键字数组
	struct BTNode *parent;//父节点
	struct BTNode *ptr[m +1];
	BookNode *recptr[m + 1];
}BTNode, *BTree;

typedef struct {//B树查找结果类型
	BTNode *p;//指向找到的节点
	int i;
	int tag;
}Result;



typedef struct QNode {
	int data;
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;




#include <stdio.h>
#include <malloc.h>
#include <stdlib.h> 
#include <string.h>

void InitBTree(BTree &t) {//初始化B树 
	t = NULL;
}

int Search(BTree p, int k) {//查找插入位置
	int i;
	for(i = 0; i < p->keynum&&p->key[i + 1] <= k; i++);
	return i;
}

Result	SearchBTree(BTree T, KeyType k)
{
	int		i = 1;
	BTree	p = T, q = NULL;						// 初始化，p指向待查结点，q指向p的双亲
	int		found = 0;
	while (p && !found)
	{
		i = Search(p, k);							// 查找k的位置使p->key[i]<=k<p->key[i+1]
		if (i > 0 && k == p->key[i])	found = TRUE;
		else {										// 未找到，则查找下一层
			q = p;
			p = p->ptr[i];
		}
	}
	if (found) { Result	r = { p, i, 1 };	return r; }	// 查找成功
	else { Result	r = { q, i, 0 };	return r; }	// 查找不成功，返回k的插入位置信息

}


void split(BTree &q, int s, BTree &ap) {
	//将q结点分裂成两个结点，前一半保留，后一半移入新结点ap
	int i, n = q->keynum;
	ap = (BTNode*)malloc(sizeof(BTNode));//生成新结点ap
	ap->ptr[0] = q->ptr[s];
	for (i = s + 1; i <= m; i++) {//后一半移入ap结点
		ap->key[i - s] = q->key[i];
		ap->ptr[i - s] = q->ptr[i];
		ap->recptr[i - s] = q->recptr[i];
	}
	ap->keynum = n - s;//计算ap的关键字个数
	ap->parent = q->parent;
	for (i = 0; i <= m - s; i++) {
		if (ap->ptr[i])
			ap->ptr[i]->parent = ap;//将ap所有孩子结点指向ap
	}
	q->keynum = s - 1;//q结点的前一半保留，修改keynum
}

void newroot(BTree &T, BTree p, int k, BTree ap, BookNode *recptr) {//生成新的根结点
	T = (BTNode*)malloc(sizeof(BTNode));
	T->keynum = 1;
	T->ptr[0] = p;
	T->ptr[1] = ap;
	T->key[1] = k;
	T->recptr[1] = recptr;  //T的子树ap的父亲指针
	if (p != NULL) p->parent = T;
	if (ap != NULL) ap->parent = T;
	T->parent = NULL;//新根的双亲是空指针
}

void Insert(BTree &q, int i, int k, BTree ap, BookNode *recptr) {//k和ap分别插到q->key[i+1]和q->ptr[i+1]
															   //并插入关键字为k的记录recprt
	int j, n = q->keynum;
	for (j = n; j > i; j--) {
		q->key[j + 1] = q->key[j];//关键字指针向后移一位
		q->ptr[j + 1] = q->ptr[j];//孩子结点指针向后移一位
		q->recptr[j + 1] = q->recptr[j];
	}
	q->key[i + 1] = k;//赋值
	q->ptr[i + 1] = ap;
	q->recptr[i + 1] = recptr;
	if (ap != NULL) ap->parent = q;
	q->keynum++;//关键字数+1
}

int InsertBTree(BTree &T, KeyType k, BTree q, int i, BookNode *rec)
{
	BTree ap = NULL;
	int finished = FALSE;
	if (!q)    newroot(T, NULL, k, NULL, rec);	// T是空树，生成仅含关键字K的根结点*T
	else {
		while (!finished)
		{
			Insert(q, i, k, ap, rec);			// 将k和ap分别插入到q->key[i+1]和q->ptr[i+1]
			if (q->keynum < m) finished = TRUE; // 插入完成
			else {
				split(q, (m + 1) / 2, ap);			// 分裂结点Q
				k = q->key[(m + 1) / 2];
				rec = q->recptr[(m + 1) / 2];
				if (q->parent)
				{							// 在双亲结点*q中查找k的插入位置
					q = q->parent;
					i = Search(q, k);
				}
				else finished = OVERFLOW;		// 根节点已分裂为*q和*ap两个结点
			}
		}
		if (finished == OVERFLOW)				// 根结点已分裂为结点*q和*ap
			newroot(T, q, k, ap, rec);			// 需生成新根结点*T,q和ap为子树指针
	}
	return OK;
}


void InsertBook(BTree &L, BookType B, Result res) {
	if (res.tag == 0)
		InsertBTree(L, B->key, res.p, res.i, B);
	//书库中不存在该书，则插入
	else {
		BookType b = res.p->recptr[res.i];
		b->left = b->left + B->total;//现存量增加
		b->total = b->total + B->total;//总库存增加
	}
}

void TakePlace(BTree &q, int &i) {
	//*q结点的第i个关键字为k，用q的后继关键字代替q，且令q指向后继所在结点
	BTree p = q;
	q = q->ptr[i];
	while (q->ptr[0]) q = q->ptr[0]; //查找p的后继
	p->key[i] = q->key[1]; //记录代替
	p->recptr[i] = q->recptr[1];
	i = 1;  //代替后应该删除q所指结点的第1个关键字
}

void Del(BTree q, int i) {
	//删除q所指结点第i个关键字及其记录
	for (; i < q->keynum; i++) {//关键字和记录指针前移
		q->key[i] = q->key[i + 1];
		q->recptr[i] = q->recptr[i + 1];
	}
	q->keynum--;//关键字数目减1
}

int	Borrow(BTree q)
// 若q的兄弟结点关键字大于(m-1)/2,则从兄弟结点上移最小（或最大）的关键字到双亲结点，
// 而将双亲结点中小于(或大于）且紧靠该关键字的关键字下移至q中,并返回OK，否则返回EREOR。
{
	int	i;
	BTree p = q->parent, b = NULL;					// p指向q的双亲结点
	for (i = 0; p->ptr[i] != q; i++);			// 查找q在双亲p的子树位置
	if (i >= 0 && i + 1 <= p->keynum && p->ptr[i + 1]->keynum > (m - 1) / 2)
	{										// 若q的右兄弟关键字个数大于(m-1)/2
		b = p->ptr[i + 1];						// b指向右兄弟结点
		q->ptr[1] = b->ptr[0];					// 子树指针也要同步移动
		q->key[1] = p->key[i + 1];				// 从父节点借第i+1个关键字
		q->recptr[1] = p->recptr[i + 1];
		p->key[i + 1] = b->key[1];				// b第一个关键字上移到父节点
		p->recptr[i + 1] = b->recptr[1];
		for (i = 1; i <= b->keynum; i++)			// b第一个关键字上移，需把剩余记录前移一位
		{
			b->key[i] = b->key[i + 1];
			b->recptr[i] = b->recptr[i + 1];
			b->ptr[i - 1] = b->ptr[i];
		}
	}
	else if (i > 0 && p->ptr[i - 1]->keynum > (m - 1) / 2)
	{										// 若q的左兄弟关键字个数大约(m-1)/2
		b = p->ptr[i - 1];						// b指向左兄弟结点
		q->ptr[1] = q->ptr[0];
		q->ptr[0] = b->ptr[b->keynum];
		q->key[1] = p->key[i];					// 从父节点借第i个关键字
		q->recptr[1] = p->recptr[i];
		p->key[i] = b->key[b->keynum];			// 将b最后一个关键字上移到父节点
		p->recptr[i] = b->recptr[b->keynum];
	}
	else return ERROR;							// 无关键字大于(m-1)/2的兄弟
	q->keynum++;
	b->keynum--;
	for (i = 0; i <= q->keynum; i++)
		if (q->ptr[i]) q->ptr[i]->parent = q;	// 刷新q的子结点的双亲指针
	return OK;
}

void Combine(BTree &q) {
	int i, j;
	BTree p = q->parent, b = NULL;//p指向q的父亲
	for (i = 0; p->ptr[i] != q; i++);//查找q在父亲p中的子树位置
	if (i == 0) {//若为0，则需合并为兄弟的第一个关键字
		b = p->ptr[i + 1];
		for (j = b->keynum; j >= 0; j--) {//将b的关键字和记录后移一位
			b->key[j + 1] = b->key[j];
			b->recptr[j + 1] = b->recptr[j];
			b->ptr[j + 1] = b->ptr[j];
		}
		b->ptr[0] = q->ptr[0];//合并
		b->key[1] = p->key[1];
		b->recptr[1] = p->recptr[1];
	}
	else if (i > 0) {//若q在父亲的子树位置大于0，需合并为兄弟b的最后一个关键字
		b = p->ptr[i - 1];
		b->key[b->keynum + 1] = p->key[i];//合并
		b->recptr[b->keynum + 1] = p->recptr[i];
		b->ptr[b->keynum + 1] = q->ptr[0];
	}
	if (i == 0 || i == 1)//若i为0或1，需将父结点p关键字前移一位
		for (; i < p->keynum; i++) {
			p->key[i] = p->key[i + 1];
			p->ptr[i] = p->ptr[i + 1];
			p->recptr[i] = p->recptr[i + 1];
		}
	p->keynum--;
	b->keynum++;
	free(q);
	q = b;   //q指向修改的兄弟结点
	for (i = 0; i <= b->keynum; i++)
		if (b->ptr[i]) b->ptr[i]->parent = b;//刷新b的子结点的双亲指针
}



int DeleteBTree(BTree &p, KeyType k) {
	KeyType	x = k;
	BTree	q, b = NULL;
	int		finished = FALSE, i = 1;
	Result res = SearchBTree(p, k); //查找关键词k
	if (res.tag == 0)  return ERROR;//没有找到k
	else
	{
		q = res.p;
		i = res.i;
		if (q->ptr[0])  //q是非底层节点,那就找大于q节点的最小节点的关键子来代替，也就是右树最下面的最左叶子节点
			TakePlace(q, i);
		Del(q, i);   //直接删除q，上面已经处理过不是叶子节点的了，所以q都是指向叶子节点的
		if (q->keynum >= (m - 1) / 2 || !q->parent)		// 若删除后关键字个数不小于(m-1)/2或q是根节点
		{
			finished = TRUE;					// 删除完成
			if (q->keynum == 0) p = NULL;		// 若q的关键字个数为0 ，则为空树
		}
		while (!finished)//删完关键字个数不符合要求
		{
			if (Borrow(q))	finished = TRUE;	// 若q的相邻兄弟结点关键字大于(m-1)/2,则从该
												// 兄弟结点上移一个最大（或最小）关键字到
												// 父节点，从父节点借一关键字到q
			else {								// 若q相邻兄弟关键字个数均等于┌m /2┑-1
				Combine(q);	// 将q中的剩余部分和双亲中的相关关键字合并至q的一个兄弟中
				q = q->parent;					// 检查双亲
				if (q == p && p->keynum == 0)	// 若被删结点的父节点是根T且T的关键字个数为0
				{
					p = p->ptr[0];				// 新根	
					p->parent = NULL;
					free(q);					// 删除原双亲结点
					finished = TRUE;
				}
				else if (q->keynum >= m / 2) finished = TRUE;
			}								// 合并后双亲关键字个数不少于(m-1)/2，完成
		}
	}
	return OK;
}

int DeleteBook(BTree &L, BookType B) {
	//如果书库中存在B书，则从书库中删除B书的信息，并返回OK，否则返回ERROR
	if (DeleteBTree(L, B->key)) return OK;//删除成功
	else return ERROR;//删除失败
}

int Borrowbook(BTree L, BookType B, ReaderType R) {
	ReaderType r;
	if (B->left)
	{

		if (!B->reader) { B->reader = R; }//没有人借过
		else//有人借过
		{
			for (r = B->reader; r->next; r = r->next);
			r->next = R;
		}
		B->left--;
		return OK;
	}
	else return ERROR;
}

void Returnbook(BTree L, BookType B, int id,FILE *fp) {
	ReaderType r;//指向找到的借阅者
	ReaderType r2;//r的前一位
	if (B->reader->number == id) { r = B->reader; B->reader = r->next; }//解决还书是第一个人
	else
	{
		for (r = B->reader; r->number != id; r = r->next) {
			r2 = r;
		}
		r2->next = r->next;//只能解决不是第一个借阅者还书
	}
	B->left++;
	free(r);
	printf("还书成功\n");
	fprintf(fp,"还书成功\n");
}

void BTrave(BTree t, char s[20], FILE *fp) {//打印出作者的所有作品
	if (t == NULL)  return;
	int	i;
	for (i = 1; i <= t->keynum; i++)
	{
		if (strcmp(t->recptr[i]->writter, s) == 0)//如果找到作者
		{
			//printf("作者：%s\n", t->recptr[i]->writter);
			printf("书名：%s\n", t->recptr[i]->bname);
			fprintf(fp,"书名：%s\n", t->recptr[i]->bname);
		}
	}
	for (i = 0; i <= t->keynum; i++)				// 递归显示子树结点关键字
		BTrave(t->ptr[i],s,fp);
}



void printBtree(BTree t,int x, FILE *fp) {
	if (t == NULL)  return;
	int	i;
	printf("\n");
	fprintf(fp,"\n");
	for (i = 0; i <= x; i++) { putchar(' '); fprintf(fp, " ");}		// 缩进x
	for (i = 1; i <= t->keynum; i++)
	{
		printf("%d,", t->key[i]);
		fprintf(fp,"%d,", t->key[i]);
	}
	for (i = 0; i <= t->keynum; i++)				// 递归显示子树结点关键字
		printBtree(t->ptr[i], x + 7,fp);
}

void printbook_reader(BTree T, BookType B, FILE *fp) {
	printf("图书书号为：%d\n", B->key);
	printf("图书作者：%s\n", B->writter);
	printf("图书书名为：%s\n", B->bname);
	printf("图书库存为：%d\n", B->left);
	printf("图书总量为：%d\n", B->total);
	fprintf(fp,"图书书号为：%d\n", B->key);
	fprintf(fp,"图书作者：%s\n", B->writter);
	fprintf(fp,"图书书名为：%s\n", B->bname);
	fprintf(fp,"图书库存为：%d\n", B->left);
	fprintf(fp,"图书总量为：%d\n", B->total);
	ReaderType r;
	ReaderType dline = B->reader;
	if (!B->reader) {printf("该书没有借阅者\n"); fprintf(fp,"该书没有借阅者\n");}//没有人借
	else   //有人借
	{
		for (r = B->reader; r; r = r->next)
		{
			printf("借阅者:%d,到期时间：%d-%d-%d\n", r->number, r->dyear, r->dmonth, r->dday);
			fprintf(fp,"借阅者:%d,到期时间：%d-%d-%d\n", r->number, r->dyear, r->dmonth, r->dday);
			if (dline->dyear > r->dyear)
			{
				dline = r; continue;
			}
			else if (dline->dyear == r->dyear&&dline->dmonth > r->dmonth)
			{
				dline = r; continue;
			}
			else if (dline->dyear == r->dyear&&dline->dmonth == r->dmonth&&dline->dday > r->dday)
				dline = r;
		}
	}
	printf("最早到期是借阅者:%d   到期时间为：%d-%d-%d\n",dline->number, dline->dyear, dline->dmonth, dline->dday);
	fprintf(fp,"最早到期是借阅者:%d   到期时间为：%d-%d-%d\n", dline->number, dline->dyear, dline->dmonth, dline->dday);
}


int InitQueue(LinkQueue &Q) {//初始化队列
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		exit(0);
	Q.front->next = NULL;
	return 1;
}
int QueueEmpty(LinkQueue Q) {//判断队列是否为空
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}
int EnQueue(LinkQueue &Q, int e) {//进队
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(0);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}
int DeQueue(LinkQueue &Q, int &e) {//出队
	QueuePtr p;
	if (Q.front == Q.rear)
		return 0;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return e;
}

void showQueue(LinkQueue Q ,FILE *fp) {//显示预约的人
	QueuePtr p=Q.front->next;
	printf("当前预约的有用户(ID)：");
	fprintf(fp,"当前预约的有用户(ID)：");
	while (p) {
		printf("ID:%d   ",p->data);
		fprintf(fp,"ID:%d   ", p->data);
		p = p->next;
	}
}

int countQueue(LinkQueue Q) {//统计预约人数
	QueuePtr p = Q.front->next;
	int i = 0;
	while (p) {
		i++;
		p = p->next;
	}
	return i;
}




void main() {
	BookType B;
	BTree T = NULL;
	Result res;
	int booknum;
	char flag;
	ReaderType R;
	LinkQueue Q;
	int queue=InitQueue(Q);//初始化预约队列
	char s[20]= "aa";//查找的作者名
	while (1)
	{
		printf("选择相应数字的功能：\n");
		printf("1:采编入库\n");
		printf("2:清除库存\n");
		printf("3:借阅\n");
		printf("4:归还\n");
		printf("5:凹入表显示\n");
		printf("6:查找某书信息及所有的借阅者\n");
		printf("7:查询某作者的全部作品\n");
		printf("8:预约借书\n");
		printf("9:显示预约借书人数\n");
		int choice;
		scanf("%d",&choice);
		FILE *fp = NULL;  //文件
		fp = fopen("Log.txt", "a+");//追加
		switch (choice)
		{
		case 1:
			fprintf(fp, "采编入库\n");
			B = (BookType)malloc(sizeof(BookNode));
			printf("请输入要入库的书号：\n");
			fprintf(fp,"请输入要入库的书号：\n");
			fflush(stdin);
			scanf_s("%d", &B->key);
			fprintf(fp,"%d\n",B->key);
			getchar();
			res = SearchBTree(T, B->key);
			if (!res.tag) {
				fflush(stdin);
				printf("请输入该书书名：\n");
				fprintf(fp, "请输入该书书名：\n");
				fflush(stdin);
				gets_s(B->bname);
				fprintf(fp, "%s\n", B->bname);
				printf("请输入该书作者：\n");
				fprintf(fp,"请输入该书作者：\n");
				fflush(stdin);
				gets_s(B->writter);
				fprintf(fp,"%s\n", B->writter);
				printf("请输入入库数：\n");
				fprintf(fp, "请输入入库数：\n");
				fflush(stdin);
				scanf_s("%d", &B->left);
				fprintf(fp, "%d\n", B->left);
				B->total = B->left;
				B->reader = NULL;  //初始假设没有人借过这本书
				InsertBook(T, B, res);
				printf("用凹入表形式显示B树如下：\n");
				fprintf(fp,"用凹入表形式显示B树如下：\n");
				printBtree(T, 8,fp);
				break;
			}
			else {//图书已存在，只增加库存
				printf("书库已有该书记录，请输入增加的册数：\n");
				fprintf(fp, "书库已有该书记录，请输入增加的册数：\n");
				fflush(stdin);
				scanf_s("%d", &B->total);
				fprintf(fp, "%d", B->total);
				InsertBook(T, B, res);
				B = res.p->recptr[res.i];
				printf("用凹入表形式显示B树如下：\n");
				fprintf(fp, "用凹入表形式显示B树如下：\n");
				printBtree(T,8,fp);
				printf("新书入库操作完成！\n");
				fprintf(fp, "新书入库操作完成！\n");
				system("pause");
				break;
			}
			fclose(fp);
			break;
		case 2://清空库存
			printf("请输入要删除的图书书号：\n");
			fprintf(fp,"请输入要删除的图书书号：\n");
			fflush(stdin);
			scanf_s("%d", &booknum);
			fprintf(fp, "%d\n", booknum);
			res = SearchBTree(T, booknum);
			if (res.tag) {
				B = res.p->recptr[res.i];
				//printBtree(B);
				printf("\n您确认删除上面的图书<Y确认，其余按键返回主菜单>?");
				fprintf(fp,"\n您确认删除上面的图书<Y确认，其余按键返回主菜单>?");
				fflush(stdin);
				getchar();
				flag = getchar();
				fprintf(fp,"%c\n", flag);
				if (flag == 'Y' || flag == 'y') {
					DeleteBook(T, B);
					printf("\n清除完毕！\t删除后用凹入表显示B树如下：\n");
					fprintf(fp,"\n清除完毕！\t删除后用凹入表显示B树如下：\n");
					printBtree(T, 8,fp);
				}
			}
			else {
				printf("\n书库不存在此书，删除失败！\n");
				fprintf(fp,"\n书库不存在此书，删除失败！\n");
			}
			printf("\t");
			fprintf(fp,"\t");
			fclose(fp);
			system("pause");
			break;
		case 3: 
			char yn;
			int e;
			R = (ReaderType)malloc(sizeof(ReaderNode));
			R->next = NULL;
			printf("请输入借阅图书书号：\n");
			fprintf(fp,"请输入借阅图书书号：\n");
			fflush(stdin);
			scanf_s("%d", &booknum);
			fprintf(fp, "%d\n",booknum);
			getchar();
			res = SearchBTree(T, booknum);
			if (res.tag)
			{
				B = res.p->recptr[res.i];
				printf("请输入您的ID号：\n");
				fprintf(fp,"请输入您的ID号：\n");
				fflush(stdin);
				scanf_s("%d", &R->number);
				fprintf(fp,"%d\n", R->number);
				printf("请输入借阅截止日期(年，月，日)：\n");
				fprintf(fp,"请输入借阅截止日期(年，月，日)：\n");
				fflush(stdin);
				scanf_s("%d,%d,%d", &R->dyear,&R->dmonth, &R->dday);
				fprintf(fp, "%d,%d,%d\n", R->dyear, R->dmonth, R->dday);
				int n = countQueue(Q);
				if (B->left <= n)//存货都被预约了
				{
					printf("现存量均已被预约，如果你已预约过请输入y，没有预约过请输入n：");
					fprintf(fp,"现存量均已被预约，如果你已预约过请输入y，没有预约过请输入n：");
					fflush(stdin);
					getchar();
					scanf("%c", &yn);
					fprintf(fp, "%c\n", yn);
					if (yn=='y')
					{
						if (R->number=DeQueue(Q,e))
						{
							if (Borrowbook(T, B, R))
							{
								printf("借书成功\n");
								fprintf(fp, "借书成功\n");
							}
							else
							{
								printf("系统出错\n");
								fprintf(fp,"系统出错\n");
							}
						}
						else
						{
							printf("您前面还有预约的人，请等候\n");
							fprintf(fp,"您前面还有预约的人，请等候\n");
						}
					}
					else
					{
						printf("您可以先去预约\n");
						fprintf(fp,"您可以先去预约\n");
					}
				}
				else//还有存货没有被预约
				{
					if (Borrowbook(T, B, R))
					{
						printf("借书成功\n");
						fprintf(fp, "借书成功\n");
					}
					else
					{
						printf("库存不足，无法借阅\n");
						fprintf(fp, "库存不足，无法借阅\n"); free(R);
					}
				}
			}
			else
			{
				printf("没有这本书，无法借阅\n"); 
				fprintf(fp, "没有这本书，无法借阅\n"); free(R);
			}
			fclose(fp);
			break;
		case 4:
			int number;
			printf("请输入归还图书书号：\n");
			fprintf(fp,"请输入归还图书书号：\n");
			fflush(stdin);
			scanf_s("%d", &booknum);
			fprintf(fp, "%d\n", booknum);
			getchar();
			res = SearchBTree(T, booknum);
			if (res.tag)
			{
				B = res.p->recptr[res.i];
				printf("请输入您的ID号：\n");
				fprintf(fp,"请输入您的ID号：\n");
				fflush(stdin);
				scanf_s("%d", &number);
				fprintf(fp, "%d\n", number);
				Returnbook(T, B, number,fp);
			}
			else {
				printf("没有这本图书，无法归还！\n");
				fprintf(fp,"没有这本图书，无法归还！\n");
			}
			fclose(fp);
			break;
		case 5:printBtree(T, 8,fp); 
			fclose(fp);
			break;
		case 6:
			printf("请输入查找书号：\n");
			fprintf(fp,"请输入查找书号：\n");
			fflush(stdin);
			scanf_s("%d", &booknum);
			fprintf(fp, "%d\n", booknum);
			getchar();
			res = SearchBTree(T, booknum);
			if (res.tag)
			{
				B = res.p->recptr[res.i];
				printbook_reader(T, B,fp);
			}
			else { printf("没有该书\n"); fprintf(fp,"没有该书\n");}
			fclose(fp);
			break;
		case 7:BTrave(T,s,fp); fclose(fp);
			break;
		case 8:
			printf("请输入要预约借阅图书书号：\n");
			fprintf(fp, "请输入借阅图书书号：\n");
			fflush(stdin);
			scanf_s("%d", &booknum);
			fprintf(fp, "%d\n", booknum);
			getchar();
			res = SearchBTree(T, booknum);
			if (res.tag)
			{
				printf("请输入您的ID号：\n");
				fprintf(fp, "请输入您的ID号：\n");
				fflush(stdin);
				scanf_s("%d", &number);
				fprintf(fp, "%d\n", number);
				if (EnQueue(Q, number)) //入队列排队预约
				{ printf("预约成功\n"); fprintf(fp, "预约成功\n"); }
				else { printf("预约失败\n"); fprintf(fp, "预约失败\n"); }	
			}
			else
			{
				printf("没有这本书，无法预约\n");
				fprintf(fp, "没有这本书，无法预约\n");
			}
			fclose(fp);
			break;
		case 9:showQueue(Q,fp); printf("\n"); break;

		default:
			break;
		}

	}


}
