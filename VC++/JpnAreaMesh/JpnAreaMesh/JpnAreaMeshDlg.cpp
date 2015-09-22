
// JpnAreaMeshDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "JpnAreaMesh.h"
#include "JpnAreaMeshDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJpnAreaMeshDlg �_�C�A���O

CJpnAreaMeshDlg::CJpnAreaMeshDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_JPNAREAMESH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJpnAreaMeshDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_LAT, m_edtLat);
	DDX_Control(pDX, IDC_EDT_LON, m_edtLon);
	DDX_Control(pDX, IDC_CHK_DOKUJI, m_chkDokujiMeshCode);
	DDX_Control(pDX, IDC_BTN_GET_MESH_CODE, m_btnGetMeshCode);
	DDX_Control(pDX, IDC_EDT_MESH_CODE, m_edtMeshCode);
	DDX_Control(pDX, IDC_BTN_GET_LAT_LON, m_btnGetLatLon);
}

BEGIN_MESSAGE_MAP(CJpnAreaMeshDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDT_LAT, &CJpnAreaMeshDlg::UpdateControls)
	ON_EN_CHANGE(IDC_EDT_LON, &CJpnAreaMeshDlg::UpdateControls)
	ON_BN_CLICKED(IDC_BTN_GET_MESH_CODE, &CJpnAreaMeshDlg::OnBnClickedBtnGetMeshCode)
	ON_EN_CHANGE(IDC_EDT_MESH_CODE, &CJpnAreaMeshDlg::UpdateControls)
	ON_BN_CLICKED(IDC_BTN_GET_LAT_LON, &CJpnAreaMeshDlg::OnBnClickedBtnGetLatLon)
END_MESSAGE_MAP()


// CJpnAreaMeshDlg ���b�Z�[�W �n���h���[

BOOL CJpnAreaMeshDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// �����l�i�V�h��V�h2-1-1 �G���f�j
	this->m_edtLat.SetWindowText(_T("35.68823693"));
	this->m_edtLon.SetWindowText(_T("139.70974445"));
	this->m_edtMeshCode.SetWindowText(_T("5339-45-26"));
	this->m_chkDokujiMeshCode.SetCheck(BST_CHECKED);

	// ��������
	this->UpdateControls();

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

