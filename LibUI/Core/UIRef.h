#pragma once

namespace LibUI{

	class UILIB_API CRef
	{
	public:
		CRef(void);
		virtual ~CRef(void);

		void Retain();

		void Release();

		unsigned int RetainCount();

	private:
		unsigned int m_iCount;
	};

};

