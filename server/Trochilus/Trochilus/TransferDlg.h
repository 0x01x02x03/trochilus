#pragma once
#include "afxcmn.h"
#include "thread/RepeatTask.h"
#include "ProgressListCtrl.h"

class CTransferDlg : public CDialogEx,public IModule
{
	DECLARE_DYNAMIC(CTransferDlg)

public:

	CTransferDlg(CWnd* pParent = NULL);
	virtual ~CTransferDlg();

	enum { IDD = IDD_DIALOG_TRANSFER };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()

public:

	//��ʼ������ؼ�������
	void InitView();
	void InitData();
	virtual BOOL OnInitDialog();

	//��ʱ����ļ�����״̬
	static DWORD WINAPI CheckTaskList(LPVOID lpParameter);
	DWORD CheckTaskListProc();

	//����ģ����Ϣ
	static void HandleModuleMsg(LPCTSTR clientid,UINT nMsg, LPVOID lpContext, LPVOID lpParameter)
	{
		return;
	}

	RepeatTask m_checkTask;
	CListCtrl m_transList;
	CImageList m_ImageList;

	//��Ӧ����������Ϣ
	afx_msg void OnDestroy();
};
