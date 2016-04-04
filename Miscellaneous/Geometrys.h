#ifndef _xfs_Geometrys_h_
#define _xfs_Geometrys_h_

class CGeometrys
{
public:
	CGeometrys();

	void PrintName();

	template<typename T>
	unsigned int GetOne( T _value )
	{
		return _value;
	}


private:
	unsigned int		m_iheight;
	unsigned int		m_iweight;
};




#endif