#pragma once
#include "global.h"
#include "CGameControl.h"
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
protected:
	HICON m_hIcon;        //系统图标

	CDC m_dcMem;          //内存DC
	CDC m_dcElement;      //元素内存DC
	CDC m_dcMask;         //掩码内存DC
	CDC m_dcBG;           //背景DC
	CDC m_dcCache;		  //缓存的内存DC
	CDC m_dcPause;        //暂停图片内存DC

	//int m_anMap[4][4];  //基本模式的四行四列
	CPoint m_ptGameTop;   //起始点坐标
	CSize m_sizeElem;     //元素图片的大小
	CRect m_rtGameRect;   //游戏区域大小
	bool m_bFirstPoint;   //是否第一个点
	Vertex m_ptSelFirst;  //第一次选的点
	Vertex m_ptSelSec;    //第二次选的点
	CGameControl m_gameControl;
	CProgressCtrl m_GameProgress;
	bool m_bPlaying;    //是否在玩游戏
	bool m_bPause;	    //是否暂停 false 进行游戏中
	int timeCount;      //计时
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexNum);
	void JudgeWin(void);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

protected:	
	void InitBackground();
	void InitElement();
	void UpdataWindow();
	void UpdataMap();
public:
	afx_msg void OnPaint();
	afx_msg void OnClickedButtonBasicStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonBasicTip();
	afx_msg void OnClickedButtonBasicAgain();
	afx_msg void OnClickedButtonBasicPause();
	afx_msg void OnClickedButtonBasicHelp();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGameTime();
	afx_msg void OnEnChangeEditTime();
};
