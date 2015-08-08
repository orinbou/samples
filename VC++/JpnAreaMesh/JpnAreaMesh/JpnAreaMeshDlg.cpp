
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

	// 初期値（新宿区新宿2-1-1 エルデ）
	this->m_edtLat.SetWindowText(_T("35.68823693"));
	this->m_edtLon.SetWindowText(_T("139.70974445"));

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

/**
* 緯度経度からメッシュコードを取得する.
* @see http://d.hatena.ne.jp/letitride/20111215
* @param dLat 緯度
* @param dLon 経度
* @return メッシュコード文字列
*/
CString CJpnAreaMeshDlg::GetMeshCode(
	const double dLat,
	const double dLon
)
{
	// -----------------------------------------------------------------------
	// ★1次メッシュ（正式名称は第1次地域区画）
	// ・1辺の長さが約80kmの四角形となります。
	// ・4桁の数字で構成され、枠の西南端の緯度を上2桁、経度を下2桁で表します。
	// ・緯度を1.5倍した値の上2桁 + 経度から100引いた値となります。
	// -----------------------------------------------------------------------
	const int iCode12 = static_cast<int>(dLat * 1.5);
	const int iCode34 = static_cast<int>(dLon - 100.0);
	CString strMeshCode1234;
	strMeshCode1234.Format(_T("%02d%02d"), iCode12, iCode34);

	// -----------------------------------------------------------------------
	// ★2次メッシュ（正式名称は第2次地域区画）
	// ・1次メッシュを縦、横ともに8等分した四角形(1次メッシュを64分割)
	// ・1辺の長さは約4kmで、緯度5分(5 / 60)、経度7分30秒(7 / 60 + 30 / 60 / 60)となります。
	// ・1次メッシュの西南端を基点(0, 0)とし、上1桁が北方向へのメッシュ位置、下1桁が東方向へのメッシュ位置を表します。
	// ・1次メッシュと組み合わせてnnnn-nnと記述します。
	// -----------------------------------------------------------------------
	// 1次メッシュの南西端の緯度、経度を除算した余りを求める
	const double dLatRest1 = dLat - (static_cast<double>(iCode12) / 1.5);
	const double dLonRest1 = dLon - (static_cast<double>(iCode34) + 100.0);

	// 2次メッシュの緯度経度方向ごとの刻み幅
	const double dLatUnit1 = (5.0 / 60.0);
	const double dLonUnit1 = (7.0 / 60.0) + (30.0 / 60 / 60);

	const int iCode5 = static_cast<int>(dLatRest1 / dLatUnit1);
	const int iCode6 = static_cast<int>(dLonRest1 / dLonUnit1);
	CString strMeshCode56;
	strMeshCode56.Format(_T("%d%d"), iCode5, iCode6);

	// -----------------------------------------------------------------------
	// ★3次メッシュ（正式名称は基準地域メッシュないし第3次地域区画）
	// ・2次メッシュを縦、横ともに10等分した四角形(2次メッシュを100分割)
	// ・1辺の長さは約1kmで、緯度30秒(30 / 60 / 60)、経度45秒(45 / 60 / 60)となります。
	// ・2次メッシュの西南端を基点(0, 0)とし、上1桁が北方向へのメッシュ位置、下1桁が東方向へのメッシュ位置を表します。
	// ・1次メッシュ、2次メッシュと組み合わせてnnnn-nn-nnのように記述します。
	// -----------------------------------------------------------------------
	// 2次メッシュの南西端の緯度、経度を除算した余りを求める
	const double dLatRest2 = dLatRest1 - (static_cast<double>(iCode5) * dLatUnit1);
	const double dLonRest2 = dLonRest1 - (static_cast<double>(iCode6) * dLonUnit1);

	// 3次メッシュの緯度経度方向ごとの刻み幅（2次メッシュの刻みの1/10）
	const double dLatUnit2 = dLatUnit1 / 10.0;
	const double dLonUnit2 = dLonUnit1 / 10.0;

	const int iCode7 = static_cast<int>(dLatRest2 / dLatUnit2);
	const int iCode8 = static_cast<int>(dLonRest2 / dLonUnit2);
	CString strMeshCode78;
	strMeshCode78.Format(_T("%d%d"), iCode7, iCode8);

	// -----------------------------------------------------------------------
	// ★4次メッシュ（※勝手に考えました）
	// ・3次メッシュを縦、横ともに10等分した四角形(3次メッシュを100分割)
	// ・1辺の長さは約100mとなります。
	// ・3次メッシュの西南端を基点(0, 0)とし、上1桁が北方向へのメッシュ位置、下1桁が東方向へのメッシュ位置を表します。
	// ・1次メッシュ、2次メッシュ、3次メッシュと組み合わせてnnnn-nn-nn-nnのように記述します。
	// -----------------------------------------------------------------------
	// 3次メッシュの南西端の緯度、経度を除算した余りを求める
	const double dLatRest3 = dLatRest2 - (static_cast<double>(iCode7) * dLatUnit2);
	const double dLonRest3 = dLonRest2 - (static_cast<double>(iCode8) * dLonUnit2);

	// 3次メッシュの緯度経度方向ごとの刻み幅（3次メッシュの刻みの1/10）
	const double dLatUnit3 = dLatUnit2 / 10.0;
	const double dLonUnit3 = dLonUnit2 / 10.0;

	const int iCode9 = static_cast<int>(dLatRest3 / dLatUnit3);
	const int iCodeA = static_cast<int>(dLonRest3 / dLonUnit3);
	CString strMeshCode9A;
	strMeshCode9A.Format(_T("%d%d"), iCode9, iCodeA);

	return strMeshCode1234 + _T("-") +  strMeshCode56 + _T("-") + strMeshCode78 + _T("-") + strMeshCode9A;
}
