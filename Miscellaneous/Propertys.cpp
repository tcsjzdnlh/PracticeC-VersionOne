#include "Propertys.h"

CPropertys::CPropertys()
{

}

unsigned int CPropertys::GetHeight()
{
	m_gometrys.PrintName();
	return m_gometrys.GetOne<unsigned int>( 300 );
}
