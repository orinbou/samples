#pragma once


// CPropertyPage1 �_�C�A���O

class CPropertyPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyPage1)

public:
	CPropertyPage1();
	virtual ~CPropertyPage1();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

private:
	// �C�x���g�n���h��
	afx_msg void OnBnClickedButton1();
};
