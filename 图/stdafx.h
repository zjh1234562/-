// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <atlbase.h>
#include <atlstr.h>

// TODO:  在此处引用程序需要的其他头文件
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
	int adjvex;//该边的另一个顶点的位置 
	struct ArcNode *nextarc; //指向下一条边 
}ArcNode;
typedef struct VNode {
	char data;//顶点的值 
	ArcNode *firstarc;//指向第一条依附该顶点的边的指针 
}VNode, AdjList[20];
typedef struct {
	AdjList vertices;//顶点数组 
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



