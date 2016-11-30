
// FreeCellStarter2010Dlg.h : header file
//

#include"cell.h"
#pragma once


// CFreeCellStarter2010Dlg dialog
class CFreeCellStarter2010Dlg : public CDialogEx
{
private:
	std::vector<Cell*> mCells;

// Construction
public:
	CFreeCellStarter2010Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FREECELLSTARTER2010_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
