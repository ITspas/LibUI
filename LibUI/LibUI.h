
#ifdef LIBUI_EXPORTS
#define UILIB_API __declspec(dllexport)
#else
#define UILIB_API __declspec(dllimport)
#endif


#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stddef.h>
#include <richedit.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>



#include "Core\UIDef.h"
#include "Core\UIRef.h"
#include "Core\UIBase.h"
#include "Core\UIManager.h"
#include "Core\UIDelegate.h"
#include "Core\UIControl.h"
#include "Core\UIContainer.h"
#include "Core\UIMarkup.h"
#include "Core\UIRender.h"

#include "Control\UICommonControls.h"
#include "Control\UIList.h"
#include "Control\UICombo.h"
#include "Control\UIActiveX.h"
#include "Control\UIRichEdit.h"
#include "Control\UIWinWnd.h"
#include "Control\UIWebView.h"

#include "Utils\UIDlgBuilder.h"
#include "Utils\UIWinUtils.h"





