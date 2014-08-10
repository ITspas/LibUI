// UIRender
#define GetAValue(rgb)      (LOBYTE((rgb)>>24))

#define C_P(_T,_N,_V)	\
	protected:_T _N;	\
 	public:void Set##_V(_T val){_N = val;};	\
 	public:_T Get##_V(){return _N;}

#define C_P_R(_T,_N,_V)	\
	protected:_T _N;	\
	public:void Set##_V(_T val){if(_N)_N->Release();_N = NULL;if(val){_N = val;_N->Retain();}};		\
	public:_T Get##_V(){return _N;}