#include <windows.h>
#include "MainWinWnd.h"
#include <stdio.h>


int WINAPI WinMain(  HINSTANCE hInstance,  HINSTANCE hPrevInstance,  LPSTR lpCmdLine,  int nShowCmd )
{
	CPaintManagerUI::SetInstance(hInstance);
	::CoInitialize(NULL);

	CWinWnd *pWinWnd = new CWinWnd();

	pWinWnd->SetDelegate(new MainWinWnd(pWinWnd));

	pWinWnd->SetAutoSize(true);

	pWinWnd->Create(NULL,_T("Main"),UI_WNDSTYLE_FRAME,0L);

	CWinUtils::CSkin_Load(pWinWnd,_T("Skin\\SkinRes"),_T("skin.xml"));

	::ShowWindow(pWinWnd->GetHWND(),SW_SHOW);

	CPaintManagerUI::MessageLoop();
	::CoUninitialize();
	return 0;
}