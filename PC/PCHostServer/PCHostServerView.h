
// PCHostServerView.h : CPCHostServerView ��Ľӿ�
//

#pragma once
#include "RecvAsyncSocket.h"

class CPCHostServerView : public CView
{
protected: // �������л�����
	CPCHostServerView();
	DECLARE_DYNCREATE(CPCHostServerView)

// ����
public:
	CPCHostServerDoc* GetDocument() const;
	
// ����
public:
	BOOL bSendMousePointWhenItChanges;
	CRecvAsyncSocket *pRecvAsyncSocket;
	

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CPCHostServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSendmousepoint();
	afx_msg void OnLetClientExit();
	afx_msg void OnAskClientIsItOnline();
};

#ifndef _DEBUG  // PCHostServerView.cpp �еĵ��԰汾
inline CPCHostServerDoc* CPCHostServerView::GetDocument() const
   { return reinterpret_cast<CPCHostServerDoc*>(m_pDocument); }
#endif

