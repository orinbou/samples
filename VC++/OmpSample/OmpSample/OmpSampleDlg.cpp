
// OmpSampleDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "OmpSample.h"
#include "OmpSampleDlg.h"
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


// COmpSampleDlg �_�C�A���O




COmpSampleDlg::COmpSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COmpSampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COmpSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COmpSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OMP_GO1, &COmpSampleDlg::OnBnClickedOmpGo1)
	ON_BN_CLICKED(IDC_OMP_GO2, &COmpSampleDlg::OnBnClickedOmpGo2)
END_MESSAGE_MAP()


// COmpSampleDlg ���b�Z�[�W �n���h���[

BOOL COmpSampleDlg::OnInitDialog()
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

void COmpSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COmpSampleDlg::OnPaint()
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
HCURSOR COmpSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////

// OpenMP�̈ꕔ�֐����g�p���邽�߂ɐ錾
#include "omp.h"

/////////////////////////////////
// OMP�T���v�����Ăяo���܂��@
/////////////////////////////////
void COmpSampleDlg::OnBnClickedOmpGo1()
{
	// �ő哯���X���b�h����ݒ肷��
	int iOldThreadNum = omp_get_max_threads();
	int iUseThreadNum = iOldThreadNum - 1;	// ���e�ő�X���b�h��(-1)���擾
	::omp_set_num_threads(iUseThreadNum);	// ����X���b�h����ݒ�

	// OpenMP��ON/OFF�𔻒肷��
	#ifdef _OPENMP
		const bool bIsOmpEnable = true;
	#else
		const bool bIsOmpEnable = false;
	#endif

	// ���s�O�m�F
	CString strMsg;
	strMsg.Format(
		_T("���s�p�����[�^\nOpenMP = %s\n�g�p�\�ȃX���b�h�� = %d\n�g�p�������X���b�h�� = %d"),
		(bIsOmpEnable ? _T("ON") : _T("OFF")),
		iOldThreadNum,
		iUseThreadNum
	);
	MessageBox(strMsg);

	// �����v���i�J�n�j
	clock_t sTime = clock();

	// �^�C�����ɏ���
	const INT_PTR iLoopCount = 3;
	CStringArray strLogMsgs;
	bool bRet = true;
	int iCountThreads = 0;
	#pragma omp parallel for schedule(dynamic, 1)
	for (INT_PTR i = 0; i < iLoopCount; i++)
	{
		if (!bRet) continue;

		// �ʃv���Z�X���N������
		if (COmpSampleDlg::executeProcess(_T("notepad.exe"), _T("")))
		{
			// ����
			#pragma omp critical
			{
				strLogMsgs.Add(_T("OK!"));
			}
		}
		else
		{
			// ���s
			bRet = false;
			#pragma omp critical
			{
				strLogMsgs.Add(_T("NG!"));
			}
		}

		#pragma omp atomic
			iCountThreads++;

		#pragma omp critical
		{
			// ���O�o��
			CString strLogMsg;
			strLogMsg.Format(_T("STEP : (%d / %d)[ThreadID : %d]\n"), iCountThreads, iLoopCount, omp_get_thread_num());
			TRACE(strLogMsg);
		}
	}
	// ������OpenMP�I���҂�

	// �����v���i�I���j
	clock_t eTime = clock();

	// �ő哯���X���b�h�������ɖ߂�
	::omp_set_num_threads(iOldThreadNum);

	// ���ʔ��\
	CString str;
	for (INT_PTR i = 0; i < strLogMsgs.GetCount(); i++)
	{
		str += strLogMsgs.GetAt(i) + _T("\n");
	}
	strMsg.Format(_T("%f[�b]\n%s"), ((double)(eTime - sTime) / CLOCKS_PER_SEC), str);
	MessageBox(_T("���� = ") + strMsg);
}

