#include "..\StdAfx.h"
#include <atlconv.h>
#include <comutil.h>
#pragma comment(lib,"comsuppw.lib")

namespace LibUI{

	CWebViewUI::CWebViewUI(void) :
		m_url(""),
		m_dwCookie(0),
		m_pHandler(NULL),
		m_pWebBroswer(NULL),
		m_bConextMenu(S_OK)
	{
		SetAttribute("clsid","{8856F961-340A-11D0-A96B-00C04FD705A2}");
	}


	CWebViewUI::~CWebViewUI(void)
	{
		if(m_pHandler)m_pHandler->Release();
		m_pWebBroswer->Release();
		ReleaseControl();
	}

	LPCSTR CWebViewUI::GetClass() const
	{
		return _T("WebViewUI");
	}

	void CWebViewUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
	{
		if (_tcscmp(pstrName,_T("url")) == 0)
		{
			m_url = pstrValue;
		}
		else CActiveXUI::SetAttribute(pstrName,pstrValue);
	}


	bool CWebViewUI::DoCreateControl()
	{
		if(!CActiveXUI::DoCreateControl())
			return false;
		GetControl(IID_IWebBrowser2,(void **)&m_pWebBroswer);
		if (!m_url.IsEmpty())
			this->Navigate(m_url);
		RegisterHandler(TRUE);
		return TRUE;
	}

	void CWebViewUI::ReleaseControl()
	{
		RegisterHandler(FALSE);
	}

	HRESULT CWebViewUI::RegisterHandler( BOOL inAdvise )
	{
		IWebBrowser2 *pWeb = NULL;
		IConnectionPoint *pCP = NULL;
		IConnectionPointContainer *pCPC = NULL;
		HRESULT hr = GetControl(IID_IWebBrowser2,(void **)&pWeb);
		if(FAILED(hr))return hr;
		hr = pWeb->QueryInterface(IID_IConnectionPointContainer,(void **)&pCPC);
		if (FAILED(hr))return hr;
		hr = pCPC->FindConnectionPoint(DIID_DWebBrowserEvents2,&pCP);
		if(FAILED(hr))return hr;
		if (inAdvise && m_pHandler)
			hr = pCP->Advise((IDispatch *)m_pHandler,&m_dwCookie);
		else
			hr = pCP->Unadvise(m_dwCookie);
		return hr;
	}

	void CWebViewUI::Navigate( LPCTSTR lpszUrl )
	{
		if(lpszUrl && m_pWebBroswer)
		{
			VARIANT url;
			url.vt = VT_BSTR;
			url.bstrVal = T2BSTR(lpszUrl);
			m_pWebBroswer->Navigate2(&url,NULL,NULL,NULL,NULL);
		}
	}

	void CWebViewUI::Refresh()
	{
		if(m_pWebBroswer)
		{
			m_pWebBroswer->Refresh();
		}
	}

	void CWebViewUI::GoBack()
	{
		if(m_pWebBroswer)
		{
			m_pWebBroswer->GoBack();
		}
	}

	void CWebViewUI::GoForward()
	{
		if(m_pWebBroswer)
		{
			m_pWebBroswer->GoForward();
		}
	}

	LPCTSTR CWebViewUI::GetLocationURL()
	{
		if(m_pWebBroswer)
		{
			BSTR url;
			if(SUCCEEDED(m_pWebBroswer->get_LocationURL(&url)))
			{
				return _com_util::ConvertBSTRToString(url);
			}
		}
		return NULL;
	}

	void CWebViewUI::SetWebViewHandler( CWebViewHandler *pWebViewHandler )
	{
		RegisterHandler(FALSE);
		m_pHandler = pWebViewHandler;
		m_pHandler->SetWebView(this);
		RegisterHandler(TRUE);
	}

	HRESULT CWebViewUI::Invoke( DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS *pDispParams,VARIANT *pVarResult,EXCEPINFO *pExcepInfo,UINT *puArgErr )
	{
		if (dispIdMember == DISPID_NAVIGATECOMPLETE2)
		{
			IDispatch *pDispatch = NULL;
			if(!m_pWebBroswer)return S_OK;
			HRESULT hr = m_pWebBroswer->get_Document(&pDispatch);
			if (FAILED(hr))return S_OK;
			ICustomDoc *pDoc = NULL;
			hr = pDispatch->QueryInterface(IID_ICustomDoc,(void **)&pDoc);
			if(FAILED(hr))return S_OK;
			pDoc->SetUIHandler(m_pHandler);
		}
		else if(dispIdMember == DISPID_BEFORENAVIGATE2)
		{
			BSTR url = pDispParams->rgvarg[5].pvarVal->bstrVal;
			CStdString strUrl;
			strUrl.Append(_com_util::ConvertBSTRToString(url));
			int idx = strUrl.Find(_T("://"));
			if(idx > 0 && strUrl.Left(idx) == _T("app"))
			{
				*pDispParams->rgvarg[0].pboolVal = VARIANT_TRUE;
				GetManager()->SendNotify(this,"ExtURL",(WPARAM)strUrl.GetData());
			}
		}
		else if (dispIdMember == DISPID_NEWWINDOW3)
		{
			 *(pDispParams->rgvarg[3].pboolVal) = VARIANT_TRUE;
			 m_pWebBroswer->Navigate2(pDispParams->rgvarg,NULL,NULL,NULL,NULL);
		}
		return S_OK;
	}

};
