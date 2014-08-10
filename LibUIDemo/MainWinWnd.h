#pragma once
#include "..\LibUI\LibUI.h"

using namespace LibUI;

class MainWinWnd :
	public ICWinWndDelegate
{
public:
	MainWinWnd(CWinWnd *pWinWnd);

	void Init(CPaintManagerUI *pPaintManager);

	bool onEventButton(void *event);

};

