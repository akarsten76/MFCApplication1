#include "pch.h"
#include "framework.h"
#include "AboutDll.h"
#include "AboutDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE AboutDllDLL = { FALSE };
static HINSTANCE g_hInstance = NULL;

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("AboutDll.DLL Initializing!\n");

		if (!AfxInitExtensionModule(AboutDllDLL, hInstance))
			return 0;

		g_hInstance = hInstance;
		new CDynLinkLibrary(AboutDllDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("AboutDll.DLL Terminating!\n");
		AfxTermExtensionModule(AboutDllDLL);
	}
	return 1;
}

extern "C" ABOUTDLL_API void ShowAboutDialog(HWND hParent)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CAboutDlg dlg;
	dlg.DoModal();
}
