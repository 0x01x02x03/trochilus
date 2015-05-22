#pragma once

#pragma pack(push, 1)
typedef struct _TCP_HEADER  //Ӧ�ò㣬������
{
	WORD SrcPort; // Դ�˿�
	WORD DstPort; // Ŀ�Ķ˿�
	DWORD SeqNum; // ˳���
	DWORD AckNum; // ȷ�Ϻ�
	BYTE DataOff; // TCPͷ��
	BYTE Flags; // ��־��URG��ACK�ȣ�
	WORD Window; // ���ڴ�С
	WORD Chksum; // У���
	WORD UrgPtr; // ����ָ��
} TCP_HEADER, *LPTCP_HEADER;
typedef TCP_HEADER UNALIGNED * ULPTCP;

typedef struct _IP_HEADER  //����㣬�����
{
	BYTE HdrLen:4; // IHL
	BYTE Version:4; // �汾
	BYTE ServiceType; // ��������
	WORD TotalLen; // �ܳ�
	WORD ID; // ��ʶ
	union
	{
		WORD Flags; // ��־
		WORD FragOff; // �ֶ�ƫ��
	};
	BYTE TimeToLive; // ������
	BYTE Protocol; // Э��
	WORD HdrChksum; // ͷУ���
	DWORD SrcAddr; // Դ��ַ
	DWORD DstAddr; // Ŀ�ĵ�ַ
	BYTE Options; // ѡ��
} IP_HEADER, *LPIP_HEADER;
typedef IP_HEADER UNALIGNED * ULPIP;

#define IP_HEADER_LEN_UNIT_BYTE 4 

// ICMPͷ��
typedef struct _ICMP_HEADER
{
	BYTE i_type; //8λ���
	BYTE i_code; //8λ���a
	USHORT i_cksum; //16λУ�� 
	USHORT i_id; //�R�e̖��һ�����M��̖�����R�e̖��
	USHORT i_seq; //��������̖ 
	//	ULONG timestamp; //�r�g��
} ICMP_HEADER, *LPICMP_HEADER;

#pragma pack(pop)


#define ICMP_ECHO        8
#define ICMP_ECHOREPLY   0
