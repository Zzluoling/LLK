#pragma once
#include "global.h"
#include"CGraph.h"
class CGameLogic
{
protected:
	int m_anPath[MAX_VERTEX_NUM];				//������ͨ·���Ķ�������
	int m_nVexNum;								//��ͨ·��������
	int m_nCorner;								//��ͨ·������յ���

	void DeleteVertex();                        //ȡ��һ������

public:
	CGameLogic();

	void InitMap(CGraph &graph);
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2);     //�ж�v1v2�Ƿ���ͨ
	void Clear(CGraph &g, Vertex v1, Vertex v2);
	bool isBlank(CGraph & g);                             //�ж�ͼ�ж����Ƿ�Ϊ��
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);        //�õ�·��axPath����ͨ���������ظ����ú���������ֵΪ������
	void UpdateArc(CGraph & g, int nRow, int nCol);       //�ж�nRow�У�nCol�еĶ��������������ҵĶ����Ƿ��бߣ�����бߣ�����ͼ�ṹ
	bool SearchPathDFS(CGraph & graph, int v0, int v1);   //��������������ж϶���V0��V1��ͼ���Ƿ���ͨ
	void PushVertex(int nV);					          //���һ��·�����㵽m_anPath�����ж�ѹ����Ƿ��γ�һ���յ㣬����ǹյ㣬��յ�������һ
	void PopVertex();							          //����һ������
	bool isExsit(int nVi);						          //�ж�����ΪnVi�Ķ����Ƿ񱣴浽��ͨ����m_anPath�� 
	bool IsCorner();							          //�ж�����·������m_anPath�У��������������Ƿ񹹳�һ���յ�
	bool SearchValidPath(CGraph &g);                      //��ʾ����·��
	void ResetGraph(CGraph &g);                           //���ŵ�ͼ
};

