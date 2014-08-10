#pragma once
#include <exdisp.h>
#include <mshtmhst.h>
#include <exdispid.h>


namespace LibUI{

	class  CWebViewHandler;

	class UILIB_API CWebViewUI :
		public CActiveXUI
	{
	public:
		CWebViewUI(void);
		virtual ~CWebViewUI(void);

		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		virtual LPCSTR GetClass() const;

		void Navigate(LPCTSTR lpszUrl);

		void Refresh();

		void GoBack();

		void GoForward();

		LPCTSTR GetLocationURL();

		void SetWebViewHandler(CWebViewHandler *pWebViewHandler);

		HRESULT Invoke( DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS *pDispParams,VARIANT *pVarResult,EXCEPINFO *pExcepInfo,UINT *puArgErr);

	protected:

		virtual bool DoCreateControl();

		virtual void ReleaseControl();

		HRESULT RegisterHandler(BOOL inAdvise);
		

	private:
		DWORD m_dwCookie;
		IWebBrowser2 *m_pWebBroswer;
		CWebViewHandler *m_pHandler;
		C_P(CStdString,m_url,URL);
		C_P(HREFTYPE,m_bConextMenu,ContextMenu);
	};



	class UILIB_API CWebViewHandler :
		public IDispatch,
		public IDocHostUIHandler
	{
	public:
		CWebViewHandler():m_pWebView(NULL){};

		// IUnknown     
		virtual HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid,_COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject)
		{
			*ppvObject = NULL;
			if (riid == IID_IDispatch)
				*ppvObject = static_cast<IDispatch *>(this);
			else if(riid == IID_IDocHostUIHandler)
				*ppvObject = static_cast<IDocHostUIHandler *>(this);

			if (*ppvObject == NULL)
				AddRef();
			return *ppvObject == NULL?E_NOTIMPL:S_OK;
		};

		virtual ULONG STDMETHODCALLTYPE AddRef( void){InterlockedIncrement(&m_dwRef);return m_dwRef;};

		virtual ULONG STDMETHODCALLTYPE Release( void){return InterlockedDecrement(&m_dwRef);};

		// IDispatch
		virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount( UINT *pctinfo){return E_NOTIMPL;};

		virtual HRESULT STDMETHODCALLTYPE GetTypeInfo( UINT iTInfo,LCID lcid, ITypeInfo **ppTInfo){return E_NOTIMPL;};

		virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,__RPC__in_range(0,16384) UINT cNames,LCID lcid,__RPC__out_ecount_full(cNames) DISPID *rgDispId){return E_NOTIMPL;};

		virtual HRESULT STDMETHODCALLTYPE Invoke( DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS *pDispParams,VARIANT *pVarResult,EXCEPINFO *pExcepInfo,UINT *puArgErr)
		{
			return m_pWebView?m_pWebView->Invoke(dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr):S_FALSE;
		};

		// IDocHostUIHandler
		virtual HRESULT STDMETHODCALLTYPE ShowContextMenu( DWORD dwID,POINT *ppt,IUnknown *pcmdtReserved,IDispatch *pdispReserved){return m_pWebView?m_pWebView->GetContextMenu():S_OK;};

		virtual HRESULT STDMETHODCALLTYPE GetHostInfo( DOCHOSTUIINFO *pInfo){ if(pInfo != NULL)pInfo->dwFlags |= DOCHOSTUIFLAG_NO3DBORDER | DOCHOSTUIFLAG_SCROLL_NO; return S_OK;};

		virtual HRESULT STDMETHODCALLTYPE ShowUI( DWORD dwID,IOleInPlaceActiveObject *pActiveObject,IOleCommandTarget *pCommandTarget,IOleInPlaceFrame *pFrame,IOleInPlaceUIWindow *pDoc){return S_FALSE;};

		virtual HRESULT STDMETHODCALLTYPE HideUI( void){return S_OK;};

		virtual HRESULT STDMETHODCALLTYPE UpdateUI( void) {return S_OK;};

		virtual HRESULT STDMETHODCALLTYPE EnableModeless(BOOL fEnable){return S_OK;};

		virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate(BOOL fActivate){return S_OK;};

		virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(BOOL fActivate){return S_OK;};

		virtual HRESULT STDMETHODCALLTYPE ResizeBorder( LPCRECT prcBorder,IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow){return S_OK;};

		virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(  LPMSG lpMsg,const GUID *pguidCmdGroup,DWORD nCmdID){return S_FALSE;};

		virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath( LPOLESTR *pchKey,DWORD dw) {return S_OK;};

		virtual HRESULT STDMETHODCALLTYPE GetDropTarget( IDropTarget *pDropTarget,IDropTarget **ppDropTarget) {return E_NOTIMPL;};

		virtual HRESULT STDMETHODCALLTYPE GetExternal( IDispatch **ppDispatch){return E_NOTIMPL;};

		virtual HRESULT STDMETHODCALLTYPE TranslateUrl(  DWORD dwTranslate,LPWSTR pchURLIn,LPWSTR *ppchURLOut){return S_OK;};

		virtual HRESULT STDMETHODCALLTYPE FilterDataObject( IDataObject *pDO,IDataObject **ppDORet){return S_OK;};

		void SetWebView(CWebViewUI *pWebView){m_pWebView = pWebView;};
	private:
		LONG			 m_dwRef;
		CWebViewUI		*m_pWebView;
	};


};