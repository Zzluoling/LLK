#pragma once
#include"global.h"
#include"CGraph.h"
#include "CTest.h"

class CGameControl
{
protected:
	CGraph m_graph;      //基本模式的四行四列
	Vertex m_ptSelFirst; //第一次选的点
	Vertex m_ptSelSec;   //第二次选的点
public:
	CGameControl();
	~CGameControl();
	void StartGame();
	int GetElement(int nRow, int nCol);                    //返回指定数组元素
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex asvPath[MAX_VERTEX_NUM], int &nVexnum);  //判断是否可连通，如果能连通，通过参数返回连接路径和连接
	int isWin(int nTime);                                   //判断图中顶点是否为空，如果为空，清理图结构，返回true
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);//帮助调用
	virtual void ResetGraph();
};

