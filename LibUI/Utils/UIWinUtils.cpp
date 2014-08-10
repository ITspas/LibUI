#include "..\StdAfx.h"

namespace LibUI{

	CControlUI * CDialogBuilderExt::CreateControl(LPCTSTR pstrClass)
	{
		if (_tcscmp(pstrClass,_T("WebView")) == 0)return new CWebViewUI();
		else return NULL;
	}

	void CWinUtils::CSkin_Load( CWinWnd *pWinWnd,const char *path,const char *skin,CSkin type /*= SKIN_DIR*/ )
	{
		if(!pWinWnd || !path || !skin)return;
		CPaintManagerUI *pPaintManager = pWinWnd->GetPaintManager();
		path = pPaintManager->GetInstancePath() + path;
		switch (type)
		{
		case SKIN_DIR:				
			pPaintManager->SetResourcePath(path);
			break;
		case SKIN_ZIP:	
			pPaintManager->SetResourceZip(path);
			break;
		default:
			return;
		}
		
		CControlUI *pRoot = CDialogBuilder().Create(skin,(UINT)0,&(CDialogBuilderExt()),pPaintManager);
		if (pRoot && pPaintManager->AttachDialog(pRoot) && NULL != pWinWnd->GetDelegate())
			pWinWnd->GetDelegate()->Init(pWinWnd->GetPaintManager());
	}

};