
// CArraySortByLambdaDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CArraySortByLambda.h"
#include "CArraySortByLambdaDlg.h"
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


// CCArraySortByLambdaDlg ダイアログ




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


// CCArraySortByLambdaDlg メッセージ ハンドラー

BOOL CCArraySortByLambdaDlg::OnInitDialog()
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CCArraySortByLambdaDlg::OnPaint()
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
HCURSOR CCArraySortByLambdaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <algorithm>

///////////////////////////////
// てきとーな構造体
///////////////////////////////
struct MyStructure
{
	INT_PTR	m_iAge;		//!< 年齢
	CString	m_strName;	//!< 名称
	bool	m_bIsMan;	//!< 男？
	double	m_dHeight;	//!< 身長
};

//////////////////////////////////////////////
// ラムダ式でCArrayのSortを実現してみる
//////////////////////////////////////////////
void CCArraySortByLambdaDlg::OnBnClickedButton1()
{
	// 設備台帳チェック
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

	// ソート前
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

	// ラムダ式で昇順ソートしてみる
	MyStructure* pStart = &structures.GetAt(0);
	std::sort(
		pStart, (pStart + iCount),
		[](const MyStructure& pA, const MyStructure& pB)->bool
		{
			return (pA.m_iAge < pB.m_iAge) ? true : false;
		}
	);

	// ソート後
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

	// メッセージ通知
	MessageBox(_T("成功(^^)"), _T("情報"), (MB_OK | MB_ICONINFORMATION));
}
