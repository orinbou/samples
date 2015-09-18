
// ClassInheritABTestDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ClassInheritABTest.h"
#include "ClassInheritABTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClassInheritABTestDlg �_�C�A���O




CClassInheritABTestDlg::CClassInheritABTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClassInheritABTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClassInheritABTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClassInheritABTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClassInheritABTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CClassInheritABTestDlg ���b�Z�[�W �n���h���[

BOOL CClassInheritABTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CClassInheritABTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CClassInheritABTestDlg::OnPaint()
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
HCURSOR CClassInheritABTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "A.h"
#include "B.h"

// hoge�e�X�g
void CClassInheritABTestDlg::OnBnClickedButton1()
{
	// �������m��
	A* a = new A;
	B* b = new B;

	////////////////////////////////////
	// �댯
	////////////////////////////////////
//	A* c = ( A* )b;						// C����̃L���X�g�͎��s���ɗ�����
//	��(Try)
//	A* c = static_cast<A*>( b );		// �r���h�G���[�ň������������i�����������Ӗ��ł͈��S���H�j
//	��(Try)
//	A* c = reinterpret_cast<A*>( b );	// static_cast�r���h�G���[�Łureinterpret_cast�AC �X�^�C�� �L���X�g�܂��͊֐��X�^�C���̃L���X�g���K�v�ł��B�v�ƌ���ꂽ�̂ŎE���Ă݂�����C����̃L���X�g�Ɠ��l�Ɏ��s���ɗ�����
	////////////////////////////////////

	////////////////////////////////////
	// ���S�i���A���vNULL�`�F�b�N�j
	// ���I�X�X���͂��܂��񂪁A�ǂ����Ă����ꍇ�́A���L�̕��@����������
	////////////////////////////////////
	A* c = dynamic_cast<A*>( b );		// ���Ȃ݂ɃN���XA�AB��Base�N���X�̌h�̂��O���ƃr���h�G���[�u�|�����[�t�B�b�N�Ȍ^�ł͂���܂���B�v�ɂȂ�
	ASSERT( c != NULL );
	////////////////////////////////////

	// ����
	a->hogeA();
	b->hogeB();
	c->hogeA();	// ���R�R�ŃA�N�Z�X�ᔽ�ɂȂ�Bdynamic_cast��NULL�`�F�b�N�Ŗh����

	// ���
	delete a;
	delete b;
}
