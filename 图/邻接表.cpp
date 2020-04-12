#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS

int LocateVex(ALGraph G, char v) {//定位函数 
	int i;
	for (i = 0; i<G.vexnum; i++) {
		if (v == G.vertices[i].data) return i;
	}
	return -1;
}
void CreateUDG(ALGraph &G) {
	ArcNode *p, *q;
	int i, j, k;
	char v1, v2;
	printf("分别输入顶点个数和边的数目：\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	printf("分别输入各个顶点值：\n");
	for (i = 0; i<G.vexnum; i++) {
		getchar();
		scanf("%c", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;//初始化 
	}
	printf("分别输入各条边的两个顶点：\n");
	for (k = 0; k<G.arcnum; k++) {
		getchar();
		scanf("%c,%c", &v1, &v2);
		i = LocateVex(G, v1); j = LocateVex(G, v2);//定位 
		p = (ArcNode*)malloc(sizeof(ArcNode));//申请一个结点 
		p->adjvex = j; p->nextarc = NULL;//赋值 
		p->nextarc = G.vertices[i].firstarc;//连接结点 
		G.vertices[i].firstarc = p;//连接结点 
		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = i; q->nextarc = NULL;
		q->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = q;
	}
}
void PrintUDG(ALGraph G) {//输出邻接表 
	int i, j;
	for (i = 0; i<G.vexnum; i++) {
		printf("%c:", G.vertices[i].data);
		ArcNode *p;
		p = G.vertices[i].firstarc;
		while (p != NULL) {
			printf("->%d", p->adjvex);
			p = p->nextarc;
		}
		printf("\n");
	}
}

void Destroy_AL(ALGraph &G) {
	ArcNode *p, *q;
	int i;
	for ( i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
		q = p;
		while (p)
		{
			p = p->nextarc;
			free(q);
			q = p;
		}
	}
	for (int j = 0; j < G.vexnum; j++)
	{
		G.vertices[i].data = ' ';
		G.vertices[i].firstarc= NULL;
	}
	G.arcnum = 0; G.vexnum = 0;
	printf("已销毁\n");
}

char GetVex_AL(ALGraph G, int k) {
	if (k<0||k>=G.vexnum)
	{
		printf("没有这个顶点\n");
		return ' ';
	}
	else
	{
		return G.vertices[k].data;
	}
}

void PutVex_AL(ALGraph &G, int k) {
	if (k<0||k>=G.vexnum)
	{
		printf("没有该顶点\n");
	}
	VexType w;
	printf("输入要赋予的值:");
	getchar();
	scanf("%c", &w);
	G.vertices[k].data = w;
	printf("已替换\n");
}

int FirstAdVex_AL(ALGraph G,int k) {//查找k顶点的第一个邻接点
	if (k < 0 || k >= G.vexnum)  return -2;//参数错误
	ArcNode *p;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p = G.vertices[k].firstarc;
	if (p!=NULL)  return p->adjvex;
	else return -1;//没有第一个邻接点
}

int NextAdjVex_AL(ALGraph G,int k ,int m) {//查找k顶点的m邻接点的下一个邻接点
	if (k < 0 || k >= G.vexnum || m < 0 || m >= G.vexnum)  return -2;//参数错误
	ArcNode *p;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p = G.vertices[k].firstarc;
	if (p == NULL)  return -1;//没有邻接点
	if (p->adjvex!=m) p = p->nextarc;//将p定位到m
	p = p->nextarc;
	if (p != NULL)  return p->adjvex;
	else return -1;//m没有下一个邻接点
}

int AddArc_AL(ALGraph &G,int k,int m) {
	ArcNode *p;
	if (k < 0 || k >= G.vexnum || m < 0 || m >= G.vexnum)  return ERROR;//参数错误
	p = G.vertices[k].firstarc;
	while (p!=NULL)
	{
		if (m == p->adjvex)   return ERROR;
		p = p->nextarc;
	}
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = m;
	p->nextarc= G.vertices[k].firstarc;
	G.vertices[k].firstarc = p;

	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = k;
	p->nextarc = G.vertices[m].firstarc;
	G.vertices[m].firstarc = p;

	G.arcnum++;
	return OK;
}

void RemoveArc_AL(ALGraph &G, int k, int m) {//删除k，m的连接
	ArcNode *p, *q;
	if (k < 0 || k >= G.vexnum || m < 0 || m >= G.vexnum)  printf("参数错误\n");//参数错误
	else
	{
		p = G.vertices[k].firstarc;
		q = NULL;
		while (p&&p->adjvex!=m)
		{
			q = p;
			p = p->nextarc;
		}
		if (p == NULL)  printf("没有该边\n");
		if (q) q->nextarc = p->nextarc;
		else G.vertices[k].firstarc = p->nextarc;
		free(p);
		G.arcnum--;
	}
}


void DFS_AL(ALGraph &G, int k) {
	int i;
	if (k < 0 || k >= G.vexnum)  printf("没有该节点\n");
	G.tags[k] = VISITED;
	printf("%c ", G.vertices[k].data);
	for (i = FirstAdVex_AL(G, k); i >= 0; i = NextAdjVex_AL(G, k, i)) {
		if (UNVISITED == G.tags[i])
			DFS_AL(G, i);
	}
}

void DFSTraverse_AL(ALGraph &G) {//深度遍历
	int i;
	for (i = 0; i < G.vexnum; i++) G.tags[i] = UNVISITED;
	for (i = 0; i < G.vexnum; i++) {
		if (UNVISITED == G.tags[i])
			DFS_AL(G, i);
	}
	printf("\n");
}

int InitQueue_AL(LinkQueue &Q) {//初始化队列
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		exit(0);
	Q.front->next = NULL;
	return 1;
}
int QueueEmpty_AL(LinkQueue Q) {//判断队列是否为空
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}
int EnQueue_AL(LinkQueue &Q, int e) {//进队
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(0);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}
int DeQueue_AL(LinkQueue &Q, int &e) {//出队
	QueuePtr p;
	if (Q.front == Q.rear)
		return 0;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return 1;
}


void BfsTraverse_AL(ALGraph G) {//广度优先遍历
	int v, u, w;
	LinkQueue Q;
	for (v = 0; v<G.vexnum; v++)
		G.tags[v] = UNVISITED;
	InitQueue_AL(Q);
	for (v = 0; v<G.vexnum; v++)
		if (!G.tags[v]) {
			G.tags[v] = VISITED;
			printf("%c", G.vertices[v].data);
			EnQueue_AL(Q, v);
			while (!QueueEmpty_AL(Q)) {
				DeQueue_AL(Q, u);
				for (w = 0; w<G.vexnum; w++)
					if (!G.tags[w] ) {
						G.tags[w] = VISITED;
						printf("%c", G.vertices[w].data);
						EnQueue_AL(Q, w);
					}
			}
		}
}


void main() {
	ALGraph G;
	CreateUDG(G);
	PrintUDG(G);
	char m = 'y';
	while (m == 'y')
	{
		printf("请输入以下序号实现对应的功能(邻接表)：\n");
		printf("1:销毁图\n");
		printf("2:查找顶点v的位序\n");
		printf("3:取图的k点赋值到w\n");
		printf("4:对图的k点赋值w\n");
		printf("5:求图k顶点的第一个邻接点位序\n");
		printf("6:求图中k顶点相对于m顶点的下一个邻接点的位序\n");
		printf("7:在图G中置顶点v到顶点w的弧或边\n");
		printf("8:在图G中删除顶点v到顶点w的弧或边\n");
		printf("9:深度优先遍历图\n");
		printf("10:广度优先遍历图\n");

		int i;
		scanf("%d", &i);
		switch (i)
		{
		case 0:m = 'n'; break;
		case 1:Destroy_AL(G); break;
		case 2:int j2;
			VexType v2;
			printf("请输入要查找的顶点：");
			getchar();
			scanf("%c", &v2);
			j2 = LocateVex(G, v2);
			if (j2 == -1) printf("没有该顶点");
			else printf("顶点所在的位序为:%d\n", j2);
			break;
		case 3:VexType w3;
			int k3;
			printf("请输入第k个顶点：");
			getchar();
			scanf("%d", &k3);
			w3 = GetVex_AL(G, k3);
			if (w3==' ') printf("没有该顶点\n");
			else printf("第k个顶点为：%c\n", w3);
			break;
		case 4:int k4;
			printf("请输入要重新赋值的第k个顶点：");
			getchar();
			scanf("%d", &k4);
			PutVex_AL(G, k4);
			for (int i = 0; i < G.vexnum; i++)
			{
				printf("%c ", G.vertices[i].data);
			}
			printf("\n");
			PrintUDG(G);
			printf("\n");
			break;
		case 5:int i5, j5;
			printf("请输入要所要查找第一个邻接点的第k个顶点：");
			getchar();
			scanf("%d", &i5);
			j5 = FirstAdVex_AL(G, i5);
			if (j5 == -1)
				printf("没有邻接点\n");
			else  if (j5 == -2) printf("参数错误\n");
			else printf("第k个顶点的第一个邻接点的位序为：%d\n", j5);
			break;
		case 6:int i6, k6, m6;
			printf("请输入k,m的值：");
			getchar();
			scanf("%d,%d", &k6, &m6);
			i6 = NextAdjVex_AL(G, k6, m6);
			if (i6 == -2 || i6 == -1)   printf("查找失败\n");
			else printf("相对于k顶点的当前邻接顶点m顶点，下一个邻接顶点的位序为：%d\n", i6);
			break;
		case 7:int i7;
			int k7, m7;
			printf("请输入要增加边的两个顶点k,m的位序:");
			getchar();
			scanf("%d,%d", &k7, &m7);
			i7 = AddArc_AL(G, k7, m7);
			if (i7 == OK) printf("添加成功\n");
			else printf("添加失败\n");
			PrintUDG(G);
			break;
		case 8: 
			int  k8, m8;
			printf("请输入要删除边的两个顶点k,m:");
			getchar();
			scanf("%d,%d", &k8, &m8);
			RemoveArc_AL(G, k8, m8);
			PrintUDG(G);
			break;
		case 9:DFSTraverse_AL(G); break;
		case 10:BfsTraverse_AL(G); printf("\n"); break;
		default:
			break;

		}
	}

}