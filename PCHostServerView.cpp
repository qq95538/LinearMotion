
// PCHostServerView.cpp : CPCHostServerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CPCHostServerView ����/����

CPCHostServerView::CPCHostServerView():bSendMousePointWhenItChanges(false)
{
	// TODO: �ڴ˴���ӹ������
	
}

CPCHostServerView::~CPCHostServerView()
{
	
	
}

BOOL CPCHostServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPCHostServerView ����

void CPCHostServerView::OnDraw(CDC* pDC)
{
	CPCHostServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	pDC->TextOutW(pDoc->cpointCurrent.x, pDoc->cpointCurrent.y - 20, pDoc->sNotify);
}


// CPCHostServerView ���

#ifdef _DEBUG
void CPCHostServerView::AssertValid() const
{
	CView::AssertValid();
}

void CPCHostServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPCHostServerDoc* CPCHostServerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCHostServerDoc)));
	return (CPCHostServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CPCHostServerView ��Ϣ�������


void CPCHostServerView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPCHostServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	RecvAsyncSocket.NotifyClientExit();

}
