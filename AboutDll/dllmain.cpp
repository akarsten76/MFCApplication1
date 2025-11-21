#include "pch.h"
#include "framework.h"
#include "AboutDll.h"
#include "AboutDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE AboutDllDLL = { FALSE };

class CAboutDllApp : public CWinApp
{
public:
	CAboutDllApp() {}

	virtual BOOL InitInstance()
	{
		if (!AfxInitExtensionModule(AboutDllDLL, m_hInstance))
			return FALSE;

		new CDynLinkLibrary(AboutDllDLL);
		return TRUE;
	}

	virtual int ExitInstance()
	{
		AfxTermExtensionModule(AboutDllDLL);
		return CWinApp::ExitInstance();
	}
};

CAboutDllApp theApp;

extern "C" ABOUTDLL_API void ShowAboutDialog(HWND hParent)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CAboutDlg dlg;
	dlg.DoModal();
}
