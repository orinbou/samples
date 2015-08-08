
// JpnAreaMeshDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "JpnAreaMesh.h"
#include "JpnAreaMeshDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJpnAreaMeshDlg ダイアログ



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


// CJpnAreaMeshDlg メッセージ ハンドラー

BOOL CJpnAreaMeshDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	this->m_edtLat.SetWindowText(_T("35.5"));
	this->m_edtLon.SetWindowText(_T("141.5"));

	// 活性制御
	this->UpdateControls();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// 活性制御
void CJpnAreaMeshDlg::UpdateControls()
{
	// 緯度
	CString strLat;
	this->m_edtLat.GetWindowText(strLat);

	// 経度
	CString strLon;
	this->m_edtLon.GetWindowText(strLon);

	// 実行ボタン
	this->m_btnExecute.EnableWindow((!strLat.IsEmpty() && !strLon.IsEmpty()) ? TRUE : FALSE);
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CJpnAreaMeshDlg::OnPaint()
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
HCURSOR CJpnAreaMeshDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// エリアコードを取得する
void CJpnAreaMeshDlg::OnBnClickedBtnExecute()
{
	// 緯度
	CString strLat;
	this->m_edtLat.GetWindowText(strLat);
	const double dLat = _ttof(strLat);

	// 経度
	CString strLon;
	this->m_edtLon.GetWindowText(strLon);
	const double dLon = _ttof(strLon);

	// メッシュコード取得
	const CString strMeshCode = this->GetMeshCode(dLat, dLon);
	TRACE(strMeshCode + _T("\n"));

	// メッシュコード表示
	CString strResultMsg;
	strResultMsg.Format(_T("メッシュコード : %s"), strMeshCode);
	MessageBox(strResultMsg);
}

// 緯度経度からメッシュコードを取得する
CString CJpnAreaMeshDlg::GetMeshCode(
	const double dLat,
	const double dLon
)
{
	// 1次メッシュ
	const int iCode12 = static_cast<int>(dLat * 1.5);
	const int iCode34 = static_cast<int>(dLon - 100);
	CString strMeshCode1234;
	strMeshCode1234.Format(_T("%d%d"), iCode12, iCode34);

	return strMeshCode1234;
}
