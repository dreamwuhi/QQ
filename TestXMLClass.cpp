// TestXMLClass.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LoginFrame.h"
//#include "MainFrame.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	HRESULT Hr = ::CoInitialize(NULL);
	 if( FAILED(Hr) ) return 0;

	CLoginFrame duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE | WS_EX_TOPMOST);
	duiFrame.SetIcon(IDI_ICON_QQ);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();

// 	 CMainFrame duiFrame;
// 	 duiFrame.Create(NULL, _T("WeChat"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE | WS_EX_TOPMOST);
// 	 //duiFrame.SetIcon(IDI_ICON_QQ);
// 	 duiFrame.CenterWindow();
// 	 duiFrame.ShowModal();


	::CoUninitialize();
	return 0;
}