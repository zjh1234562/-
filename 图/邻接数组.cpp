// ConsoleApplication13.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int LocateVex_M(MGraph G, VexType v) {//查找顶点v在图G的位序
	int i;
	for (i = 0; i < G.n; i++)
	{
		if (v == G.vexs[i])
		{
			return i;
		}
	}
	return -1;
}



void CreatUDG_M(MGraph &G) {//创建无向图
	int i, j;
	int k;
	char c1, c2;
	G.kind = UDG;
	printf("输入顶点数和边数:");
	scanf("%d,%d",&(G.n),&(G.e));
	for ( i = 0; i < G.n; i++)
	{
		G.tags[i] = UNVISITED;
		getchar();
		scanf("%c", &(G.vexs[i]));
	}
	for ( i = 0; i < G.n; i++)
	{
		for ( j = 0; j < G.n; j++)
		{
			G.arcs[i][j] = 0;
		}
	}
	printf("输入每条边对应的两个顶点\n");
	for (k = 0; k < (G.e); k++)
	{
		getchar();
		scanf("%c,%c", &c1, &c2);
		i = LocateVex_M(G, c1);
		j = LocateVex_M(G, c2);
		if (i >= 0 && j >= 0)
			G.arcs[i][j] = G.arcs[j][i] = 1;
	}
	
}

void DestroyGraph(MGraph &G) {//销毁图
	for (int i = 0; i < G.n; i++)
	{
		G.vexs[i] = NULL;
		G.tags[i] = NULL;
		for (int j = 0; j < G.n; j++)
		{
			G.arcs[i][j] = NULL;
		}
	}
	G.e = 0;
	G.n = 0;
	printf("已销毁图");
}

char GetVex_M(MGraph G, int k) {
	if (k<0)
	{
		printf("没有这个顶点");
		return ' ';
	}
	else
	{
		return G.vexs[k];
	}  
}

void PutVex_M(MGraph &G, int k) {
	if (k<0)
	{
		printf("没有该顶点");
	}
	VexType w;
	printf("输入要赋予的值:");
	getchar();
	scanf("%c", &w);
	G.vexs[k] = w;
	printf("已替换\n");
}

int FirstAdjVex_M(MGraph G, int k) {//返回k顶点的第一个邻接点
	if (k<0||k>G.n)
	{
		printf("顶点不存在");
		return -1;
	}
	for (int i = 0; i < G.n; i++)
		{
			if (G.arcs[k][i] != 0)
				return i;
		}
	return -1;//k没有邻接点
}

int NextAdjVex(MGraph G, int k, int m)
/* 在图G中，相对于k顶点的当前邻接顶点m顶点，求下一个邻接顶点 */
{
	if (k == 0 && m == 0)  return 0;
	int i;
	for (i = m + 1; i<G.n; i++) {
		if (G.arcs[k][i] == 1) return i;
	}
	if (i == (G.n - 1))  return -1;
	return -1;
}

Status SetArc(MGraph &G, VexType v, VexType w){
/* 在图G中置顶点v到顶点w的弧或边 */
	int i, j;
	i = LocateVex_M(G, v);
	j = LocateVex_M(G, w);
	if (i<0 || j<0 || i == j)  return ERROR;
	if (G.arcs[i][j] == 1)  return TRUE;
	else
	{
		G.arcs[i][j] = G.arcs[j][i]=1;
		G.e += 1; 
		return TRUE;
	}
	return ERROR;
}

Status RemoveArc(MGraph &G, VexType v, VexType w) {
	/* 在图G中删除顶点v到顶点w的弧或边 */
	int i, j;
	i = LocateVex_M(G, v);
	j = LocateVex_M(G, w);
	if (i<0 || j<0 || i == j)  return ERROR;
	if (G.arcs[i][j] == 0)  return TRUE;
	else
	{
		G.arcs[i][j] = G.arcs[j][i] = 0;
		G.e -= 1;
		return TRUE;
	}
	return ERROR;
}


void juzheng(MGraph G) {//打印邻接矩阵
	printf("邻接矩阵为：\n");
	for (int i = 0; i < G.n; i++)
	{
		for (int j = 0; j < G.n; j++)
		{
			printf("  %d", G.arcs[i][j]);
		}
		printf("\n");
	}
}


