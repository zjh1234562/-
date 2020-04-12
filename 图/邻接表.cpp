#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS

int LocateVex(ALGraph G, char v) {//��λ���� 
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
	printf("�ֱ����붥������ͱߵ���Ŀ��\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	printf("�ֱ������������ֵ��\n");
	for (i = 0; i<G.vexnum; i++) {
		getchar();
		scanf("%c", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;//��ʼ�� 
	}
	printf("�ֱ���������ߵ��������㣺\n");
	for (k = 0; k<G.arcnum; k++) {
		getchar();
		scanf("%c,%c", &v1, &v2);
		i = LocateVex(G, v1); j = LocateVex(G, v2);//��λ 
		p = (ArcNode*)malloc(sizeof(ArcNode));//����һ����� 
		p->adjvex = j; p->nextarc = NULL;//��ֵ 
		p->nextarc = G.vertices[i].firstarc;//���ӽ�� 
		G.vertices[i].firstarc = p;//���ӽ�� 
		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = i; q->nextarc = NULL;
		q->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = q;
	}
}
void PrintUDG(ALGraph G) {//����ڽӱ� 
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
	printf("������\n");
}

char GetVex_AL(ALGraph G, int k) {
	if (k<0||k>=G.vexnum)
	{
		printf("û���������\n");
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
		printf("û�иö���\n");
	}
	VexType w;
	printf("����Ҫ�����ֵ:");
	getchar();
	scanf("%c", &w);
	G.vertices[k].data = w;
	printf("���滻\n");
}

int FirstAdVex_AL(ALGraph G,int k) {//����k����ĵ�һ���ڽӵ�
	if (k < 0 || k >= G.vexnum)  return -2;//��������
	ArcNode *p;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p = G.vertices[k].firstarc;
	if (p!=NULL)  return p->adjvex;
	else return -1;//û�е�һ���ڽӵ�
}

int NextAdjVex_AL(ALGraph G,int k ,int m) {//����k�����m�ڽӵ����һ���ڽӵ�
	if (k < 0 || k >= G.vexnum || m < 0 || m >= G.vexnum)  return -2;//��������
	ArcNode *p;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p = G.vertices[k].firstarc;
	if (p == NULL)  return -1;//û���ڽӵ�
	if (p->adjvex!=m) p = p->nextarc;//��p��λ��m
	p = p->nextarc;
	if (p != NULL)  return p->adjvex;
	else return -1;//mû����һ���ڽӵ�
}

int AddArc_AL(ALGraph &G,int k,int m) {
	ArcNode *p;
	if (k < 0 || k >= G.vexnum || m < 0 || m >= G.vexnum)  return ERROR;//��������
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

void RemoveArc_AL(ALGraph &G, int k, int m) {//ɾ��k��m������
	ArcNode *p, *q;
	if (k < 0 || k >= G.vexnum || m < 0 || m >= G.vexnum)  printf("��������\n");//��������
	else
	{
		p = G.vertices[k].firstarc;
		q = NULL;
		while (p&&p->adjvex!=m)
		{
			q = p;
			p = p->nextarc;
		}
		if (p == NULL)  printf("û�иñ�\n");
		if (q) q->nextarc = p->nextarc;
		else G.vertices[k].firstarc = p->nextarc;
		free(p);
		G.arcnum--;
	}
}


void DFS_AL(ALGraph &G, int k) {
	int i;
	if (k < 0 || k >= G.vexnum)  printf("û�иýڵ�\n");
	G.tags[k] = VISITED;
	printf("%c ", G.vertices[k].data);
	for (i = FirstAdVex_AL(G, k); i >= 0; i = NextAdjVex_AL(G, k, i)) {
		if (UNVISITED == G.tags[i])
			DFS_AL(G, i);
	}
}

void DFSTraverse_AL(ALGraph &G) {//��ȱ���
	int i;
	for (i = 0; i < G.vexnum; i++) G.tags[i] = UNVISITED;
	for (i = 0; i < G.vexnum; i++) {
		if (UNVISITED == G.tags[i])
			DFS_AL(G, i);
	}
	printf("\n");
}

int InitQueue_AL(LinkQueue &Q) {//��ʼ������
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		exit(0);
	Q.front->next = NULL;
	return 1;
}
int QueueEmpty_AL(LinkQueue Q) {//�ж϶����Ƿ�Ϊ��
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}
int EnQueue_AL(LinkQueue &Q, int e) {//����
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(0);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}
int DeQueue_AL(LinkQueue &Q, int &e) {//����
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


void BfsTraverse_AL(ALGraph G) {//������ȱ���
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
		printf("�������������ʵ�ֶ�Ӧ�Ĺ���(�ڽӱ�)��\n");
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
		case 1:Destroy_AL(G); break;
		case 2:int j2;
			VexType v2;
			printf("������Ҫ���ҵĶ��㣺");
			getchar();
			scanf("%c", &v2);
			j2 = LocateVex(G, v2);
			if (j2 == -1) printf("û�иö���");
			else printf("�������ڵ�λ��Ϊ:%d\n", j2);
			break;
		case 3:VexType w3;
			int k3;
			printf("�������k�����㣺");
			getchar();
			scanf("%d", &k3);
			w3 = GetVex_AL(G, k3);
			if (w3==' ') printf("û�иö���\n");
			else printf("��k������Ϊ��%c\n", w3);
			break;
		case 4:int k4;
			printf("������Ҫ���¸�ֵ�ĵ�k�����㣺");
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
			printf("������Ҫ��Ҫ���ҵ�һ���ڽӵ�ĵ�k�����㣺");
			getchar();
			scanf("%d", &i5);
			j5 = FirstAdVex_AL(G, i5);
			if (j5 == -1)
				printf("û���ڽӵ�\n");
			else  if (j5 == -2) printf("��������\n");
			else printf("��k������ĵ�һ���ڽӵ��λ��Ϊ��%d\n", j5);
			break;
		case 6:int i6, k6, m6;
			printf("������k,m��ֵ��");
			getchar();
			scanf("%d,%d", &k6, &m6);
			i6 = NextAdjVex_AL(G, k6, m6);
			if (i6 == -2 || i6 == -1)   printf("����ʧ��\n");
			else printf("�����k����ĵ�ǰ�ڽӶ���m���㣬��һ���ڽӶ����λ��Ϊ��%d\n", i6);
			break;
		case 7:int i7;
			int k7, m7;
			printf("������Ҫ���ӱߵ���������k,m��λ��:");
			getchar();
			scanf("%d,%d", &k7, &m7);
			i7 = AddArc_AL(G, k7, m7);
			if (i7 == OK) printf("��ӳɹ�\n");
			else printf("���ʧ��\n");
			PrintUDG(G);
			break;
		case 8: 
			int  k8, m8;
			printf("������Ҫɾ���ߵ���������k,m:");
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