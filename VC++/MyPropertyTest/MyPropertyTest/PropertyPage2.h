#pragma once


// CPropertyPage2 �_�C�A���O

class CPropertyPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyPage2)

public:
	CPropertyPage2();
	virtual ~CPropertyPage2();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

private:
	// �C�x���g�n���h��
	afx_msg void OnBnClickedButton2();
};
