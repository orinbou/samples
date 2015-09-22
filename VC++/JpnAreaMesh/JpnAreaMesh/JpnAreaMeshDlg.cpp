
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
	this->m_edtMeshCode.SetWindowText(_T("5339-45-26"));
	this->m_chkDokujiMeshCode.SetCheck(BST_CHECKED);

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

	// メッシュコード
	CString strMeshCode;
	this->m_edtMeshCode.GetWindowText(strMeshCode);

	// 取得ボタン
	this->m_btnGetMeshCode.EnableWindow((!strLat.IsEmpty() && !strLon.IsEmpty()) ? TRUE : FALSE);
	this->m_btnGetLatLon.EnableWindow((!strMeshCode.IsEmpty()) ? TRUE : FALSE);
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
void CJpnAreaMeshDlg::OnBnClickedBtnGetMeshCode()
{
	// 緯度
	CString strLat;
	this->m_edtLat.GetWindowText(strLat);
	const double dLat = _ttof(strLat);

	// 経度
	CString strLon;
	this->m_edtLon.GetWindowText(strLon);
	const double dLon = _ttof(strLon);

	// 独自メッシュコード？
	const bool bIsDokujiMesh = (this->m_chkDokujiMeshCode.GetCheck() == BST_CHECKED) ? true : false;

	// メッシュコード取得
	const CString strMeshCode = this->GetMeshCode(dLat, dLon, bIsDokujiMesh);
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
	const double dLon,
	const bool bIsDokujiMesh
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
	// ★4次メッシュ
	// -----------------------------------------------------------------------
	CString strMeshCode9A;
	if (bIsDokujiMesh)
	{
		// -----------------------------------------------------------------------
		// ☆独自4次メッシュ（※勝手に考えました）
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

		strMeshCode9A.Format(_T("%d%d"), iCode9, iCodeA);
	}
	else
	{
		// -----------------------------------------------------------------------
		// ☆第4次メッシュ（1/2地域メッシュ）
		// ・3次メッシュを縦、横ともに2等分した四角形(3次メッシュを4分割)
		// ・1辺の長さは約500mとなります。
		// ・1次メッシュ、2次メッシュ、3次メッシュと組み合わせてnnnn-nn-nn-nのように記述します。
		// ・参考1：http://www.sinfonica.or.jp/mesh/mimginfo.html
		// ・参考2：http://www.opengis.co.jp/htm/basic/mesh_polygon.htm
		// -----------------------------------------------------------------------
		// 3次メッシュの南西端の緯度、経度を除算した余りを求める
		const double dLatRest3 = dLatRest2 - (static_cast<double>(iCode7) * dLatUnit2);
		const double dLonRest3 = dLonRest2 - (static_cast<double>(iCode8) * dLonUnit2);

		// 3次メッシュの緯度経度方向ごとの刻み幅（3次メッシュの刻みの1/2）
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

// 緯度・経度を取得する
void CJpnAreaMeshDlg::OnBnClickedBtnGetLatLon()
{
	// メッシュコード
	CString strMeshCode;
	this->m_edtMeshCode.GetWindowText(strMeshCode);

	double dLat = 0.0;
	double dLon = 0.0;

	// 緯度・経度取得
	this->GetLatLonFromMeshCode(strMeshCode, dLat, dLon);

	// 緯度・経度表示
	CString strResultMsg;
	strResultMsg.Format(_T("(Lat, Lon) : (%f, %f)"), dLat, dLon);
	MessageBox(strResultMsg);
}

/**
* メッシュコードから緯度経度を取得する.
* @param strMeshCode メッシュコード
* @param dLat 緯度
* @param dLon 経度
* @return true:成功 false:失敗
*/
bool CJpnAreaMeshDlg::GetLatLonFromMeshCode(
	const CString strMeshCode,
	double& dLat,
	double& dLon
)
{
	// 2次メッシュの緯度経度方向ごとの刻み幅
	const double dLatUnit2 = (5.0 / 60.0);
	const double dLonUnit2 = (7.0 / 60.0) + (30.0 / 60.0 / 60.0);
	// 3次メッシュの緯度経度方向ごとの刻み幅
	const double dLatUnit3 = dLatUnit2 / 10.0;
	const double dLonUnit3 = dLonUnit2 / 10.0;
	// 4次メッシュの緯度経度方向ごとの刻み幅
	const double dLatUnit4 = dLatUnit3 / 10.0;
	const double dLonUnit4 = dLonUnit3 / 10.0;

	// 初期化
	dLat = 0.0;
	dLon = 0.0;

	// エリアコード分割
	CStringArray aryMeshCode;
	this->SplitString(strMeshCode, _T("-"), aryMeshCode);
	const INT_PTR iCount = aryMeshCode.GetCount();
	if (iCount >= 1)
	{
		// 1次メッシュ
		const CString strCode1234 = aryMeshCode.GetAt(0);
		const CString strCode12 = strCode1234.Left(2);
		const CString strCode34 = strCode1234.Right(2);
		// 緯度
		dLat = ::_ttof(strCode12) / 1.5;
		// 経度
		dLon = ::_ttof(strCode34) + 100.0;
	}
	if (iCount >= 2)
	{
		// 2次メッシュ
		const CString strCode56 = aryMeshCode.GetAt(1);
		const CString strCode5 = strCode56.Left(1);
		const CString strCode6 = strCode56.Right(1);
		// 緯度
		dLat += ::_ttof(strCode5) * dLatUnit2;
		// 経度
		dLon += ::_ttof(strCode6) * dLonUnit2;
	}
	if (iCount >= 3)
	{
		// 3次メッシュ
		const CString strCode78 = aryMeshCode.GetAt(2);
		const CString strCode7 = strCode78.Left(1);
		const CString strCode8 = strCode78.Right(1);
		// 緯度
		dLat += ::_ttof(strCode7) * dLatUnit3;
		// 経度
		dLon += ::_ttof(strCode8) * dLonUnit3;
	}
	if (iCount >= 4)
	{
		// 4次メッシュ
		const CString strCode9A = aryMeshCode.GetAt(3);
		const CString strCode9 = strCode9A.Left(1);
		const CString strCodeA = strCode9A.Right(1);
		// 緯度
		dLat += ::_ttof(strCode9) * dLatUnit4;
		// 経度
		dLon += ::_ttof(strCodeA) * dLonUnit4;
	}

	return true;
}

// セパレータで文字列を分割する
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
