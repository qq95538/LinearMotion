
// PCHostServerView.h : CPCHostServerView 类的接口
//

#pragma once
#include "RecvAsyncSocket.h"

class CPCHostServerView : public CView
{
protected: // 仅从序列化创建
	CPCHostServerView();
	DECLARE_DYNCREATE(CPCHostServerView)

// 特性
public:
	CPCHostServerDoc* GetDocument() const;
	
// 操作
public:
	BOOL bSendMousePointWhenItChanges;
	CRecvAsyncSocket *pRecvAsyncSocket;
	

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CPCHostServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSendmousepoint();
	afx_msg void OnLetClientExit();
	afx_msg void OnAskClientIsItOnline();
};

#ifndef _DEBUG  // PCHostServerView.cpp 中的调试版本
inline CPCHostServerDoc* CPCHostServerView::GetDocument() const
   { return reinterpret_cast<CPCHostServerDoc*>(m_pDocument); }
#endif

