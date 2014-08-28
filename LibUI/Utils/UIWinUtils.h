#pragma once

namespace LibUI{

	typedef enum tagCSkin
	{
		SKIN_DIR,
		SKIN_ZIP
	} CSkin;

	class CDialogBuilderExt :
		public IDialogBuilderCallback
	{
	public:
		virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	};

	class UILIB_API CWinUtils
	{
	public:
		static void CSkin_Load(CWinWnd *pWinWnd,const TCHAR *path,const TCHAR *skin,CSkin type = SKIN_DIR);
	};
};
