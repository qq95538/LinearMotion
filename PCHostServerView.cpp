
// PCHostServerView.cpp : CPCHostServerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PCHostServer.h"
#endif

#include "PCHostServerDoc.h"
#include "PCHostServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPCHostServerView

IMPLEMENT_DYNCREATE(CPCHostServerView, CView)

BEGIN_MESSAGE_MAP(CPCHostServerView, CView)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SENDMOUSEPOINT, &CPCHostServerView::OnSendmousepoint)
	ON_COMMAND(ID_LETCLIENTEXIT, &CPCHostServerView::OnLetClientExit)
END_MESSAGE_MAP()

// CPCHostServerView 构造/析构

CPCHostServerView::CPCHostServerView():bSendMousePointWhenItChanges(false)
{
	// TODO: 在此处添加构造代码
	
}

CPCHostServerView::~CPCHostServerView()
{
	
	
}

BOOL CPCHostServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPCHostServerView 绘制

void CPCHostServerView::OnDraw(CDC* pDC)
{
	CPCHostServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	pDC->TextOutW(pDoc->cpointCurrent.x, pDoc->cpointCurrent.y - 20, pDoc->sNotify);
}


// CPCHostServerView 诊断

#ifdef _DEBUG
void CPCHostServerView::AssertValid() const
{
	CView::AssertValid();
}

void CPCHostServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPCHostServerDoc* CPCHostServerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCHostServerDoc)));
	return (CPCHostServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CPCHostServerView 消息处理程序


void CPCHostServerView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPCHostServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此添加命令处理程序代码
	INT16 iDeltaX = point.x - pDoc->cpointCurrent.x;
	UINT16 iDirection = 0;
	pDoc->cpointCurrent = point;

	if (iDeltaX < 0) {
		iDeltaX = -iDeltaX;
		iDirection = 0;
	}
	else {
		iDirection = 1;
	}
	if (bSendMousePointWhenItChanges) {
		pDoc->sNotify.Format(_T("%d"), point.x);
		RecvAsyncSocket.SendClientMousePointChange((UINT16)iDeltaX, iDirection);
	}
	RedrawWindow();
	CView::OnMouseMove(nFlags, point);
}



void CPCHostServerView::OnSendmousepoint()
{
	bSendMousePointWhenItChanges = !bSendMousePointWhenItChanges;

}


void CPCHostServerView::OnLetClientExit()
{
	// TODO: 在此添加命令处理程序代码
	RecvAsyncSocket.NotifyClientExit();

}
