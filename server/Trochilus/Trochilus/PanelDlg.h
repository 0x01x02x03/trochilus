#pragma once
#include "afxcmn.h"
#include "FileMgrDlg.h"
#include "TransferDlg.h"
#include "CmdDlg.h"
// CPanelDlg �Ի���



class CPanelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPanelDlg)

public:
	CPanelDlg(CWnd* pParent = NULL);
	virtual ~CPanelDlg();
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
	void InitOutsideModule();
	virtual BOOL OnInitDialog();

	//����ģ��ص���Ϣ
	void HandleModuleMsg(UINT nMsg, LPVOID lpContext, LPVOID lpParameter);

	//����ģ��״̬��Ϣ
	void HandleMsgNotify(UINT nType, LPCTSTR lpContext);

	//��Tab��ѡ��ı�
	afx_msg void OnTcnSelchangeTabPanel(NMHDR *pNMHDR, LRESULT *pResult);

	//���ÿͻ���ID
	void SetClientID(LPCTSTR clientid)
	{
		m_clientid = clientid;
	}

private:

	CTabCtrl m_TabCtrl;
	CListCtrl m_msgList;
	CImageList m_ImageList;

	typedef std::map<tstring,tstring> ModuleCallBack;
	ModuleCallBack m_moduleinfo;

	CString m_clientid;
	ModuleMap m_moduleMap;
	CriticalSection m_csModuleMap;

	typedef std::list<CString> ClientModList;
	ClientModList m_clientModList;


	typedef std::list<CDialogEx*> NewMemList;

	NewMemList m_MemList;

public:
	afx_msg void OnClose();
};
