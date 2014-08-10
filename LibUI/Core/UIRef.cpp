#include "..\StdAfx.h"

namespace LibUI{

	CRef::CRef(void) :
		m_iCount(0)
	{
	}


	CRef::~CRef(void)
	{

	}

	void CRef::Retain()
	{
		m_iCount++;
	}

	void CRef::Release()
	{
		if(--m_iCount == 0)
		{
			delete this;
		}
	}

	unsigned int CRef::RetainCount()
	{
		return m_iCount;
	}

};