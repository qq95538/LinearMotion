#pragma once

// CRecvAsyncSocket ÃüÁîÄ¿±ê
#define CLIENT_IP_ADDRESS_STRING "192.168.2.15"
#define SERVER_IP_ADDRESS_STRING "192.168.2.3"
#define BUF0_COMMAND_CLIENT_TO_SERVER_VERIFY_USER_PASSWORD (0x01)
#define BUF0_COMMAND_CLIENT_TO_SERVER_REPLY_AN_EXIT_NOTIFICATION (0x02)
//#define BUF0_COMMAND_CLIENT_TO_SERVER_REPLY_FOR_RECEIVING_MOUSE_POINT (0x04)
#define BUF0_COMMAND_CLIENT_TO_SERVER_REPLY_FOR_FOR_A_STILL_ONLINE_MESSAGE (0x08)
#define BUF0_COMMAND_SERVER_TO_CLIENT_VERIFY_SERVER (0x81)
#define BUF0_COMMAND_SERVER_TO_CLIENT_EXIT_NOTIFICATION (0x82)
#define BUF0_COMMAND_SERVER_TO_CLIENT_SEND_MOUSE_POINT (0x84)
#define BUF0_COMMAND_SERVER_TO_CLIENT_ASK_FOR_A_STILL_ONLINE_MESSAGE (0x88)


class CRecvAsyncSocket : public CAsyncSocket
{
public:
	CRecvAsyncSocket();
	virtual ~CRecvAsyncSocket();
	virtual void OnReceive(int nErrorCode);
	CString strSendersIp;
	UINT uSendersPort;
	int SendClientMousePointChange(UINT16 iDeltaXMovement, UINT16 iDeltaTime);
	int NotifyClientExit();
	int CheckWhetherClientIsOnlineOrNot();
	bool bIsReadyToSend;
};


