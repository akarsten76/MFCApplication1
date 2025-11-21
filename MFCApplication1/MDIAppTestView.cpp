
// MDIAppTestView.cpp : implementation of the CMDIAppTestView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MDIAppTest.h"
#endif

#include "MDIAppTestDoc.h"
#include "MDIAppTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDIAppTestView

IMPLEMENT_DYNCREATE(CMDIAppTestView, CView)

BEGIN_MESSAGE_MAP(CMDIAppTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMDIAppTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMDIAppTestView construction/destruction

CMDIAppTestView::CMDIAppTestView() noexcept
{
	// TODO: add construction code here

}

CMDIAppTestView::~CMDIAppTestView()
{
}

BOOL CMDIAppTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMDIAppTestView drawing

void CMDIAppTestView::OnDraw(CDC* /*pDC*/)
{
	CMDIAppTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMDIAppTestView printing


void CMDIAppTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMDIAppTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMDIAppTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMDIAppTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMDIAppTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMDIAppTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMDIAppTestView diagnostics

#ifdef _DEBUG
void CMDIAppTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIAppTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDIAppTestDoc* CMDIAppTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIAppTestDoc)));
	return (CMDIAppTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMDIAppTestView message handlers
