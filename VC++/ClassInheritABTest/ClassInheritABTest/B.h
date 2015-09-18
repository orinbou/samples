#pragma once
#include "base.h"

class B
	:	public Base
{
public:
	B(void);
	~B(void);

	bool m_bB[10];
	CString m_strB;

	void hogeB();
};

