#pragma once
#include"global.h"
#include"CGraph.h"
#include "CTest.h"

class CGameControl
{
protected:
	CGraph m_graph;      //����ģʽ����������
	Vertex m_ptSelFirst; //��һ��ѡ�ĵ�
	Vertex m_ptSelSec;   //�ڶ���ѡ�ĵ�
public:
	CGameControl();
	~CGameControl();
	void StartGame();
	int GetElement(int nRow, int nCol);                    //����ָ������Ԫ��
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex asvPath[MAX_VERTEX_NUM], int &nVexnum);  //�ж��Ƿ����ͨ���������ͨ��ͨ��������������·��������
	int isWin(int nTime);                                   //�ж�ͼ�ж����Ƿ�Ϊ�գ����Ϊ�գ�����ͼ�ṹ������true
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);//��������
	virtual void ResetGraph();
};

