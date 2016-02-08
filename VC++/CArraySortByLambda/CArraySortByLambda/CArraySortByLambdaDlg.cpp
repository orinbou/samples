
// CArraySortByLambdaDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "CArraySortByLambda.h"
#include "CArraySortByLambdaDlg.h"
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


// CCArraySortByLambdaDlg �_�C�A���O




CCArraySortByLambdaDlg::CCArraySortByLambdaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCArraySortByLambdaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCArraySortByLambdaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCArraySortByLambdaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCArraySortByLambdaDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCArraySortByLambdaDlg ���b�Z�[�W �n���h���[

BOOL CCArraySortByLambdaDlg::OnInitDialog()
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

void CCArraySortByLambdaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCArraySortByLambdaDlg::OnPaint()
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
HCURSOR CCArraySortByLambdaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <algorithm>

///////////////////////////////
// �Ă��Ɓ[�ȍ\����
///////////////////////////////
struct MyStructure
{
	INT_PTR	m_iAge;		//!< �N��
	CString	m_strName;	//!< ����
	bool	m_bIsMan;	//!< �j�H
	double	m_dHeight;	//!< �g��
};

//////////////////////////////////////////////
// �����_����CArray��Sort���������Ă݂�
//////////////////////////////////////////////
void CCArraySortByLambdaDlg::OnBnClickedButton1()
{
	// �ݔ��䒠�`�F�b�N
	const CString strFormat(_T("Yamada %drou"));
	CArray<MyStructure> structures;
	for (INT_PTR i = 10; i > 0; i--)
	{
		MyStructure structure;
		structure.m_iAge	= i;
		structure.m_strName.Format(strFormat, i);
		structure.m_bIsMan	= (i % 2) ? true : false;
		structure.m_dHeight	= static_cast<double>(i) * 0.5;
		structures.Add(structure);
	}
	const INT_PTR iCount = structures.GetCount();

	// �\�[�g�O
	TRACE(_T("=====================\n"));
	TRACE(_T("=>> Gekiteki Before! \n"));
	TRACE(_T("=====================\n"));
	for (INT_PTR i = 0; i < iCount; i++)
	{
		const MyStructure* pStructure = &structures.GetAt(i);
		TRACE(
			_T("structure[%d] (m_iAge, m_strName, m_bIsMan, m_dHeight) = (%d, %s, %d, %.02f)\n"),
			i,
			pStructure->m_iAge,
			pStructure->m_strName,
			pStructure->m_bIsMan,
			pStructure->m_dHeight
		);
	}

	// �����_���ŏ����\�[�g���Ă݂�
	MyStructure* pStart = &structures.GetAt(0);
	std::sort(
		pStart, (pStart + iCount),
		[](const MyStructure& pA, const MyStructure& pB)->bool
		{
			return (pA.m_iAge < pB.m_iAge) ? true : false;
		}
	);

	// �\�[�g��
	TRACE(_T("=====================\n"));
	TRACE(_T("=>> Gekiteki Afer!   \n"));
	TRACE(_T("=====================\n"));
	for (INT_PTR i = 0; i < iCount; i++)
	{
		const MyStructure* pStructure = &structures.GetAt(i);
		TRACE(
			_T("structure[%d] (m_iAge, m_strName, m_bIsMan, m_dHeight) = (%d, %s, %d, %.02f)\n"),
			i,
			pStructure->m_iAge,
			pStructure->m_strName,
			pStructure->m_bIsMan,
			pStructure->m_dHeight
		);
	}

	// ���b�Z�[�W�ʒm
	MessageBox(_T("����(^^)"), _T("���"), (MB_OK | MB_ICONINFORMATION));
}