// ��������
void CJpnAreaMeshDlg::UpdateControls()
{
	// �ܓx
	CString strLat;
	this->m_edtLat.GetWindowText(strLat);

	// �o�x
	CString strLon;
	this->m_edtLon.GetWindowText(strLon);

	// ���b�V���R�[�h
	CString strMeshCode;
	this->m_edtMeshCode.GetWindowText(strMeshCode);

	// �擾�{�^��
	this->m_btnGetMeshCode.EnableWindow((!strLat.IsEmpty() && !strLon.IsEmpty()) ? TRUE : FALSE);
	this->m_btnGetLatLon.EnableWindow((!strMeshCode.IsEmpty()) ? TRUE : FALSE);
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CJpnAreaMeshDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CJpnAreaMeshDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// �G���A�R�[�h���擾����
void CJpnAreaMeshDlg::OnBnClickedBtnGetMeshCode()
{
	// �ܓx
	CString strLat;
	this->m_edtLat.GetWindowText(strLat);
	const double dLat = _ttof(strLat);

	// �o�x
	CString strLon;
	this->m_edtLon.GetWindowText(strLon);
	const double dLon = _ttof(strLon);

	// �Ǝ����b�V���R�[�h�H
	const bool bIsDokujiMesh = (this->m_chkDokujiMeshCode.GetCheck() == BST_CHECKED) ? true : false;

	// ���b�V���R�[�h�擾
	const CString strMeshCode = this->GetMeshCode(dLat, dLon, bIsDokujiMesh);
	TRACE(strMeshCode + _T("\n"));

	// ���b�V���R�[�h�\��
	CString strResultMsg;
	strResultMsg.Format(_T("���b�V���R�[�h : %s"), strMeshCode);
	MessageBox(strResultMsg);
}

/**
* �ܓx�o�x���烁�b�V���R�[�h���擾����.
* @see http://d.hatena.ne.jp/letitride/20111215
* @param dLat �ܓx
* @param dLon �o�x
* @return ���b�V���R�[�h������
*/
CString CJpnAreaMeshDlg::GetMeshCode(
	const double dLat,
	const double dLon,
	const bool bIsDokujiMesh
)
{
	// -----------------------------------------------------------------------
	// ��1�����b�V���i�������̂͑�1���n����j
	// �E1�ӂ̒�������80km�̎l�p�`�ƂȂ�܂��B
	// �E4���̐����ō\������A�g�̐���[�̈ܓx����2���A�o�x����2���ŕ\���܂��B
	// �E�ܓx��1.5�{�����l�̏�2�� + �o�x����100�������l�ƂȂ�܂��B
	// -----------------------------------------------------------------------
	const int iCode12 = static_cast<int>(dLat * 1.5);
	const int iCode34 = static_cast<int>(dLon - 100.0);
	CString strMeshCode1234;
	strMeshCode1234.Format(_T("%02d%02d"), iCode12, iCode34);

	// -----------------------------------------------------------------------
	// ��2�����b�V���i�������̂͑�2���n����j
	// �E1�����b�V�����c�A���Ƃ���8���������l�p�`(1�����b�V����64����)
	// �E1�ӂ̒����͖�4km�ŁA�ܓx5��(5 / 60)�A�o�x7��30�b(7 / 60 + 30 / 60 / 60)�ƂȂ�܂��B
	// �E1�����b�V���̐���[����_(0, 0)�Ƃ��A��1�����k�����ւ̃��b�V���ʒu�A��1�����������ւ̃��b�V���ʒu��\���܂��B
	// �E1�����b�V���Ƒg�ݍ��킹��nnnn-nn�ƋL�q���܂��B
	// -----------------------------------------------------------------------
	// 1�����b�V���̓쐼�[�̈ܓx�A�o�x�����Z�����]������߂�
	const double dLatRest1 = dLat - (static_cast<double>(iCode12) / 1.5);
	const double dLonRest1 = dLon - (static_cast<double>(iCode34) + 100.0);

	// 2�����b�V���̈ܓx�o�x�������Ƃ̍��ݕ�
	const double dLatUnit1 = (5.0 / 60.0);
	const double dLonUnit1 = (7.0 / 60.0) + (30.0 / 60 / 60);

	const int iCode5 = static_cast<int>(dLatRest1 / dLatUnit1);
	const int iCode6 = static_cast<int>(dLonRest1 / dLonUnit1);
	CString strMeshCode56;
	strMeshCode56.Format(_T("%d%d"), iCode5, iCode6);

	// -----------------------------------------------------------------------
	// ��3�����b�V���i�������̂͊�n�惁�b�V���Ȃ�����3���n����j
	// �E2�����b�V�����c�A���Ƃ���10���������l�p�`(2�����b�V����100����)
	// �E1�ӂ̒����͖�1km�ŁA�ܓx30�b(30 / 60 / 60)�A�o�x45�b(45 / 60 / 60)�ƂȂ�܂��B
	// �E2�����b�V���̐���[����_(0, 0)�Ƃ��A��1�����k�����ւ̃��b�V���ʒu�A��1�����������ւ̃��b�V���ʒu��\���܂��B
	// �E1�����b�V���A2�����b�V���Ƒg�ݍ��킹��nnnn-nn-nn�̂悤�ɋL�q���܂��B
	// -----------------------------------------------------------------------
	// 2�����b�V���̓쐼�[�̈ܓx�A�o�x�����Z�����]������߂�
	const double dLatRest2 = dLatRest1 - (static_cast<double>(iCode5) * dLatUnit1);
	const double dLonRest2 = dLonRest1 - (static_cast<double>(iCode6) * dLonUnit1);

	// 3�����b�V���̈ܓx�o�x�������Ƃ̍��ݕ��i2�����b�V���̍��݂�1/10�j
	const double dLatUnit2 = dLatUnit1 / 10.0;
	const double dLonUnit2 = dLonUnit1 / 10.0;

	const int iCode7 = static_cast<int>(dLatRest2 / dLatUnit2);
	const int iCode8 = static_cast<int>(dLonRest2 / dLonUnit2);
	CString strMeshCode78;
	strMeshCode78.Format(_T("%d%d"), iCode7, iCode8);

	// -----------------------------------------------------------------------
	// ��4�����b�V��
	// -----------------------------------------------------------------------
	CString strMeshCode9A;
	if (bIsDokujiMesh)
	{
		// -----------------------------------------------------------------------
		// ���Ǝ�4�����b�V���i������ɍl���܂����j
		// �E3�����b�V�����c�A���Ƃ���10���������l�p�`(3�����b�V����100����)
		// �E1�ӂ̒����͖�100m�ƂȂ�܂��B
		// �E3�����b�V���̐���[����_(0, 0)�Ƃ��A��1�����k�����ւ̃��b�V���ʒu�A��1�����������ւ̃��b�V���ʒu��\���܂��B
		// �E1�����b�V���A2�����b�V���A3�����b�V���Ƒg�ݍ��킹��nnnn-nn-nn-nn�̂悤�ɋL�q���܂��B
		// -----------------------------------------------------------------------
		// 3�����b�V���̓쐼�[�̈ܓx�A�o�x�����Z�����]������߂�
		const double dLatRest3 = dLatRest2 - (static_cast<double>(iCode7) * dLatUnit2);
		const double dLonRest3 = dLonRest2 - (static_cast<double>(iCode8) * dLonUnit2);

		// 3�����b�V���̈ܓx�o�x�������Ƃ̍��ݕ��i3�����b�V���̍��݂�1/10�j
		const double dLatUnit3 = dLatUnit2 / 10.0;
		const double dLonUnit3 = dLonUnit2 / 10.0;

		const int iCode9 = static_cast<int>(dLatRest3 / dLatUnit3);
		const int iCodeA = static_cast<int>(dLonRest3 / dLonUnit3);

		strMeshCode9A.Format(_T("%d%d"), iCode9, iCodeA);
	}
	else
	{
		// -----------------------------------------------------------------------
		// ����4�����b�V���i1/2�n�惁�b�V���j
		// �E3�����b�V�����c�A���Ƃ���2���������l�p�`(3�����b�V����4����)
		// �E1�ӂ̒����͖�500m�ƂȂ�܂��B
		// �E1�����b�V���A2�����b�V���A3�����b�V���Ƒg�ݍ��킹��nnnn-nn-nn-n�̂悤�ɋL�q���܂��B
		// �E�Q�l1�Fhttp://www.sinfonica.or.jp/mesh/mimginfo.html
		// �E�Q�l2�Fhttp://www.opengis.co.jp/htm/basic/mesh_polygon.htm
		// -----------------------------------------------------------------------
		// 3�����b�V���̓쐼�[�̈ܓx�A�o�x�����Z�����]������߂�
		const double dLatRest3 = dLatRest2 - (static_cast<double>(iCode7) * dLatUnit2);
		const double dLonRest3 = dLonRest2 - (static_cast<double>(iCode8) * dLonUnit2);

		// 3�����b�V���̈ܓx�o�x�������Ƃ̍��ݕ��i3�����b�V���̍��݂�1/2�j
		const double dLatUnit3 = dLatUnit2 / 2.0;
		const double dLonUnit3 = dLonUnit2 / 2.0;

		const int iCodeLat = static_cast<int>(dLatRest3 / dLatUnit3);
		const int iCodeLon = static_cast<int>(dLonRest3 / dLonUnit3);

		int iCode;
		if      ((iCodeLat == 0) && (iCodeLon == 0)) iCode = 1;
		else if ((iCodeLat == 0) && (iCodeLon == 1)) iCode = 2;
		else if ((iCodeLat == 1) && (iCodeLon == 0)) iCode = 3;
		else if ((iCodeLat == 1) && (iCodeLon == 1)) iCode = 4;

		strMeshCode9A.Format(_T("%d"), iCode);
	}

	return strMeshCode1234 + _T("-") +  strMeshCode56 + _T("-") + strMeshCode78 + _T("-") + strMeshCode9A;
}

// �ܓx�E�o�x���擾����
void CJpnAreaMeshDlg::OnBnClickedBtnGetLatLon()
{
	// ���b�V���R�[�h
	CString strMeshCode;
	this->m_edtMeshCode.GetWindowText(strMeshCode);

	double dLat = 0.0;
	double dLon = 0.0;

	// �ܓx�E�o�x�擾
	this->GetLatLonFromMeshCode(strMeshCode, dLat, dLon);

	// �ܓx�E�o�x�\��
	CString strResultMsg;
	strResultMsg.Format(_T("(Lat, Lon) : (%f, %f)"), dLat, dLon);
	MessageBox(strResultMsg);
}

/**
* ���b�V���R�[�h����ܓx�o�x���擾����.
* @param strMeshCode ���b�V���R�[�h
* @param dLat �ܓx
* @param dLon �o�x
* @return true:���� false:���s
*/
bool CJpnAreaMeshDlg::GetLatLonFromMeshCode(
	const CString strMeshCode,
	double& dLat,
	double& dLon
)
{
	// 2�����b�V���̈ܓx�o�x�������Ƃ̍��ݕ�
	const double dLatUnit2 = (5.0 / 60.0);
	const double dLonUnit2 = (7.0 / 60.0) + (30.0 / 60.0 / 60.0);
	// 3�����b�V���̈ܓx�o�x�������Ƃ̍��ݕ�
	const double dLatUnit3 = dLatUnit2 / 10.0;
	const double dLonUnit3 = dLonUnit2 / 10.0;
	// 4�����b�V���̈ܓx�o�x�������Ƃ̍��ݕ�
	const double dLatUnit4 = dLatUnit3 / 10.0;
	const double dLonUnit4 = dLonUnit3 / 10.0;

	// ������
	dLat = 0.0;
	dLon = 0.0;

	// �G���A�R�[�h����
	CStringArray aryMeshCode;
	this->SplitString(strMeshCode, _T("-"), aryMeshCode);
	const INT_PTR iCount = aryMeshCode.GetCount();
	if (iCount >= 1)
	{
		// 1�����b�V��
		const CString strCode1234 = aryMeshCode.GetAt(0);
		const CString strCode12 = strCode1234.Left(2);
		const CString strCode34 = strCode1234.Right(2);
		// �ܓx
		dLat = ::_ttof(strCode12) / 1.5;
		// �o�x
		dLon = ::_ttof(strCode34) + 100.0;
	}
	if (iCount >= 2)
	{
		// 2�����b�V��
		const CString strCode56 = aryMeshCode.GetAt(1);
		const CString strCode5 = strCode56.Left(1);
		const CString strCode6 = strCode56.Right(1);
		// �ܓx
		dLat += ::_ttof(strCode5) * dLatUnit2;
		// �o�x
		dLon += ::_ttof(strCode6) * dLonUnit2;
	}
	if (iCount >= 3)
	{
		// 3�����b�V��
		const CString strCode78 = aryMeshCode.GetAt(2);
		const CString strCode7 = strCode78.Left(1);
		const CString strCode8 = strCode78.Right(1);
		// �ܓx
		dLat += ::_ttof(strCode7) * dLatUnit3;
		// �o�x
		dLon += ::_ttof(strCode8) * dLonUnit3;
	}
	if (iCount >= 4)
	{
		// 4�����b�V��
		const CString strCode9A = aryMeshCode.GetAt(3);
		const CString strCode9 = strCode9A.Left(1);
		const CString strCodeA = strCode9A.Right(1);
		// �ܓx
		dLat += ::_ttof(strCode9) * dLatUnit4;
		// �o�x
		dLon += ::_ttof(strCodeA) * dLonUnit4;
	}

	return true;
}

// �Z�p���[�^�ŕ�����𕪊�����
void CJpnAreaMeshDlg::SplitString(
	const CString& strTgt,
	const CString& strSep,
	CStringArray& aryString
)
{
	if (strTgt.IsEmpty()) return;

	int intNow = strTgt.Find(strSep, 0);
	if (intNow < 0)
	{
		aryString.Add(strTgt);
		return;
	}

	int intPrev = 0;
	while (true)
	{
		aryString.Add(strTgt.Mid(intPrev, intNow - intPrev));

		intPrev = intNow + 1;
		intNow = strTgt.Find(strSep, intPrev);

		if (intNow < 0)
		{
			aryString.Add(strTgt.Mid(intPrev));
			break;
		}
	}
}
