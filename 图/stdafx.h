// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <atlbase.h>
#include <atlstr.h>

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#define UNVISITED 0
#define VISITED 1
#define INFINITY MAXINT
#define VexType char
#define TRUE   1
#define FALSE  0
#define OK     1
#define ERROR  0
#define IBFEASIBLE  -1
#define OVERFLOW    -2 
#define Status int

typedef enum { DG, DN, UDG, UDN }GraphKind;
typedef struct {
	VexType vexs[10];
	int arcs[10][10];
	int n, e;
	GraphKind kind;
	int tags[10];
}MGraph;

typedef struct {
	VexType v, w;
	int info;
}ArcInfo;

typedef struct ArcNode {
	int adjvex;//�ñߵ���һ�������λ�� 
	struct ArcNode *nextarc; //ָ����һ���� 
}ArcNode;
typedef struct VNode {
	char data;//�����ֵ 
	ArcNode *firstarc;//ָ���һ�������ö���ıߵ�ָ�� 
}VNode, AdjList[20];
typedef struct {
	AdjList vertices;//�������� 
	int vexnum, arcnum;
	int tags[20];
}ALGraph;



typedef struct QNode {
	int data;
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;



