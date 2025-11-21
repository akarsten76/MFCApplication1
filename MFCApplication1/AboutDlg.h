#pragma once

#include "afxdialogex.h"
#include <vector>

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);

private:
	CListCtrl m_moduleList;
	int m_nSortColumn;
	bool m_bSortAscending;

	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};
