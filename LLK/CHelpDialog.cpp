#include "pch.h"
#include "LLK.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{
	m_rtHelp.left = 0;
	m_rtHelp.top = 0;
	m_rtHelp.right = 440;
	m_rtHelp.bottom = 400;
}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	//ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR1, &CHelpDialog::OnThemechangedScrollbar1)
END_MESSAGE_MAP()


// CHelpDialog 消息处理程序


BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CClientDC dc(this);
	HANDLE hHelp = ::LoadImage(NULL, _T("theme\\picture\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcHelp.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcHelp.SelectObject(hHelp);

	//创建DC大小
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 440, 400);
	m_dcMem.SelectObject(&bmpMem);

	//绘制白色背景
	m_dcMem.BitBlt(0, 0, 440, 400, &m_dcHelp, 0, 0, SRCCOPY);
	//设置滚动条范围
	CScrollBar *pScrollBar = (CScrollBar*)GetDlgItem(IDC_SCROLLBAR_HELP);
	pScrollBar->SetScrollRange(0, 650);
	UpdateWindow();
	//绘制帮助信息
	UpdateHelp(0);


	return TRUE;
}


void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int Pos = pScrollBar->GetScrollPos();
	switch (nSBCode) {
	case SB_LINEUP:
		Pos -= 1;
		break;
	case SB_LINEDOWN:
		Pos += 1;
		break;
	case SB_PAGEUP:
		Pos -= m_rtHelp.bottom - m_rtHelp.top;
		break;
	case SB_PAGEDOWN:
		Pos += m_rtHelp.bottom - m_rtHelp.top;
	case SB_TOP:
		Pos = 0;
		break;
	case SB_BOTTOM:
		Pos = 700;
		break;
	case SB_THUMBTRACK:
	{
		Pos = nPos;
		break;
	}
	case SB_THUMBPOSITION:
		Pos = nPos;
		break;
	}
	pScrollBar->SetScrollPos(Pos);
	UpdateHelp(Pos);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CHelpDialog::UpdateHelp(int nPos)
{
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
	InvalidateRect(m_rtHelp, FALSE);
}
void CHelpDialog::UpdateWindow()
{
	// TODO: 在此处添加实现代码.
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);   //获得窗口大小
	this->GetClientRect(rtClient); //获得客户区大小
	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//设置窗口大小
	MoveWindow(0, 0, 500 - nSpanWidth, 450 - nSpanHeight);
	//设置对话框显示在Windows窗口中央
	CenterWindow();
}


void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 440, 450, &m_dcMem, 0, 0, SRCCOPY);
}


void CHelpDialog::OnThemechangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}