#include "MainWinWnd.h"
#include <stdio.h>
#include <exdisp.h>
#include <mshtmhst.h>
#include <exdispid.h>


MainWinWnd::MainWinWnd( CWinWnd *pWinWnd ):
	ICWinWndDelegate(pWinWnd)
{

}


void MainWinWnd::Init( CPaintManagerUI *pPaintManager )
{
	CComboUI *pBtn = (CComboUI *)pPaintManager->FindControl(_T("Btn"));
	pBtn->OnEvent += MakeDelegate(this,&MainWinWnd::onEventButton);

}

bool MainWinWnd::onEventButton( void *event )
{
	TEventUI *pEvent = (TEventUI *)event;
	if (pEvent->Type == UIEVENT_BUTTONDOWN)
	{
		CVerticalLayoutUI *pLayout = (CVerticalLayoutUI *)m_pWinWnd->GetPaintManager()->FindControl(_T("cnt"));
	

	}
	return false;
}
