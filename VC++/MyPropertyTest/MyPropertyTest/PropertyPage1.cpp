// PropertyPage1.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MyPropertyTest.h"
#include "PropertyPage1.h"
#include "afxdialogex.h"


// CPropertyPage1 �_�C�A���O

IMPLEMENT_DYNAMIC(CPropertyPage1, CPropertyPage)

CPropertyPage1::CPropertyPage1()
	: CPropertyPage(CPropertyPage1::IDD)
{

}

CPropertyPage1::~CPropertyPage1()
{
}

void CPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyPage1, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CPropertyPage1::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPropertyPage1 ���b�Z�[�W �n���h���[


void CPropertyPage1::OnBnClickedButton1()
{
	MessageBox(_T("�v���p�e�B�y�[�W�@"));
}