void DFS_M(MGraph &G,int k) {
	int i;
	if (k < 0 || k >= G.n)  printf("没有该节点\n");
	G.tags[k] = VISITED;
	printf("%c ", G.vexs[k]);
	for ( i = FirstAdjVex_M(G,k);i>=0;i=NextAdjVex(G,k,i)){
		if (UNVISITED == G.tags[i])  
			DFS_M(G, i);
	}
}

void DFSTraverse_M(MGraph &G) {//深度遍历
	int i;
	for (i = 0; i < G.n; i++) G.tags[i] = UNVISITED;
	for (i = 0; i < G.n; i++) {
		if (UNVISITED == G.tags[i])
			DFS_M(G,i);
	}
	printf("\n");
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
	return 1;
}
void BfsTraverse_M(MGraph G) {//广度优先遍历
	int v, u, w;
	LinkQueue Q;
	for (v = 0; v<G.n; v++)
		G.tags[v]=UNVISITED;
	InitQueue(Q);
	for (v = 0; v<G.n; v++)
		if (!G.tags[v]) {
			G.tags[v] = VISITED;
			printf("%c", G.vexs[v]);
			EnQueue(Q, v);
			while (!QueueEmpty(Q)) {
				DeQueue(Q, u);
				for (w = 0; w<G.n; w++)
					if (!G.tags[w] && G.arcs[u][w]!= 0) {
						G.tags[w] = VISITED;
						printf("%c", G.vexs[w]);
						EnQueue(Q, w);
					}
			}
		}
}




/*void main()
{
	MGraph G;
	char m;
	CreatUDG_M(G);
	juzheng(G);
	system("pause");
	m = 'y';
	while (m == 'y')
	{
		printf("请输入以下序号实现对应的功能：\n");
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
		case 1:DestroyGraph(G); break;
		case 2:int j2;
			VexType v2;
			printf("请输入要查找的顶点：");
			getchar();
			scanf("%c", &v2);
			j2 = LocateVex_M(G, v2);
			if (j2 == -1) printf("没有该顶点");
			else printf("顶点所在的位序为:%d\n", j2);
			break;
		case 3:VexType w3;
			int k3;
			printf("请输入第k个顶点：");
			getchar();
			scanf("%d", &k3);
			w3 = GetVex_M(G, k3);
			printf("第k个顶点为：%c\n", w3);
			break;
		case 4:int k4;
			printf("请输入要重新赋值的第k个顶点：");
			getchar();
			scanf("%d", &k4);
			PutVex_M(G, k4);
			for (int i = 0; i < G.n; i++)
			{
				printf("%c ", G.vexs[i]);
			}
			juzheng(G);
			printf("\n");
			break;
		case 5:int i5, j5;
			printf("请输入要所要查找第一个邻接点的第k个顶点：");
			getchar();
			scanf("%d", &i5);
			j5 = FirstAdjVex_M(G, i5);
			if (j5 == -1)
				printf("没有邻接点\n");
			else  printf("第k个顶点的第一个邻接点的位序为：%d\n", j5);
			break;
		case 6:int i6, k6, m6;
			printf("请输入k,m的值：");
			getchar();
			scanf("%d,%d", &k6, &m6);
			i6 = NextAdjVex(G, k6, m6);
			if (i6 == 0 || i6 == -1)   printf("查找失败\n");
			else printf("相对于k顶点的当前邻接顶点m顶点，下一个邻接顶点的位序为：%d\n", i6);
			break;
		case 7:int i7;
			VexType k7, m7;
			printf("请输入要增加边的两个顶点k,m:");
			getchar();
			scanf("%c,%c", &k7, &m7);
			i7 = SetArc(G, k7, m7);
			if (i7 == TRUE) printf("添加成功\n");
			else printf("添加失败\n");
			juzheng(G);
			break;
		case 8:int i8;
			VexType k8, m8;
			printf("请输入要删除边的两个顶点k,m:");
			getchar();
			scanf("%c,%c", &k8, &m8);
			i8 = RemoveArc(G, k8, m8);
			if (i8 == TRUE) printf("删除成功\n");
			else printf("删除失败\n");
			juzheng(G);
			break;
		case 9:DFSTraverse_M(G); break;
		case 10:BfsTraverse_M(G); printf("\n"); break;
		default:
			break;

		}
	}
}*/



