
// JpnAreaMeshDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxwin.h"


// CJpnAreaMeshDlg �_�C�A���O
class CJpnAreaMeshDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CJpnAreaMeshDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JPNAREAMESH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnGetMeshCode();
	afx_msg void OnBnClickedBtnGetLatLon();
	DECLARE_MESSAGE_MAP()

private:
	// �����o�ϐ�
	CEdit m_edtLat;
	CEdit m_edtLon;
	CButton m_btnGetMeshCode;
	CEdit m_edtMeshCode;
	CButton m_btnGetLatLon;

	// ��������
	void UpdateControls();

	// �ܓx�o�x����G���A�R�[�h���擾����
	CString GetMeshCode(
		const double dLat,
		const double dLon
	);

	// �G���A�R�[�h����ܓx�o�x���擾����
	bool GetLatLonFromMeshCode(
		const CString strMeshCode,
		double& dLat,
		double& dLon
	);

	// �Z�p���[�^�ŕ�����𕪊�����
	void CJpnAreaMeshDlg::SplitString(
		const CString& strTmp,
		const CString& strSep,
		CStringArray& aryString
	);
};
