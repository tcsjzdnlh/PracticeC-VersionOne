#ifndef _xfs_Propertys_h_
#define _xfs_Propertys_h_

#include "Property.h"
#include "Flying.h"
#include "Books.h"
#include "Geometrys.h"

class CPropertys : public CProperty
{
public:
	CPropertys();
	unsigned int GetHeight();
private:
	CFlying			m_flying;
	CBooks			m_books;
	CGeometrys		m_gometrys;
};



#endif