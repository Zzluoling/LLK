#pragma once
#include "global.h"
#include"CGraph.h"
class CGameLogic
{
protected:
	int m_anPath[MAX_VERTEX_NUM];				//保存连通路径的顶点索引
	int m_nVexNum;								//连通路径顶点数
	int m_nCorner;								//连通路径数组拐点数

	void DeleteVertex();                        //取出一个顶点

public:
	CGameLogic();

	void InitMap(CGraph &graph);
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2);     //判断v1v2是否连通
	void Clear(CGraph &g, Vertex v1, Vertex v2);
	bool isBlank(CGraph & g);                             //判断图中顶点是否都为空
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);        //得到路径axPath，并通过参数返回给调用函数，返回值为顶点数
	void UpdateArc(CGraph & g, int nRow, int nCol);       //判断nRow行，nCol列的顶点与它上下左右的顶点是否有边，如果有边，更新图结构
	bool SearchPathDFS(CGraph & graph, int v0, int v1);   //深度优先搜索，判断顶点V0，V1在图中是否连通
	void PushVertex(int nV);					          //添加一个路径顶点到m_anPath，并判断压入后，是否形成一个拐点，如果是拐点，则拐点数量加一
	void PopVertex();							          //弹出一个顶点
	bool isExsit(int nVi);						          //判断索引为nVi的顶点是否保存到连通数组m_anPath中 
	bool IsCorner();							          //判断连接路径数组m_anPath中，连续三个顶点是否构成一个拐点
	bool SearchValidPath(CGraph &g);                      //提示查找路径
	void ResetGraph(CGraph &g);                           //重排地图
};

