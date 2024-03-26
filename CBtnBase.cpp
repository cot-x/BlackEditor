#include "CBtnBase.h"
#include <new>

#define BTNBASE_CLASSNAME   TEXT("BlackEditor_BtnBase")

#define ID_BTN  0


// private section //

bool CBtnBase::ms_bClass = false;


// public section //

CBtnBase::CBtnBase( HINSTANCE hInstance )
:   m_hWnd(NULL), m_hInstance(hInstance), m_bMouseDown(false), m_bMouseIn(false)
{
    if( !ms_bClass ){
        WNDCLASSEX  wc;
        wc.cbSize           = sizeof(wc);
        wc.style            = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc      = CBtnBase::WndProc;
        wc.cbClsExtra       = 0;
        wc.cbWndExtra       = 0;
        wc.hInstance        = m_hInstance;
        wc.hIcon            = NULL;
        wc.hCursor          = LoadCursor( NULL, IDC_CROSS );
        wc.hbrBackground    = CreateSolidBrush( RGB(0,0,0) );
        wc.lpszMenuName     = NULL;
        wc.lpszClassName    = BTNBASE_CLASSNAME;
        wc.hIconSm          = NULL;
        RegisterClassEx( &wc );
        ms_bClass = true;
    }
}

CBtnBase::~CBtnBase()
{
}

// static
LRESULT CALLBACK CBtnBase::WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    bool        bNewMouseIn;
    PAINTSTRUCT ps;
    PCBtnBase   This = (PCBtnBase)GetWindowLong(hWnd, GWL_USERDATA);

    if( !This )
        return DefWindowProc( hWnd, Msg, wParam, lParam );

    switch( Msg ){
    case WM_SIZE:
        This->m_nWidth = LOWORD(lParam);
        This->m_nHeight = HIWORD(lParam);
        return 0;

    case WM_LBUTTONDOWN:
        SetCapture( hWnd );
        InvalidateRect( hWnd, NULL, TRUE );
        This->m_bMouseDown = true;
        return 0;

    case WM_LBUTTONUP:
        if( !This->m_bMouseDown )
            return 0;
        ReleaseCapture();
        InvalidateRect( hWnd, NULL, TRUE );
        if( This->m_bMouseIn ){
            This->BtnPush();
            PostMessage( GetParent(hWnd), WM_COMMAND,
                (WPARAM)GetWindowLong(hWnd, GWL_ID), (LPARAM)hWnd );
            This->m_bMouseIn = false;
        }
        This->m_bMouseDown = false;
        return 0;

    case WM_MOUSEMOVE:
        if( 0<=LOWORD(lParam) && 0<=HIWORD(lParam)
                && LOWORD(lParam)<=This->m_nWidth && HIWORD(lParam)<=This->m_nHeight ){
            if( !This->m_bMouseDown )
                SetCapture( hWnd );
            bNewMouseIn = true;
        }else{
            if( !This->m_bMouseDown )
                ReleaseCapture();
            bNewMouseIn = false;
        }

        if( This->m_bMouseIn != bNewMouseIn )
            InvalidateRect( hWnd, NULL, TRUE );

        This->m_bMouseIn = bNewMouseIn;
        return 0;

    case WM_PAINT:
        BeginPaint( hWnd, &ps );
        if( !This->m_bMouseIn )                         // カーソルは外
            This->BtnOut( ps.hdc );
        if( !This->m_bMouseDown && This->m_bMouseIn )   // カーソルは中(ButtonUp)
            This->BtnIn( ps.hdc );
        if( This->m_bMouseDown && This->m_bMouseIn )    // カーソルは中(ButtonDown)
            This->BtnDown( ps.hdc );
        EndPaint( hWnd, &ps );
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );
}

bool CBtnBase::CreateControl( HWND hWndParent, WORD wID )
{
    if( m_hWnd )
        return false;

    m_hWnd = CreateWindow( BTNBASE_CLASSNAME, NULL, WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0, hWndParent, (HMENU)wID, m_hInstance, NULL );
    if( !m_hWnd )
        return false;
    SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this );

    return true;
}

bool CBtnBase::MoveControl( int x, int y, int nWidth, int nHeight )
{
    if( !m_hWnd )
        return false;

    BOOL bRet = MoveWindow( m_hWnd, x, y, nWidth, nHeight, TRUE );
    return bRet?true:false;
}

void CBtnBase::Show( bool bShow )
{
    if( !m_hWnd )
        return;

    ShowWindow( m_hWnd, (bShow?SW_SHOW:SW_HIDE) );
}
