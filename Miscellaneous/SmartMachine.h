#ifndef _xfs_SmartMachine_h_
#define _xfs_SmartMachine_h_

#include "Propertys.h"

template<typename T>
class CSmartMachine
{
public:
	CSmartMachine()
	{}
	unsigned int GetHeight()
	{
		return m_psmp.GetHeight();
	}
	
	void PrintName()
	{

	}

private:
	CPropertys		m_psmp;
};




#endif