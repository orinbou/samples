#pragma once
#include "base.h"

class A
	:	public Base
{
public:
	A(void);
	~A(void);

	double m_dA[10];
	CString m_strA;

	void hogeA();
};

