#include "pch.h"
#include "CGameControl.h"
#include"CGameLogic.h"
#include"CTest.h"

CGameControl::CGameControl()
{

}

CGameControl::~CGameControl()
{
}

void CGameControl::StartGame() 
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
	CTest::Output(m_graph);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow*MAX_COL + nCol);
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link(Vertex asvPath[MAX_VERTEX_NUM],int &nVexNum)
{
	//判断是否为同一位置
	if (m_ptSelFirst.col == m_ptSelSec.col&&m_ptSelFirst.row == m_ptSelSec.row) {
		return false;
	}
	//判断图片是否相同，如果不同则不能连通
	int	nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col);
	int	nInfo2 = m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
	{
		return false;
	}

	//判断是否可以连通
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//消子
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);


		//返回路径顶点
		nVexNum = gameLogic.GetVexPath(asvPath);
		return true;
	}

	return false;
}

/*int CGameControl::isWin()
{
	CGameLogic gameLogic;
	if (gameLogic.isBlank(m_graph)) {
		m_graph.ClearGraph();
		return GAME_SUCESS;
	}
	return GAME_PLAY;
}*/

int CGameControl::isWin(int nTime)
{
	//定义逻辑处理类
	CGameLogic logic;

	//判断游戏时间
	if (nTime <= 0)
	{
		//清除图
		m_graph.ClearGraph();
		return GAME_LOSE;
	}

	//判断是否图中所有点为空
	if (logic.isBlank(m_graph) == true)
	{
		//清除图
		m_graph.ClearGraph();
		return GAME_SUCESS;
	}
	return GAME_PLAY;
}

bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum)
{
	CGameLogic logic;
	//判断是否为空
	if(logic.isBlank(m_graph)==true)
	{
		return false;
	}
	//查找一个有效的提示路径
	if (logic.SearchValidPath(m_graph))
	{
		nVexnum = logic.GetVexPath(avPath);
		return true;
		//返回路径顶点
	}
	return false;
}

void CGameControl::ResetGraph()
{
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}