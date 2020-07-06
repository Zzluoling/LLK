#include "pch.h"
#include "LLK.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog �Ի���

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


// CHelpDialog ��Ϣ�������


BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CClientDC dc(this);
	HANDLE hHelp = ::LoadImage(NULL, _T("theme\\picture\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcHelp.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcHelp.SelectObject(hHelp);

	//����DC��С
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 440, 400);
	m_dcMem.SelectObject(&bmpMem);

	//���ư�ɫ����
	m_dcMem.BitBlt(0, 0, 440, 400, &m_dcHelp, 0, 0, SRCCOPY);
	//���ù�������Χ
	CScrollBar *pScrollBar = (CScrollBar*)GetDlgItem(IDC_SCROLLBAR_HELP);
	pScrollBar->SetScrollRange(0, 650);
	UpdateWindow();
	//���ư�����Ϣ
	UpdateHelp(0);


	return TRUE;
}


void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ˴����ʵ�ִ���.
	//�������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);   //��ô��ڴ�С
	this->GetClientRect(rtClient); //��ÿͻ�����С
	//����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//���ô��ڴ�С
	MoveWindow(0, 0, 500 - nSpanWidth, 450 - nSpanHeight);
	//���öԻ�����ʾ��Windows��������
	CenterWindow();
}


void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 440, 450, &m_dcMem, 0, 0, SRCCOPY);
}


void CHelpDialog::OnThemechangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �ù���Ҫ��ʹ�� Windows XP ����߰汾��
	// ���� _WIN32_WINNT ���� >= 0x0501��
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}