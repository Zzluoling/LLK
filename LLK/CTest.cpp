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
	//新建日志文件
	CStdioFile file(_T("log.txt"), CFile::modeCreate | CFile::modeReadWrite);
	//新建顶点信息
	int nVexnum = graph.GetVexNum();
	//输出关系矩阵
	CString strTmp;
	//输出顶点信息
	for (int i = 0; i < nVexnum; i++)
	{
		strTmp.Format(_T("%d\t"), graph.GetVertex(i));
		file.WriteString(strTmp);
	}
	//关闭文件
	file.Close();
}