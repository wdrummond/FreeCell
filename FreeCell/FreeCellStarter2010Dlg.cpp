
// FreeCellStarter2010Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeCellStarter2010.h"
#include "FreeCellStarter2010Dlg.h"
#include "afxdialogex.h"
#include "WindowsCards.h"
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CFreeCellStarter2010Dlg dialog




CFreeCellStarter2010Dlg::CFreeCellStarter2010Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFreeCellStarter2010Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFreeCellStarter2010Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFreeCellStarter2010Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CFreeCellStarter2010Dlg message handlers

BOOL CFreeCellStarter2010Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// Setup the cards
	bool ok = InitializeCards();
	if(!ok)
	{
		MessageBox(L"cards.dll failed to initialize", L"Error");
		return true;
	}

	//STEP 1!! initialize all 16 cells at their correct locations
	//3 for loops

	//create the 4 free cells
	for(int i = 0; i < 4; i++)
	{	
		int x1, y1, x2, y2;
		x1 = ((i+1)*gCardWidth)+spaceBetweenCells*.5;
		y1 = 20;
		x2 = x1+gCardWidth;
		y2 = y1+gCardHeight;
		TempCell* fCell = new TempCell(x1, y1, x2, y2);
		mCells.push_back(fCell);
	}

	//create the 4 end cells
	for( int j = 0; j < 4; j++)
	{
		//must be right of the temp cells
		int x1, y1, x2, y2;
		x1 = (((j+10)+(cellToCardMargin))*gCardWidth)+spaceBetweenCells;
		y1 = 20;
		x2 = x1+gCardWidth;
		y2 = y1+gCardHeight;
		EndCell* eCell = new EndCell(x1, y1, x2, y2);
		mCells.push_back(eCell);
	}

	//create the rest of the cells.
	for ( int c = 0; c < 8; c++)
	{
		//Underneath other cells
		int x1, y1, x2, y2;
		x1 = (((c+3.1)*gCardWidth)+spaceBetweenCells)*1.2;
		y1 = 150;
		x2 = x1+gCardWidth;
		y2 = y1+gCardHeight*4;
		StartCell* sCell = new StartCell(x1, y1, x2, y2);
		mCells.push_back(sCell);
	}
	



	// STEP 3!! Add the 52 cards to the 8 start cells
	std::vector<int> randIndex;
	for (int i = 0; i < 52; i ++)
	{
		randIndex.push_back(i);
	}
	std::random_shuffle(randIndex.begin(),randIndex.end());

	int cellIndex = 8;
	for ( int i = 0; i < 52; i++)
	{
		mCells[cellIndex]->AddCard(randIndex[i]);
		cellIndex += 1;
		if (cellIndex == 16) 
		{
			cellIndex = 8;
		}

	}



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFreeCellStarter2010Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFreeCellStarter2010Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting

		//paint the Background ??Not working//
		CRect rect;
		COLORREF backgroundColor = RGB(16,155,16);
		CBrush backgroundBrush( backgroundColor );
		dc.SelectObject(backgroundBrush);
		dc.Rectangle(rect);

		//!!!!!for loop and draw each cell
		//STEP 2!! PAINT ALL CELLS
		for(size_t i = 0; i < mCells.size(); i++)
		{
			mCells[i]->Draw(dc);
		}


		// This code draws each card horizontally.
		//int x=2;
		//int y=130;
		//bool highlighted = false;
		//for(int index=0; index<52; index++)
		//{
		//	DrawCard(dc, x, y, index, highlighted);
		//	x += 26;
		//}
		
		CDialogEx::OnPaint();
	}

	
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFreeCellStarter2010Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFreeCellStarter2010Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	UninstallCards();

	CDialogEx::OnClose();
}


void CFreeCellStarter2010Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);
	int w = rect.Width();
	int h = rect.Height();
	int x1,x2,y1,y2;

	if (clickNum == -1)
	{
		for(int i = 0; i < 16; i++)
		{
			x1 = mCells[i]->mLeft;
			x2 = mCells[i]->mTop;
			y1 = mCells[i]->nRight;
			y2 = mCells[i]->mBottom;
			if( point.x >= x1*w/100 && point.y <= h-y1*h/100 && point.x <= x2*w/100 && point.y >= h-y2*h/100)
			{
				int picked = i;
			}

		if (mCells[i]->CanRemoveCard())
		{
			clickNum = 1;
		}
	}

	if (clickNum == 1)
	{

	}

	CDialogEx::OnLButtonDown(nFlags, point);

}
