// RecvAsyncSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "PCHostServer.h"
#include "RecvAsyncSocket.h"


// CRecvAsyncSocket

CRecvAsyncSocket::CRecvAsyncSocket():bIsReadyToSend(false)
{
	// Just specify input PORT#, local machine is assumed
	BOOL bRet = Create(8001, SOCK_DGRAM, FD_READ | FD_WRITE, _T(SERVER_IP_ADDRESS_STRING));
	if (bRet != TRUE)
	{
		UINT uErr = GetLastError();
		TCHAR szError[256];
		wsprintf(szError, L"Server Receive Socket Create() failed: %d", uErr);
		AfxMessageBox(szError);
	}
	uSendersPort = 8001;
	strSendersIp = CLIENT_IP_ADDRESS_STRING;
}

CRecvAsyncSocket::~CRecvAsyncSocket()
{
}

// CRecvAsyncSocket 成员函数
void CRecvAsyncSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	static int i = 0;

	i++;

	UINT16 recv_buf[16];
	memset(recv_buf, 0, sizeof(recv_buf));
	int nRead;

	
	// Could use Receive here if you don't need the senders address & port
	nRead = ReceiveFrom(recv_buf, 16, strSendersIp, uSendersPort);
	switch (nRead)
	{
	case 0:       // Connection was closed.
		Close();
		break;
	case SOCKET_ERROR:
	{
		UINT ret = GetLastError();
		if (ret != WSAEWOULDBLOCK)
		{
			TCHAR szError[256];
			wsprintf(szError, L"ReceiveFrom() Function Error: %d", ret);
			AfxMessageBox(szError);
			Close();
		}
		break;
	}
	default: // Normal case: Receive() returned the # of bytes received.
		//AfxMessageBox(strSendersIp);
		//Process buff[0] command from the client. 
		switch (recv_buf[0]) {
			case BUF0_COMMAND_CLIENT_TO_SERVER_VERIFY_USER_PASSWORD:
				if (recv_buf[1] != 1212 || recv_buf[2] != 7329)
				{
					AfxMessageBox(L"User / Password are not right. Login failed.");
					return;
				}
				UINT16 send_buf[3];
				send_buf[0] = BUF0_COMMAND_SERVER_TO_CLIENT_VERIFY_SERVER;
				send_buf[1] = 1234;
				send_buf[2] = 4321;
				if (SendTo(send_buf, sizeof(send_buf), uSendersPort, strSendersIp, 0) != sizeof(send_buf))
				{
					AfxMessageBox(L"Sent Data not equal to which are planned.");
					return;
				}
				AfxMessageBox(L"User/Password Verify Succeed, Connected.");
				bIsReadyToSend = true;
				break;
			case BUF0_COMMAND_CLIENT_TO_SERVER_REPLY_AN_EXIT_NOTIFICATION:
				AfxMessageBox(L"Client Exited Successfully");
				bIsReadyToSend = false;
				break;
			case BUF0_COMMAND_CLIENT_TO_SERVER_REPLY_FOR_FOR_A_STILL_ONLINE_MESSAGE:
				AfxMessageBox(L"Client Is Still Online.");
				bIsReadyToSend = true;
				break;
			default:
				TCHAR szMessageFromClient[256];
				wsprintf(szMessageFromClient, L"ReceiveFrom Message From Client: %d, %d, %d", recv_buf[0], recv_buf[1], recv_buf[2]);
				AfxMessageBox(szMessageFromClient);
				bIsReadyToSend = true;
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

int CRecvAsyncSocket::SendClientMousePointChange(UINT16 iDeltaXMovement, UINT16 iDeltaTime) {
	UINT16 send_buf[3];
	send_buf[0] = BUF0_COMMAND_SERVER_TO_CLIENT_SEND_MOUSE_POINT;
	send_buf[1] = iDeltaXMovement;
	send_buf[2] = iDeltaTime;
	if(bIsReadyToSend){
		if (SendTo(send_buf, sizeof(send_buf), uSendersPort, strSendersIp, 0) != sizeof(send_buf)) {
			AfxMessageBox(L"Sent Data not equal to which are planned.");
			return -1;
		}
	}
	else {
		AfxMessageBox(L"Please connect a client before send data.");
		return -2;
	}
	return 0;
}

int CRecvAsyncSocket::NotifyClientExit()
{
	UINT16 send_buf[3];
	send_buf[0] = BUF0_COMMAND_SERVER_TO_CLIENT_EXIT_NOTIFICATION;
	send_buf[1] = 0;
	send_buf[2] = 0;
	if (bIsReadyToSend) {
		if (SendTo(send_buf, sizeof(send_buf), uSendersPort, strSendersIp, 0) != sizeof(send_buf))
		{
			AfxMessageBox(L"Sent Data not equal to which are planned.");
			return -1;
		}
	}
	else {
		AfxMessageBox(L"Please connect a client before send data.");
		return -2;
	}

	return 0;
}


int CRecvAsyncSocket::CheckWhetherClientIsOnlineOrNot()
{
	UINT16 send_buf[3];
	send_buf[0] = BUF0_COMMAND_SERVER_TO_CLIENT_ASK_FOR_A_STILL_ONLINE_MESSAGE;
	send_buf[1] = 0;
	send_buf[2] = 0;
	if (bIsReadyToSend) {
		if (SendTo(send_buf, sizeof(send_buf), uSendersPort, strSendersIp, 0) != sizeof(send_buf))
		{
			AfxMessageBox(L"Sent Data not equal to which are planned.");
			return -1;
		}
	}
	else {
		AfxMessageBox(L"Please connect a client before send data.");
		return -2;
	}

	return 0;
}
