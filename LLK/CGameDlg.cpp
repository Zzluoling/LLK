// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "global.h"
#include "CGameLogic.h"
#include"CHelpDialog.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//加载系统图标
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_ptGameTop.x = MAP_TOP;
	m_ptGameTop.y = MAP_LEFT;

	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	m_bFirstPoint = true;
	m_bPlaying = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BASIC_START, &CGameDlg::OnClickedButtonBasicStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_BASIC_TIP, &CGameDlg::OnClickedButtonBasicTip)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_AGAIN, &CGameDlg::OnClickedButtonBasicAgain)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_PAUSE, &CGameDlg::OnClickedButtonBasicPause)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_HELP, &CGameDlg::OnClickedButtonBasicHelp)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_TIME, &CGameDlg::OnEnChangeEditTime)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

void CGameDlg::UpdataMap()
{
	int nLeft = MAP_TOP;
	int nTop = MAP_LEFT;
	int nElemW = PIC_WIDTH;
	int nElemH = PIC_HEIGHT;
	
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < MAX_ROW; i++)
	{
    	for (int j = 0; j < MAX_COL; j++)
		{   //绘制单张图片
			int nInfo = m_gameControl.GetElement(i,j);
			if (nInfo == BLANK)continue;
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo * nElemH, SRCAND);
		}
	}
}

void CGameDlg::UpdataWindow()
{
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);//获得窗口大小
	this->GetWindowRect(rtClient);//获得客户区大小

	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeigh = rtWin.Height() - rtClient.Height();

	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeigh);

	//设置对话框显示在windows窗口正中央
	CenterWindow();
}

void CGameDlg::InitBackground()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);
	//加载BMP图片资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\sky_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcBG.SelectObject(hBmpBG);
	
	//初始化内存
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
	UpdateWindow();
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();

	//设置进度条隐藏和剩余时间控件
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);
}


void CGameDlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);
	//加载BMP图片资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\soccer_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcElement.SelectObject(hBmpBG);

	//加载BMP图片资源
	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\soccer_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);

	//加载掩盖图片
	//加载BMP图片资源
	HANDLE hCache = ::LoadImage(NULL, _T("theme\\picture\\lgx_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcCache.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcCache.SelectObject(hCache);
}


void CGameDlg::OnClickedButtonBasicStart()
{
	if (m_bPause == true) return;
	//初始化游戏地图
	m_gameControl.StartGame();

	//初始时间是300
	timeCount = 299;

	//判断是否正在玩游戏
	m_bPlaying = true;
	//禁止【开始游戏】按钮点击
	this->GetDlgItem(IDC_BUTTON_BASIC_START)->EnableWindow(false);

	//初始化进度条
	m_GameProgress.SetRange(0, 60 * 5);    //初始范围
	m_GameProgress.SetStep(-1);            //初始步数值
	m_GameProgress.SetPos(60 * 5);;        //设置初始值
	//启动定时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);

	//更新界面
	UpdataMap();

	Invalidate(FALSE);
	//设置进度条隐藏和剩余时间控件
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(TRUE);
	//this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(TRUE);
}



void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bPlaying == false) {
		return;
	}
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > MAX_ROW - 1 || nCol > MAX_COL - 1) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}


	//如果是第一次选中，绘制矩形框
	if (m_bFirstPoint) {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);
		//消除
		//获得路径
		Vertex avPath[MAX_VERTEX_NUM];
		int VertexNum;
		//连子判断
		if (m_gameControl.Link(avPath, VertexNum))
		{
			//画线
			DrawTipLine(avPath, VertexNum);
			//更新地图
			UpdataMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
		//判断是否胜利
		JudgeWin();
	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.x + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}


//绘制提示线
void CGameDlg::DrawTipLine(Vertex asvPath[MAX_VERTEX_NUM],int nVexNum)
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	for (int i = 0; i < nVexNum - 1; i++)
	{

		dc.LineTo(m_ptGameTop.x + asvPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + asvPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}

void CGameDlg::OnClickedButtonBasicTip()
{
	//如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex avPath[MAX_VERTEX_NUM];     //获得路径
	int nVexnum = 0;      //顶点个数
	if (m_gameControl.Help(avPath, nVexnum))
	{

		//画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);

		//画第一个点的提示框
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);

		//画提示线
		DrawTipLine(avPath, nVexnum);

		Sleep(1000);    //延迟

		UpdataMap();	//更新地图

		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
	}
	//为了使用第二个提示框可以看到，暂停200ms后，再刷新界面
}


void CGameDlg::OnClickedButtonBasicAgain()
{
	if (m_bPlaying == false)return;
	
	//重排
	m_gameControl.ResetGraph();
	//更新地图
	UpdataMap();
	//重绘界面
	InvalidateRect(m_rtGameRect, FALSE);
}

//判断胜负
void CGameDlg::JudgeWin(void)
{
	//游戏胜负判断
	int bGameStatus = m_gameControl.isWin(m_GameProgress.GetPos());
	//判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//将游戏标识改为false
		m_bPlaying = false;

		//关闭定时器
		KillTimer(PLAY_TIMER_ID);

		//提示获胜
		CString strTitle;
		this->GetWindowText(strTitle);
		if (bGameStatus == GAME_SUCESS)
		{
			MessageBox(_T("恭喜获胜！"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("很遗憾，时间到了！"), strTitle);
		}
		//还原开始游戏按钮，使用按钮可以点击
		this->GetDlgItem(IDC_BUTTON_BASIC_START)->EnableWindow(TRUE);
	}

}

void CGameDlg::OnClickedButtonBasicPause()
{
	//获得当前对话框的视频内容
	CClientDC dc(this);

	//游戏没在进行时，直接返回
	if (m_bPlaying == false)
		return;

	//如果游戏没有暂停
	if (m_bPause == false)
	{
		//hu绘制背景到内存DC中
		m_dcMem.BitBlt(MAP_LEFT, MAP_TOP, 640, 400, &m_dcCache, 0, 0, SRCCOPY);
	
		GetDlgItem(IDC_BUTTON_BASIC_TIP)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON_BASIC_AGAIN)->EnableWindow(0);
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BUTTON_BASIC_PAUSE)->SetWindowTextW(_T("继续游戏"));
	}

	//如果游戏暂停
	if (m_bPause == true)
	{
		UpdataMap();
		GetDlgItem(IDC_BUTTON_BASIC_TIP)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON_BASIC_AGAIN)->EnableWindow(1);
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新

		this->GetDlgItem(IDC_BUTTON_BASIC_PAUSE)->SetWindowTextW(_T("暂停游戏"));
	}

	m_bPause = !m_bPause;
}

void CGameDlg::OnClickedButtonBasicHelp()
{
	CHelpDialog dlg;
	dlg.DoModal();
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	JudgeWin();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && m_bPause == false)
	{	
		//游戏时间减一秒
		if (timeCount > -1)
		{
			CString str;
			str.Format(_T("%d"), timeCount);
			SetDlgItemText(IDC_EDIT_TIME, str);

			UpdateData(false);
			timeCount--;

			m_GameProgress.StepIt();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

//倒计时函数
void CGameDlg::DrawGameTime()
{
	CFont font;
	//font.CreatePointFont(720,"Arial");

}


void CGameDlg::OnEnChangeEditTime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
