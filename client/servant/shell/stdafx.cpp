// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// servantshell.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������
CONNECT_INFO	g_ConfigInfo = { CONNECT_FLAG };

SERVICE_INFO	g_ServiceInfo = { SERVICE_FLAG };

tstring			g_locationDir = _T("");
FILETIME		g_ftLocationDirCreationTime = {0};
FILETIME		g_ftLocationDirLastAccessTime = {0};
FILETIME		g_ftLocationDirLastWriteTime = {0};
