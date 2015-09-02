#pragma once


// CPropertyPage1 ダイアログ

class CPropertyPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyPage1)

public:
	CPropertyPage1();
	virtual ~CPropertyPage1();

// ダイアログ データ
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

private:
	// イベントハンドラ
	afx_msg void OnBnClickedButton1();
};
