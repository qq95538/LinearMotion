
// PCHostServer.h : PCHostServer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPCHostServerApp:
// �йش����ʵ�֣������ PCHostServer.cpp
//

class CPCHostServerApp : public CWinApp
{
public:
	CPCHostServerApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPCHostServerApp theApp;
