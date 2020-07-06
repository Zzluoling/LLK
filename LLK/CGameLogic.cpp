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
	//随机生成地图
	int anTemp[MAX_VERTEX_NUM];
	//多少花色
	for (int i = 0; i < MAX_PIC_NUM; i++)
	{
		for (int j = 0; j < REPEAT_NUM; j++)
		{
			anTemp[i*REPEAT_NUM + j] = i;
		}
	}
	//设置种子
	srand((int)time(NULL));

	//随机任意交换两个数字
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;
	}
	//初始化顶点
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		graph.AddVertex(anTemp[i]);
	}

	//更新弧信息
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
	
	//获取顶点索引号
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;
	//压入第一个点
	PushVertex(nV1Index);
	//搜寻两点之间的连通路径
	if (SearchPathDFS(graph, nV1Index, nV2Index) == true)
	{
		return true;
	}

	PopVertex();

	/*修改判断外圈可连接*/

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
	//获得顶点索引号
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;

	//更新顶点
	g.UpdateVertex(nV1Index, BLANK);
	g.UpdateVertex(nV2Index, BLANK);

	//更新边信息
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

void CGameLogic::DeleteVertex()//取出一个顶点
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

//更新边
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
	//得到顶点数
	int nVexnum = graph.GetVexNum();
	//遍历图中nV0行，从0到nVexnum列值为true的点
	for (int vi = 0; vi < nVexnum; vi++) {
		if (graph.GetArc(v0, vi) && !isExsit(vi)) {
			PushVertex(vi);
			if (m_nCorner > 2) {
				PopVertex();
				continue;
			}

			//当中间顶点不是v1时，继续搜索下一个相邻且连通的点
			if (vi != v1) {
				//当中间顶点不为空时，表示路径不连通
				if (graph.GetVertex(vi) != BLANK) {
					PopVertex();
					continue;
				}
				//如果vi是一个已消除的点，判断(vi v1)
				if (SearchPathDFS(graph, vi, v1)) {
					return true;
					//表示已经找到了一条连通路径，返回true
				}
			}
			else {//如果vi=v1表示已经找到了一条连通路径，返回true
				return true;
			}
			PopVertex();
		}
	}
	return false;
}

void CGameLogic::PushVertex(int nV)
{
	//将顶点压栈
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;

	//判断是否形成新的拐点
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

	//得到顶点数
	int nVexnum = g.GetVexNum();
	for (int i = 0; i < nVexnum; i++)
	{
		//得到第一个非空顶点
		if (g.GetVertex(i) == BLANK)
		{
			continue;
		}
		//遍历得到第二个同色顶点
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				//如果第i个点和第j个点同色
				if (g.GetVertex(i) == g.GetVertex(j))
				{
					//压入第一个点
					PushVertex(i);
					if (SearchPathDFS(g, i, j) == true)
					{
						return true;
					}
					//取出压入的顶点时，与PushVertex(i);对应
					PopVertex();
				}

			}
		}
	}
	return false;
}
void CGameLogic::ResetGraph(CGraph &graph)
{
	//随机交换顶点数组中两个顶点的值
	for (int i = 0; i < 200; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		graph.ChangeVerex(nIndex1, nIndex2);
	}

	//更新弧信息
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			UpdateArc(graph, i, j);
		}
	}
}