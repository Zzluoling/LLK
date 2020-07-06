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
	//�ж��Ƿ�Ϊͬһλ��
	if (m_ptSelFirst.col == m_ptSelSec.col&&m_ptSelFirst.row == m_ptSelSec.row) {
		return false;
	}
	//�ж�ͼƬ�Ƿ���ͬ�������ͬ������ͨ
	int	nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col);
	int	nInfo2 = m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
	{
		return false;
	}

	//�ж��Ƿ������ͨ
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//����
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);


		//����·������
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
	//�����߼�������
	CGameLogic logic;

	//�ж���Ϸʱ��
	if (nTime <= 0)
	{
		//���ͼ
		m_graph.ClearGraph();
		return GAME_LOSE;
	}

	//�ж��Ƿ�ͼ�����е�Ϊ��
	if (logic.isBlank(m_graph) == true)
	{
		//���ͼ
		m_graph.ClearGraph();
		return GAME_SUCESS;
	}
	return GAME_PLAY;
}

bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum)
{
	CGameLogic logic;
	//�ж��Ƿ�Ϊ��
	if(logic.isBlank(m_graph)==true)
	{
		return false;
	}
	//����һ����Ч����ʾ·��
	if (logic.SearchValidPath(m_graph))
	{
		nVexnum = logic.GetVexPath(avPath);
		return true;
		//����·������
	}
	return false;
}

void CGameControl::ResetGraph()
{
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}