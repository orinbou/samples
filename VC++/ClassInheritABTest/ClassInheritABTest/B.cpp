#include "StdAfx.h"
#include "B.h"


B::B(void)
{
	this->m_strB = _T( "BBB" );
}


B::~B(void)
{
}

void B::hogeB()
{
	TRACE( _T( "hogeB! %s\n" ), this->m_strB );
}
