#include "pch.h"
#include "CGameLogic.h"
#include "CGameDlg.h"
#include "global.h"
#include"CGraph.h"

CGameLogic::CGameLogic()
{
	m_nVexNum = 0;
	m_nCorner = 0;
}

void CGameLogic::InitMap(CGraph &graph)
{
	//������ɵ�ͼ
	int anTemp[MAX_VERTEX_NUM];
	//���ٻ�ɫ
	for (int i = 0; i < MAX_PIC_NUM; i++)
	{
		for (int j = 0; j < REPEAT_NUM; j++)
		{
			anTemp[i*REPEAT_NUM + j] = i;
		}
	}
	//��������
	srand((int)time(NULL));

	//������⽻����������
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		//����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//����������ֵ
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;
	}
	//��ʼ������
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		graph.AddVertex(anTemp[i]);
	}

	//���»���Ϣ
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			UpdateArc(graph, i, j);
		}
	}
}

bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2)
{
	
	//��ȡ����������
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;
	//ѹ���һ����
	PushVertex(nV1Index);
	//��Ѱ����֮�����ͨ·��
	if (SearchPathDFS(graph, nV1Index, nV2Index) == true)
	{
		return true;
	}

	PopVertex();

	/*�޸��ж���Ȧ������*/

	if (v1.row == v2.row) {
		if (v1.row == 0 || v1.row == MAX_ROW - 1) {
			return true;
		}
	}

	if (v1.col == v2.col) {
		if (v1.col == 0 || v1.col == MAX_COL - 1) {
			return true;
		}
	}
	return false;

}

void CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2)
{
	//��ö���������
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;

	//���¶���
	g.UpdateVertex(nV1Index, BLANK);
	g.UpdateVertex(nV2Index, BLANK);

	//���±���Ϣ
	UpdateArc(g, v1.row, v1.col);
	UpdateArc(g, v2.row, v2.col);
}

bool CGameLogic::isBlank(CGraph & g)
{
	int vn = g.GetVexNum();
	for (int i = 0; i < vn; i++) {
		if (g.GetVertex(i) != BLANK)
			return false;
	}
	return true;
}

void CGameLogic::DeleteVertex()//ȡ��һ������
{
	m_nVexNum--;
}

int CGameLogic::GetVexPath(Vertex avPath[MAX_VERTEX_NUM])
{
	Vertex point;
	for (int i = 0; i < m_nVexNum; i++)
		for (point.col = 0; point.col < MAX_COL; point.col++)
		{
			for (point.row = 0; point.row < MAX_ROW; point.row++)
			{
				if (point.row * MAX_COL + point.col == m_anPath[i])
				{
					avPath[i] = point;
				}
			}
		}
	return m_nVexNum;
}

//���±�
void CGameLogic::UpdateArc(CGraph & g, int nRow, int nCol)
{
	int nV1Index = nRow * MAX_COL + nCol;
	if (nCol > 0) {
		int nV2Index = nV1Index - 1;
		if (g.GetVertex(nV2Index) == g.GetVertex(nV1Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK) {
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nCol < MAX_COL - 1) {
		int nV2Index = nV1Index + 1;
		if (g.GetVertex(nV2Index) == g.GetVertex(nV1Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK) {
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow > 0) {
		int nV2Index = nV1Index - MAX_COL;
		if (g.GetVertex(nV2Index) == g.GetVertex(nV1Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK) {
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < MAX_ROW - 1) {
		int nV2Index = nV1Index + MAX_COL;
		if (g.GetVertex(nV2Index) == g.GetVertex(nV1Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK) {
			g.AddArc(nV1Index, nV2Index);
		}
	}
}

bool CGameLogic::SearchPathDFS(CGraph & graph, int v0, int v1)
{
	//�õ�������
	int nVexnum = graph.GetVexNum();
	//����ͼ��nV0�У���0��nVexnum��ֵΪtrue�ĵ�
	for (int vi = 0; vi < nVexnum; vi++) {
		if (graph.GetArc(v0, vi) && !isExsit(vi)) {
			PushVertex(vi);
			if (m_nCorner > 2) {
				PopVertex();
				continue;
			}

			//���м䶥�㲻��v1ʱ������������һ����������ͨ�ĵ�
			if (vi != v1) {
				//���м䶥�㲻Ϊ��ʱ����ʾ·������ͨ
				if (graph.GetVertex(vi) != BLANK) {
					PopVertex();
					continue;
				}
				//���vi��һ���������ĵ㣬�ж�(vi v1)
				if (SearchPathDFS(graph, vi, v1)) {
					return true;
					//��ʾ�Ѿ��ҵ���һ����ͨ·��������true
				}
			}
			else {//���vi=v1��ʾ�Ѿ��ҵ���һ����ͨ·��������true
				return true;
			}
			PopVertex();
		}
	}
	return false;
}

void CGameLogic::PushVertex(int nV)
{
	//������ѹջ
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;

	//�ж��Ƿ��γ��µĹյ�
	if (IsCorner())
	{
		m_nCorner++;
	}
}

void CGameLogic::PopVertex()
{
	if (IsCorner()) {
		m_nCorner--;
	}
	m_nVexNum--;
}

bool CGameLogic::isExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++) {
		if (m_anPath[i] == nVi) {
			return true;
		}
	}
	return false;
}

bool CGameLogic::IsCorner()
{
	if (m_nVexNum >= 3) {
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2]) {

			return true;
		}
	}
	return false;
}

bool CGameLogic::SearchValidPath(CGraph &g)
{

	//�õ�������
	int nVexnum = g.GetVexNum();
	for (int i = 0; i < nVexnum; i++)
	{
		//�õ���һ���ǿն���
		if (g.GetVertex(i) == BLANK)
		{
			continue;
		}
		//�����õ��ڶ���ͬɫ����
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				//�����i����͵�j����ͬɫ
				if (g.GetVertex(i) == g.GetVertex(j))
				{
					//ѹ���һ����
					PushVertex(i);
					if (SearchPathDFS(g, i, j) == true)
					{
						return true;
					}
					//ȡ��ѹ��Ķ���ʱ����PushVertex(i);��Ӧ
					PopVertex();
				}

			}
		}
	}
	return false;
}
void CGameLogic::ResetGraph(CGraph &graph)
{
	//��������������������������ֵ
	for (int i = 0; i < 200; i++)
	{
		//����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//����������ֵ
		graph.ChangeVerex(nIndex1, nIndex2);
	}

	//���»���Ϣ
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			UpdateArc(graph, i, j);
		}
	}
}