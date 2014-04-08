
// OmpSampleDlg.h : ヘッダー ファイル
//

#pragma once


// COmpSampleDlg ダイアログ
class COmpSampleDlg : public CDialogEx
{
// コンストラクション
public:
	COmpSampleDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_OMPSAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedOmpGo();
	DECLARE_MESSAGE_MAP()

	// 外部アプリケーション起動
	static bool executeProcess(
		const CString& strAppPath,
		const CString& strParam
	);
public:
	afx_msg void OnBnClickedOmpGo1();
	afx_msg void OnBnClickedOmpGo2();
};
