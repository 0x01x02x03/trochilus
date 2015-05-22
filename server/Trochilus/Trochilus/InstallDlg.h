#pragma once
#include "afxcmn.h"


// CInstallDlg �Ի���

class CInstallDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInstallDlg)

public:
	CInstallDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInstallDlg();

	void Init(LPCTSTR clientid,LPCTSTR ModuleName);

// �Ի�������
	enum { IDD = IDD_DIALOG_INSTALL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	//���ģ��״��
	static DWORD WINAPI CheckModule(LPVOID lpParameter);
	DWORD WINAPI CheckModuleProc();


	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CProgressCtrl m_insProgress;

	CString m_clientid;
	CString m_modname;

	RepeatTask m_CheckRepeat;
	afx_msg void OnBnClickedButtonInstall();
};
