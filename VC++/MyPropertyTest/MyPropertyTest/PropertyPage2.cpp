// PropertyPage2.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MyPropertyTest.h"
#include "PropertyPage2.h"
#include "afxdialogex.h"


// CPropertyPage2 �_�C�A���O

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


// CPropertyPage2 ���b�Z�[�W �n���h���[


void CPropertyPage2::OnBnClickedButton2()
{
	MessageBox(_T("�v���p�e�B�y�[�W�A"));
}
