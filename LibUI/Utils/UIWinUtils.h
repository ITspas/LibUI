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
		static void CSkin_Load(CWinWnd *pWinWnd,const char *path,const char *skin,CSkin type = SKIN_DIR);
	};
};
