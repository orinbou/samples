
// OmpSampleDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "OmpSample.h"
#include "OmpSampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// COmpSampleDlg ダイアログ




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


// COmpSampleDlg メッセージ ハンドラー

BOOL COmpSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void COmpSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR COmpSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////

// OpenMPの一部関数を使用するために宣言
#include "omp.h"

/////////////////////////////////
// OMPサンプルを呼び出します①
/////////////////////////////////
void COmpSampleDlg::OnBnClickedOmpGo1()
{
	// 最大同時スレッド数を設定する
	int iOldThreadNum = omp_get_max_threads();
	int iUseThreadNum = iOldThreadNum - 1;	// 許容最大スレッド数(-1)を取得
	::omp_set_num_threads(iUseThreadNum);	// 並列スレッド数を設定

	// OpenMPのON/OFFを判定する
	#ifdef _OPENMP
		const bool bIsOmpEnable = true;
	#else
		const bool bIsOmpEnable = false;
	#endif

	// 実行前確認
	CString strMsg;
	strMsg.Format(
		_T("実行パラメータ\nOpenMP = %s\n使用可能なスレッド数 = %d\n使用する並列スレッド数 = %d"),
		(bIsOmpEnable ? _T("ON") : _T("OFF")),
		iOldThreadNum,
		iUseThreadNum
	);
	MessageBox(strMsg);

	// 時刻計測（開始）
	clock_t sTime = clock();

	// タイル毎に処理
	const INT_PTR iLoopCount = 3;
	CStringArray strLogMsgs;
	bool bRet = true;
	int iCountThreads = 0;
	#pragma omp parallel for schedule(dynamic, 1)
	for (INT_PTR i = 0; i < iLoopCount; i++)
	{
		if (!bRet) continue;

		// 別プロセスを起動する
		if (COmpSampleDlg::executeProcess(_T("notepad.exe"), _T("")))
		{
			// 成功
			#pragma omp critical
			{
				strLogMsgs.Add(_T("OK!"));
			}
		}
		else
		{
			// 失敗
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
			// ログ出力
			CString strLogMsg;
			strLogMsg.Format(_T("STEP : (%d / %d)[ThreadID : %d]\n"), iCountThreads, iLoopCount, omp_get_thread_num());
			TRACE(strLogMsg);
		}
	}
	// ここでOpenMP終了待ち

	// 時刻計測（終了）
	clock_t eTime = clock();

	// 最大同時スレッド数を元に戻す
	::omp_set_num_threads(iOldThreadNum);

	// 結果発表
	CString str;
	for (INT_PTR i = 0; i < strLogMsgs.GetCount(); i++)
	{
		str += strLogMsgs.GetAt(i) + _T("\n");
	}
	strMsg.Format(_T("%f[秒]\n%s"), ((double)(eTime - sTime) / CLOCKS_PER_SEC), str);
	MessageBox(_T("結果 = ") + strMsg);
}

/////////////////////////////////
// OMPサンプルを呼び出します②
/////////////////////////////////
void COmpSampleDlg::OnBnClickedOmpGo2()
{
	// 最大同時スレッド数を設定する
	int iOldThreadNum = omp_get_max_threads();
	int iUseThreadNum = iOldThreadNum - 1;	// 許容最大スレッド数(-1)を取得
	::omp_set_num_threads(iUseThreadNum); 	// 並列スレッド数を設定

	// OpenMPのON/OFFを判定する
	#ifdef _OPENMP
		const bool bIsOmpEnable = true;
	#else
		const bool bIsOmpEnable = false;
	#endif

	// 実行前確認
	CString strMsg;
	strMsg.Format(
		_T("実行パラメータ\nOpenMP = %s\n使用可能なスレッド数 = %d\n使用する並列スレッド数 = %d"),
		(bIsOmpEnable ? _T("ON") : _T("OFF")),
		iOldThreadNum,
		iUseThreadNum
	);
	MessageBox(strMsg);

	// 時刻計測（開始）
	clock_t sTime = clock();

	// タイル毎に処理
	const INT_PTR iLoopCount = 10;
	CStringArray strLogMsgs;
	bool bRet = true;
	int iCountThreads = 0;
	#pragma omp parallel for schedule(dynamic, 1)
	for (INT_PTR i = 0; i < iLoopCount; i++)
	{
		if (!bRet) continue;

		// テキトーな重い処理
		TRACE(_T("index[%d]\n"), i);
		Sleep(3000);	// 仮想重い処理（※3秒待機）
		if (true)
		{
			// 成功
			#pragma omp critical
			{
				strLogMsgs.Add(_T("OK!"));
			}
		}
		else
		{
			// 失敗
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
			// ログ出力
			CString strLogMsg;
			strLogMsg.Format(_T("STEP : (%d / %d)[ThreadID : %d]\n"), iCountThreads, iLoopCount, omp_get_thread_num());
			TRACE(strLogMsg);
		}
	}
	// ここでOpenMP終了待ち

	// 時刻計測（終了）
	clock_t eTime = clock();

	// 最大同時スレッド数を元に戻す
	::omp_set_num_threads(iOldThreadNum);

	// 結果発表
	CString str;
	for (INT_PTR i = 0; i < strLogMsgs.GetCount(); i++)
	{
		str += strLogMsgs.GetAt(i) + _T("\n");
	}
	strMsg.Format(_T("%f[秒]\n%s"), ((double)(eTime - sTime) / CLOCKS_PER_SEC), str);
	MessageBox(_T("結果 = ") + strMsg);
}


// 外部アプリケーション起動
bool COmpSampleDlg::executeProcess(
	const CString&	strAppPath,	//!< in		実行対象APPパス
	const CString&	strParam	//!< in		パラメータ
)
{
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;

	::ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
//	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
//	startupInfo.wShowWindow = SW_HIDE; // これで、非表示

	CString strCommand;
	strCommand.Format(_T("%s %s"), strAppPath, strParam);

	// 実行
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

	// プロセス終了を待機する
	::WaitForSingleObject(processInfo.hProcess, INFINITE);

	// ExitCodeを取得して結果を判断すること
	DWORD dwExitCode = 0;
	::GetExitCodeProcess(processInfo.hProcess, &dwExitCode);

	::CloseHandle(processInfo.hProcess);

	// EXEの戻り値が 0 以外は異常と判断する
	if (dwExitCode != 0) return false;

	return true;
}
