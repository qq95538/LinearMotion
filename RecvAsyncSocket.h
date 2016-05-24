#pragma once

// CRecvAsyncSocket ÃüÁîÄ¿±ê
#define CLIENT_IP_ADDRESS_STRING "192.168.12.102"
#define SERVER_IP_ADDRESS_STRING "192.168.12.101"
#define BUF0_COMMAND_CLIENT_TO_SERVER_VERIFY_USER_PASSWORD (0x01)
#define BUF0_COMMAND_CLIENT_TO_SERVER_REPLY_AN_EXIT_NOTIFICATION (0x02)
//#define BUF0_COMMAND_CLIENT_TO_SERVER_ASK_MOUSE_POINT (0x04)
#define BUF0_COMMAND_SERVER_TO_CLIENT_VERIFY_SERVER (0x81)
#define BUF0_COMMAND_SERVER_TO_CLIENT_EXIT_NOTIFICATION (0x82)
#define BUF0_COMMAND_SERVER_TO_CLIENT_SEND_MOUSE_POINT (0x84)




class CRecvAsyncSocket : public CAsyncSocket
{
public:
	CRecvAsyncSocket();
	virtual ~CRecvAsyncSocket();
	virtual void OnReceive(int nErrorCode);
	CString strSendersIp;
	UINT uSendersPort;
	BOOL bSendMousePointWhenItChanges;
	int SendClientMousePointChange(UINT16 iDeltaXMovement, UINT16 iDeltaTime);
	void NotifyClientExit();

};


