#include "StdAfx.h"
#include "A.h"


A::A(void)
{
	this->m_strA = _T( "AAA" );
}


A::~A(void)
{
}

void A::hogeA()
{
	TRACE( _T( "hogeA! %s\n" ), this->m_strA );
}
