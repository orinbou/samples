// MyPropertyPage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MyPropertyTest.h"
#include "MyPropertyPage.h"


// CMyPropertyPage

IMPLEMENT_DYNAMIC(CMyPropertyPage, CPropertySheet)

CMyPropertyPage::CMyPropertyPage(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	//this->m_psh.dwFlags |= PSH_NOAPPLYNOW;
	//this->m_psh.dwFlags &= ~PSH_HASHELP;

	AddPage(&m_cpPage1);
	AddPage(&m_cpPage2);
}

CMyPropertyPage::CMyPropertyPage(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	//this->m_psh.dwFlags |= PSH_NOAPPLYNOW;
	//this->m_psh.dwFlags &= ~PSH_HASHELP;

	AddPage(&m_cpPage1);
	AddPage(&m_cpPage2);
}

CMyPropertyPage::~CMyPropertyPage()
{
}


BEGIN_MESSAGE_MAP(CMyPropertyPage, CPropertySheet)
END_MESSAGE_MAP()


// CMyPropertyPage メッセージ ハンドラー
