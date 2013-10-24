
// SnakeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Snake.h"
#include "SnakeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSnakeDlg 对话框



CSnakeDlg::CSnakeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSnakeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSnakeDlg 消息处理程序

BOOL CSnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetGameRuler();
	SetTimer(SnakeMoveTimerID,delta,NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSnakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		{
			//Draw
			CPaintDC dc(this);

			CRect rectWnd;
			GetWindowRect(&rectWnd);
			int nWidth = rectWnd.Width();
			int nHeight= rectWnd.Height();

			CDC MemDC;
			CBitmap MemBitmap;
			MemDC.CreateCompatibleDC (&dc);
			MemBitmap.CreateCompatibleBitmap(&dc,nWidth,nHeight);

			CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
			MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));

			POINT point[2];

			point[0].x = OffsizeX;
			point[0].y = OffsizeY;
			point[1].x = OffsizeX;
			point[1].y = OffsizeY + GridHeight * (MapHeight );
			MemDC.Polyline(point, 2);

			point[0].x = OffsizeX + GridWidth * (MapWidth );
			point[0].y = OffsizeY;
			point[1].x = OffsizeX + GridWidth * (MapWidth );
			point[1].y = OffsizeY + GridHeight * (MapHeight );
			MemDC.Polyline(point, 2);

			//for(int i = 0; i < MapWidth; ++i)
			//{
			//	dc.Polyline(point, 2);
			//	point[0].x = point[0].x + GridWidth;
			//	point[1].x = point[1].x + GridWidth;
			//}

			point[0].x = OffsizeX;
			point[0].y = OffsizeY;
			point[1].x = OffsizeX + GridWidth * (MapWidth );
			point[1].y = OffsizeY;
			MemDC.Polyline(point, 2);

			point[0].x = OffsizeX;
			point[0].y = OffsizeY + GridHeight * (MapHeight );
			point[1].x = OffsizeX + GridWidth * (MapWidth );
			point[1].y = OffsizeY + GridHeight * (MapHeight );
			MemDC.Polyline(point, 2);

			//for(int i = 0; i < MapHeight; ++i)
			//{
			//	dc.Polyline(point, 2);

			//	point[0].y += GridHeight;
			//	point[1].y += GridHeight;
			//}

			RECT rect;
			Chessboard& cb=GetChessboard();

			for(int x = 0; x < MapWidth; x = x + 1)
			{
				for(int y = 0; y < MapHeight; y = y + 1)
				{
					if(cb.GetIdOfPoint(ChessPoint(x,y)) == GridSnake)
					{
						MemDC.SelectStockObject(BLACK_BRUSH);

						rect.left = OffsizeX + x * GridWidth;
						rect.top = OffsizeY + y * GridHeight;
						rect.right = rect.left + GridWidth;
						rect.bottom = rect.top + GridHeight;

						MemDC.Ellipse(&rect);
					}
					else if(cb.GetIdOfPoint(ChessPoint(x,y)) == GridFood)
					{
						MemDC.SelectStockObject(WHITE_BRUSH);

						rect.left = OffsizeX + x * GridWidth;
						rect.top = OffsizeY + y * GridHeight;
						rect.right = rect.left + GridWidth;
						rect.bottom = rect.top + GridHeight;

						MemDC.Ellipse(&rect);
					}
				}
			}

			dc.BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
			MemBitmap.DeleteObject();
			MemDC.DeleteDC();
		}
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Result result= GetGameRuler().Go();
	Invalidate();
	if (result==Result::Win)
	{
		KillTimer(SnakeMoveTimerID);
		MessageBox(L"You Win!");
	}
	if (result==Result::Lose)
	{
		//MessageBox(L"You Lose!");
		KillTimer(SnakeMoveTimerID);
		MessageBox(L"You Lose!");
	}
	CDialogEx::OnTimer(nIDEvent);

}


void CSnakeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int x=point.x-(GetSnake().begin()->x*GridWidth+OffsizeX);
	int y=point.y-(GetSnake().begin()->y*GridHeight+OffsizeY);
	if (x==0)
	{
		if (y>0)
		{
			GetGameRuler().ChangeDirection(ChessPoint(0,1));//UP
		}
		else if (y<0)
		{
			GetGameRuler().ChangeDirection(ChessPoint(0,-1));//DOWN
		}
	}

	double tanxy=y/(double)x;
	bool result=true;
	if (tanxy>1)
	{
		if (x>0)
		{
			result&=GetGameRuler().ChangeDirection(ChessPoint(0,1));//UP
		}
		else
		{
			result&=GetGameRuler().ChangeDirection(ChessPoint(0,-1));//DOWN
		}

		if (!result)
		{
			if (x>0)
			{
				GetGameRuler().ChangeDirection(ChessPoint(1,0));//RIGHT
			}
			else
			{
				GetGameRuler().ChangeDirection(ChessPoint(-1,0));//LEFT
			}
		}
	}
	else if (tanxy>=-1)//-1<=tanxy<=1
	{
		if (x>0)
		{
			result&=GetGameRuler().ChangeDirection(ChessPoint(1,0));//RIGHT
		}
		else
		{
			result&=GetGameRuler().ChangeDirection(ChessPoint(-1,0));//LEFT
		}

		if (!result)
		{
			if (y>0)
			{
				GetGameRuler().ChangeDirection(ChessPoint(0,1));//UP
			}
			else
			{
				GetGameRuler().ChangeDirection(ChessPoint(0,-1));//DOWN
			}
		}
	}
	else 
	{
		if (x>0)
		{
			result&=GetGameRuler().ChangeDirection(ChessPoint(0,-1));//DOWN
		}
		else
		{
			result&=GetGameRuler().ChangeDirection(ChessPoint(0,1));//UP
		}

		if (!result)
		{
			if (x>0)
			{
				GetGameRuler().ChangeDirection(ChessPoint(1,0));//RIGHT
			}
			else
			{
				GetGameRuler().ChangeDirection(ChessPoint(-1,0));//LEFT
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CSnakeDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
