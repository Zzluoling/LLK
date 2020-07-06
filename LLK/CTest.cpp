#include "pch.h"
#include "CTest.h"
#include <string.h>
#include <iostream>

CTest::CTest()
{
}


CTest::~CTest()
{
}

void CTest::Output(CGraph & graph)
{
	//�½���־�ļ�
	CStdioFile file(_T("log.txt"), CFile::modeCreate | CFile::modeReadWrite);
	//�½�������Ϣ
	int nVexnum = graph.GetVexNum();
	//�����ϵ����
	CString strTmp;
	//���������Ϣ
	for (int i = 0; i < nVexnum; i++)
	{
		strTmp.Format(_T("%d\t"), graph.GetVertex(i));
		file.WriteString(strTmp);
	}
	//�ر��ļ�
	file.Close();
}