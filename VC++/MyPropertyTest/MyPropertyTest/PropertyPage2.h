#pragma once


// CPropertyPage2 ダイアログ

class CPropertyPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyPage2)

public:
	CPropertyPage2();
	virtual ~CPropertyPage2();

// ダイアログ データ
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

private:
	// イベントハンドラ
	afx_msg void OnBnClickedButton2();
};
