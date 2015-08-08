
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
	DDX_Control(pDX, IDC_BTN_EXECUTE, m_btnExecute);
}

BEGIN_MESSAGE_MAP(CJpnAreaMeshDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDT_LAT, &CJpnAreaMeshDlg::UpdateControls)
	ON_EN_CHANGE(IDC_EDT_LON, &CJpnAreaMeshDlg::UpdateControls)
	ON_BN_CLICKED(IDC_BTN_EXECUTE, &CJpnAreaMeshDlg::OnBnClickedBtnExecute)
END_MESSAGE_MAP()


// CJpnAreaMeshDlg ���b�Z�[�W �n���h���[

BOOL CJpnAreaMeshDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	this->m_edtLat.SetWindowText(_T("35.5"));
	this->m_edtLon.SetWindowText(_T("141.5"));

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

	// ���s�{�^��
	this->m_btnExecute.EnableWindow((!strLat.IsEmpty() && !strLon.IsEmpty()) ? TRUE : FALSE);
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
void CJpnAreaMeshDlg::OnBnClickedBtnExecute()
{
	// �ܓx
	CString strLat;
	this->m_edtLat.GetWindowText(strLat);
	const double dLat = _ttof(strLat);

	// �o�x
	CString strLon;
	this->m_edtLon.GetWindowText(strLon);
	const double dLon = _ttof(strLon);

	// ���b�V���R�[�h�擾
	const CString strMeshCode = this->GetMeshCode(dLat, dLon);
	TRACE(strMeshCode + _T("\n"));

	// ���b�V���R�[�h�\��
	CString strResultMsg;
	strResultMsg.Format(_T("���b�V���R�[�h : %s"), strMeshCode);
	MessageBox(strResultMsg);
}

// �ܓx�o�x���烁�b�V���R�[�h���擾����
CString CJpnAreaMeshDlg::GetMeshCode(
	const double dLat,
	const double dLon
)
{
	// 1�����b�V��
	const int iCode12 = static_cast<int>(dLat * 1.5);
	const int iCode34 = static_cast<int>(dLon - 100);
	CString strMeshCode1234;
	strMeshCode1234.Format(_T("%d%d"), iCode12, iCode34);

	return strMeshCode1234;
}