/////////////////////////////////
// OMP�T���v�����Ăяo���܂��A
/////////////////////////////////
void COmpSampleDlg::OnBnClickedOmpGo2()
{
	// �ő哯���X���b�h����ݒ肷��
	int iOldThreadNum = omp_get_max_threads();
	int iUseThreadNum = iOldThreadNum - 1;	// ���e�ő�X���b�h��(-1)���擾
	::omp_set_num_threads(iUseThreadNum); 	// ����X���b�h����ݒ�

	// OpenMP��ON/OFF�𔻒肷��
	#ifdef _OPENMP
		const bool bIsOmpEnable = true;
	#else
		const bool bIsOmpEnable = false;
	#endif

	// ���s�O�m�F
	CString strMsg;
	strMsg.Format(
		_T("���s�p�����[�^\nOpenMP = %s\n�g�p�\�ȃX���b�h�� = %d\n�g�p�������X���b�h�� = %d"),
		(bIsOmpEnable ? _T("ON") : _T("OFF")),
		iOldThreadNum,
		iUseThreadNum
	);
	MessageBox(strMsg);

	// �����v���i�J�n�j
	clock_t sTime = clock();

	// �^�C�����ɏ���
	const INT_PTR iLoopCount = 10;
	CStringArray strLogMsgs;
	bool bRet = true;
	int iCountThreads = 0;
	#pragma omp parallel for schedule(dynamic, 1)
	for (INT_PTR i = 0; i < iLoopCount; i++)
	{
		if (!bRet) continue;

		// �e�L�g�[�ȏd������
		TRACE(_T("index[%d]\n"), i);
		Sleep(3000);	// ���z�d�������i��3�b�ҋ@�j
		if (true)
		{
			// ����
			#pragma omp critical
			{
				strLogMsgs.Add(_T("OK!"));
			}
		}
		else
		{
			// ���s
			bRet = false;
			#pragma omp critical
			{
				strLogMsgs.Add(_T("NG!"));
			}
		}

		#pragma omp atomic
			iCountThreads++;

		#pragma omp critical
		{
			// ���O�o��
			CString strLogMsg;
			strLogMsg.Format(_T("STEP : (%d / %d)[ThreadID : %d]\n"), iCountThreads, iLoopCount, omp_get_thread_num());
			TRACE(strLogMsg);
		}
	}
	// ������OpenMP�I���҂�

	// �����v���i�I���j
	clock_t eTime = clock();

	// �ő哯���X���b�h�������ɖ߂�
	::omp_set_num_threads(iOldThreadNum);

	// ���ʔ��\
	CString str;
	for (INT_PTR i = 0; i < strLogMsgs.GetCount(); i++)
	{
		str += strLogMsgs.GetAt(i) + _T("\n");
	}
	strMsg.Format(_T("%f[�b]\n%s"), ((double)(eTime - sTime) / CLOCKS_PER_SEC), str);
	MessageBox(_T("���� = ") + strMsg);
}


// �O���A�v���P�[�V�����N��
bool COmpSampleDlg::executeProcess(
	const CString&	strAppPath,	//!< in		���s�Ώ�APP�p�X
	const CString&	strParam	//!< in		�p�����[�^
)
{
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;

	::ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
//	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
//	startupInfo.wShowWindow = SW_HIDE; // ����ŁA��\��

	CString strCommand;
	strCommand.Format(_T("%s %s"), strAppPath, strParam);

	// ���s
	if (
		!::CreateProcess(
			NULL,
			(LPTSTR)(LPCTSTR)strCommand,
			NULL,
			NULL,
			FALSE,
			NORMAL_PRIORITY_CLASS,
			NULL,
			NULL,
			&startupInfo,
			&processInfo
		)
	)
	{
		return false;
	}

	::CloseHandle(processInfo.hThread);

	// �v���Z�X�I����ҋ@����
	::WaitForSingleObject(processInfo.hProcess, INFINITE);

	// ExitCode���擾���Č��ʂ𔻒f���邱��
	DWORD dwExitCode = 0;
	::GetExitCodeProcess(processInfo.hProcess, &dwExitCode);

	::CloseHandle(processInfo.hProcess);

	// EXE�̖߂�l�� 0 �ȊO�ُ͈�Ɣ��f����
	if (dwExitCode != 0) return false;

	return true;
}
