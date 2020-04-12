// ConsoleApplication13.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int LocateVex_M(MGraph G, VexType v) {//���Ҷ���v��ͼG��λ��
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



void CreatUDG_M(MGraph &G) {//��������ͼ
	int i, j;
	int k;
	char c1, c2;
	G.kind = UDG;
	printf("���붥�����ͱ���:");
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
	printf("����ÿ���߶�Ӧ����������\n");
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

void DestroyGraph(MGraph &G) {//����ͼ
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
	printf("������ͼ");
}

char GetVex_M(MGraph G, int k) {
	if (k<0)
	{
		printf("û���������");
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
		printf("û�иö���");
	}
	VexType w;
	printf("����Ҫ�����ֵ:");
	getchar();
	scanf("%c", &w);
	G.vexs[k] = w;
	printf("���滻\n");
}

int FirstAdjVex_M(MGraph G, int k) {//����k����ĵ�һ���ڽӵ�
	if (k<0||k>G.n)
	{
		printf("���㲻����");
		return -1;
	}
	for (int i = 0; i < G.n; i++)
		{
			if (G.arcs[k][i] != 0)
				return i;
		}
	return -1;//kû���ڽӵ�
}

int NextAdjVex(MGraph G, int k, int m)
/* ��ͼG�У������k����ĵ�ǰ�ڽӶ���m���㣬����һ���ڽӶ��� */
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
/* ��ͼG���ö���v������w�Ļ���� */
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
	/* ��ͼG��ɾ������v������w�Ļ���� */
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


void juzheng(MGraph G) {//��ӡ�ڽӾ���
	printf("�ڽӾ���Ϊ��\n");
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
	if (k < 0 || k >= G.n)  printf("û�иýڵ�\n");
	G.tags[k] = VISITED;
	printf("%c ", G.vexs[k]);
	for ( i = FirstAdjVex_M(G,k);i>=0;i=NextAdjVex(G,k,i)){
		if (UNVISITED == G.tags[i])  
			DFS_M(G, i);
	}
}

void DFSTraverse_M(MGraph &G) {//��ȱ���
	int i;
	for (i = 0; i < G.n; i++) G.tags[i] = UNVISITED;
	for (i = 0; i < G.n; i++) {
		if (UNVISITED == G.tags[i])
			DFS_M(G,i);
	}
	printf("\n");
}



int InitQueue(LinkQueue &Q) {//��ʼ������
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		exit(0);
	Q.front->next = NULL;
	return 1;
}
int QueueEmpty(LinkQueue Q) {//�ж϶����Ƿ�Ϊ��
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}
int EnQueue(LinkQueue &Q, int e) {//����
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(0);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}
int DeQueue(LinkQueue &Q, int &e) {//����
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
void BfsTraverse_M(MGraph G) {//������ȱ���
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
		printf("�������������ʵ�ֶ�Ӧ�Ĺ��ܣ�\n");
		printf("1:����ͼ\n");
		printf("2:���Ҷ���v��λ��\n");
		printf("3:ȡͼ��k�㸳ֵ��w\n");
		printf("4:��ͼ��k�㸳ֵw\n");
		printf("5:��ͼk����ĵ�һ���ڽӵ�λ��\n");
		printf("6:��ͼ��k���������m�������һ���ڽӵ��λ��\n");
		printf("7:��ͼG���ö���v������w�Ļ����\n");
		printf("8:��ͼG��ɾ������v������w�Ļ����\n");
		printf("9:������ȱ���ͼ\n");
		printf("10:������ȱ���ͼ\n");

		int i;
		scanf("%d", &i);
		switch (i)
		{
		case 0:m = 'n'; break;
		case 1:DestroyGraph(G); break;
		case 2:int j2;
			VexType v2;
			printf("������Ҫ���ҵĶ��㣺");
			getchar();
			scanf("%c", &v2);
			j2 = LocateVex_M(G, v2);
			if (j2 == -1) printf("û�иö���");
			else printf("�������ڵ�λ��Ϊ:%d\n", j2);
			break;
		case 3:VexType w3;
			int k3;
			printf("�������k�����㣺");
			getchar();
			scanf("%d", &k3);
			w3 = GetVex_M(G, k3);
			printf("��k������Ϊ��%c\n", w3);
			break;
		case 4:int k4;
			printf("������Ҫ���¸�ֵ�ĵ�k�����㣺");
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
			printf("������Ҫ��Ҫ���ҵ�һ���ڽӵ�ĵ�k�����㣺");
			getchar();
			scanf("%d", &i5);
			j5 = FirstAdjVex_M(G, i5);
			if (j5 == -1)
				printf("û���ڽӵ�\n");
			else  printf("��k������ĵ�һ���ڽӵ��λ��Ϊ��%d\n", j5);
			break;
		case 6:int i6, k6, m6;
			printf("������k,m��ֵ��");
			getchar();
			scanf("%d,%d", &k6, &m6);
			i6 = NextAdjVex(G, k6, m6);
			if (i6 == 0 || i6 == -1)   printf("����ʧ��\n");
			else printf("�����k����ĵ�ǰ�ڽӶ���m���㣬��һ���ڽӶ����λ��Ϊ��%d\n", i6);
			break;
		case 7:int i7;
			VexType k7, m7;
			printf("������Ҫ���ӱߵ���������k,m:");
			getchar();
			scanf("%c,%c", &k7, &m7);
			i7 = SetArc(G, k7, m7);
			if (i7 == TRUE) printf("��ӳɹ�\n");
			else printf("���ʧ��\n");
			juzheng(G);
			break;
		case 8:int i8;
			VexType k8, m8;
			printf("������Ҫɾ���ߵ���������k,m:");
			getchar();
			scanf("%c,%c", &k8, &m8);
			i8 = RemoveArc(G, k8, m8);
			if (i8 == TRUE) printf("ɾ���ɹ�\n");
			else printf("ɾ��ʧ��\n");
			juzheng(G);
			break;
		case 9:DFSTraverse_M(G); break;
		case 10:BfsTraverse_M(G); printf("\n"); break;
		default:
			break;

		}
	}
}*/



