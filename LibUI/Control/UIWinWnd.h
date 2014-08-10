#pragma once

namespace LibUI{


	class CWinWnd;

	class UILIB_API ICWinWndDelegate :
		public CRef
	{
	public:
		ICWinWndDelegate(CWinWnd *pWinWnd):m_pWinWnd(pWinWnd){};

		virtual void Init(CPaintManagerUI *pPaintManager) = 0;

	protected:
		CWinWnd *m_pWinWnd;
	};

	class UILIB_API CWinWnd :
		public CWindowWnd
	{
	public:
		CWinWnd(void);
		~CWinWnd(void);

		LPCSTR GetWindowClassName() const;

		virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );

		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	protected:
		C_P(CPaintManagerUI *,m_pm,PaintManager);
		C_P(bool,m_bAutoSize,AutoSize);
		C_P_R(ICWinWndDelegate *,m_pDelegate,Delegate);
	};

};
