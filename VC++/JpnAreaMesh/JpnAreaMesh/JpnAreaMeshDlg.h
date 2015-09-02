
// JpnAreaMeshDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"


// CJpnAreaMeshDlg ダイアログ
class CJpnAreaMeshDlg : public CDialogEx
{
// コンストラクション
public:
	CJpnAreaMeshDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JPNAREAMESH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnGetMeshCode();
	afx_msg void OnBnClickedBtnGetLatLon();
	DECLARE_MESSAGE_MAP()

private:
	// メンバ変数
	CEdit m_edtLat;
	CEdit m_edtLon;
	CButton m_btnGetMeshCode;
	CEdit m_edtMeshCode;
	CButton m_btnGetLatLon;

	// 活性制御
	void UpdateControls();

	// 緯度経度からエリアコードを取得する
	CString GetMeshCode(
		const double dLat,
		const double dLon
	);

	// エリアコードから緯度経度を取得する
	bool GetLatLonFromMeshCode(
		const CString strMeshCode,
		double& dLat,
		double& dLon
	);

	// セパレータで文字列を分割する
	void CJpnAreaMeshDlg::SplitString(
		const CString& strTmp,
		const CString& strSep,
		CStringArray& aryString
	);
};
