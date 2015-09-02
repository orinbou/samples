#pragma once
#include "propertypage1.h"
#include "propertypage2.h"

// CMyPropertyPage

class CMyPropertyPage : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropertyPage)

public:
	CMyPropertyPage(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyPropertyPage(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMyPropertyPage();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CPropertyPage1 m_cpPage1;
	CPropertyPage2 m_cpPage2;
};


