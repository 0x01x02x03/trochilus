#pragma once
#include "afxcmn.h"
#include "FileMgrDlg.h"
#include "TransferDlg.h"
#include "CmdDlg.h"
// CPanelDlg �Ի���



class CFilePanelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilePanelDlg)

public:
	CFilePanelDlg(CWnd* pParent = NULL);
	virtual ~CFilePanelDlg();
	// �Ի�������
	enum { IDD = IDD_DIALOG_PANEL };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()

public:
	//��ʼ������͹���״̬
	void InitView();
	void InitData();
	void InitInsideModule();
	virtual BOOL OnInitDialog();

	//����ģ��״̬��Ϣ
	void HandleMsgNotify(UINT nType, LPCTSTR lpContext);

	//��Tab��ѡ��ı�
	afx_msg void OnTcnSelchangeTabPanel(NMHDR *pNMHDR, LRESULT *pResult);

	//���ÿͻ���ID
	void SetClientID(LPCTSTR clientid)
	{
		m_clientid = clientid;
		
		FileDlg.InitModule(clientid);
		TransDlg.InitModule(clientid);

	}

private:

	CTabCtrl m_TabCtrl;

	typedef std::map<tstring,tstring> ModuleCallBack;
	ModuleCallBack m_moduleinfo;

	CString m_clientid;
	CriticalSection m_csModuleMap;

	CFileMgrDlg FileDlg;
	CTransferDlg TransDlg;

public:
	afx_msg void OnClose();
};
