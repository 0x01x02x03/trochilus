#include "stdafx.h"
#include <Winsock2.h>
#include "socket/MySocket.h"
#include "ICMPStructs.h"
#include "ICMPSocket.h"

ICMPSocket::ICMPSocket()
	: m_sock(INVALID_SOCKET)
	, m_listenIP(0)
{

}

ICMPSocket::~ICMPSocket()
{
	Close();
}

BOOL ICMPSocket::Create( LPCTSTR listenIPOrHost )
{
	tstring iporhost;
	if (NULL == listenIPOrHost)
	{
		char hostname[128] = {0};
		gethostname(hostname, 128);
		iporhost = a2t(hostname);
	}
	else
	{
		iporhost = listenIPOrHost;
	}

	Close();

	m_listenIP = INADDR_NONE;
	if (! MySocket::IPOrHostname2IP(iporhost.c_str(), m_listenIP))
	{
		errorLog(_T("invalid listeniporhost [%s]"), listenIPOrHost);
		return FALSE;
	}

	if (! CreateListenSocket(m_listenIP, m_sock))
	{
		errorLog(_T("create listen socket failed"));
		m_sock = INVALID_SOCKET;

		return FALSE;
	}

	return TRUE;
}

ULONG ICMPSocket::GetListenIP() const
{
	return m_listenIP;
}

BOOL ICMPSocket::RecvICMP( ULONG& srcIP, ULONG& destIP, ByteBuffer& icmpData )
{
	ByteBuffer buffer;
	buffer.Alloc(1024 * 4);
	int ret = recv(m_sock, (char*)(LPBYTE)buffer, buffer.Size(), 0);
	if (SOCKET_ERROR == ret)
	{
		errorLog(_T("recv failed.WE%d"), ::WSAGetLastError());
		return FALSE;
	}

	LPIP_HEADER pIpHeader = (LPIP_HEADER)(LPBYTE)buffer;
	if (IPPROTO_ICMP != pIpHeader->Protocol) return FALSE;

	LPICMP_HEADER pIcmpHeader = (LPICMP_HEADER) ((LPBYTE)buffer + pIpHeader->HdrLen * IP_HEADER_LEN_UNIT_BYTE);
	if (ICMP_ECHO != pIcmpHeader->i_type) return FALSE;

	LPBYTE pIcmpData = (LPBYTE)pIcmpHeader + sizeof(ICMP_HEADER);
	int iIcmpDataLen = ret - pIpHeader->HdrLen * IP_HEADER_LEN_UNIT_BYTE - sizeof(ICMP_HEADER);

	srcIP = pIpHeader->SrcAddr;
	destIP = pIpHeader->DstAddr;

	icmpData.Alloc(iIcmpDataLen);
	memcpy((LPBYTE)icmpData, pIcmpData, iIcmpDataLen);

	return TRUE;
}

void ICMPSocket::Close()
{
	if (INVALID_SOCKET != m_sock)
	{
		::closesocket(m_sock);
		m_sock = INVALID_SOCKET;
	}
}

#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
BOOL ICMPSocket::CreateListenSocket( ULONG ip, SOCKET& sock ) const
{
	// ����ԭʼ�׽���
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	// ����IPͷ����ѡ�����flag ����Ϊture�����Զ�IPͷ���д���
	DWORD flag = TRUE;
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag));

	// ���SOCKADDR_IN�ṹ
	SOCKADDR_IN addr_in;
	addr_in.sin_addr.S_un.S_addr = ip;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(1004);

	// ��ԭʼ�׽���sock �󶨵�����������ַ��
	if (0 != bind(sock, (PSOCKADDR)&addr_in, sizeof(addr_in)))
	{
		::closesocket(sock);
		errorLog(_T("bind %X failed.WE%d"), ip, ::WSAGetLastError());

		return FALSE;
	}

	// dwValueΪ�������������Ϊ1ʱִ�У�0ʱȡ��
	DWORD dwValue = 1;
	// ���� SOCK_RAW ΪSIO_RCVALL���Ա�������е�IP��������SIO_RCVALL
	// �Ķ���Ϊ�� #define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
	ioctlsocket(sock, SIO_RCVALL, &dwValue); //����������Ϊ���ģʽ  

	return TRUE;
}

