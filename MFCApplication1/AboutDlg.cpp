#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "AboutDlg.h"
#include "ModuleInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX), m_nSortColumn(-1), m_bSortAscending(true)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODULE_LIST, m_moduleList);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_MODULE_LIST, &CAboutDlg::OnColumnClick)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set up list control columns
	m_moduleList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_moduleList.InsertColumn(0, _T("Filename"), LVCFMT_LEFT, 200);
	m_moduleList.InsertColumn(1, _T("Version"), LVCFMT_LEFT, 100);
	m_moduleList.InsertColumn(2, _T("Date"), LVCFMT_LEFT, 120);

	// Get and display loaded modules
	std::vector<ModuleInfo> modules = GetLoadedModules();
	int row = 0;
	for (const auto& mod : modules)
	{
		int idx = m_moduleList.InsertItem(row, mod.fileName.c_str());
		m_moduleList.SetItemText(idx, 1, mod.version.c_str());
		m_moduleList.SetItemText(idx, 2, mod.fileDate.c_str());
		m_moduleList.SetItemData(idx, idx);
		row++;
	}

	return TRUE;
}

struct SortParam
{
	CListCtrl* pList;
	int nColumn;
	bool bAscending;
};

int CALLBACK CAboutDlg::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	SortParam* pParam = (SortParam*)lParamSort;
	CListCtrl* pList = pParam->pList;

	LVFINDINFO findInfo;
	findInfo.flags = LVFI_PARAM;

	findInfo.lParam = lParam1;
	int idx1 = pList->FindItem(&findInfo);
	findInfo.lParam = lParam2;
	int idx2 = pList->FindItem(&findInfo);

	CString str1 = pList->GetItemText(idx1, pParam->nColumn);
	CString str2 = pList->GetItemText(idx2, pParam->nColumn);

	int result = str1.CompareNoCase(str2);
	return pParam->bAscending ? result : -result;
}

void CAboutDlg::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (pNMLV->iSubItem == m_nSortColumn)
		m_bSortAscending = !m_bSortAscending;
	else
	{
		m_nSortColumn = pNMLV->iSubItem;
		m_bSortAscending = true;
	}

	SortParam param;
	param.pList = &m_moduleList;
	param.nColumn = m_nSortColumn;
	param.bAscending = m_bSortAscending;

	m_moduleList.SortItems(CompareFunc, (LPARAM)&param);

	*pResult = 0;
}
