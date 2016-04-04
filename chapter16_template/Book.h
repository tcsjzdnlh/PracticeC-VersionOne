#ifndef _xfs_Book_h_
#define _xfs_Book_h_

class CBook
{
public:

public:
	template<typename T>
	void IncrementLevel( T _level )
	{
		m_level += _level;
	}

public:
	int GetLevel() const;
	
private:
	int m_level = 0;
};



#endif