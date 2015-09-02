// PropertyPage2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MyPropertyTest.h"
#include "PropertyPage2.h"
#include "afxdialogex.h"


// CPropertyPage2 ダイアログ

IMPLEMENT_DYNAMIC(CPropertyPage2, CPropertyPage)

CPropertyPage2::CPropertyPage2()
	: CPropertyPage(CPropertyPage2::IDD)
{

}

CPropertyPage2::~CPropertyPage2()
{
}

void CPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyPage2, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON2, &CPropertyPage2::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPropertyPage2 メッセージ ハンドラー


void CPropertyPage2::OnBnClickedButton2()
{
	MessageBox(_T("プロパティページ②"));
}
