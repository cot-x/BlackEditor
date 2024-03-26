#include "CMove.h"
#include "Resource.h"
#include <new>

#define MOVE_CLASSNAME  TEXT("BlackEditor_Move")


// public section //

CMove::CMove( HINSTANCE hInstance )
:   m_hWnd(NULL), m_hInstance(hInstance)
{
    WNDCLASSEX  wc;
    wc.cbSize           = sizeof(wc);
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = CMove::WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = m_hInstance;
    wc.hIcon            = NULL;
    wc.hCursor          = LoadCursor( NULL, IDC_SIZEALL );
    wc.hbrBackground    = CreateSolidBrush( RGB(0,0,0) );
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = MOVE_CLASSNAME;
    wc.hIconSm          = NULL;
    RegisterClassEx( &wc );

    m_hBitmap = LoadBitmap( hInstance, MAKEINTRESOURCE(MOVE_BMP) );
    GetObject( m_hBitmap, sizeof(BITMAP), &m_bitmap );
}

CMove::~CMove()
{
    if( m_hBitmap )
        DeleteObject( m_hBitmap );
}

bool CMove::CreateControl( HWND hWndParent, WORD wID )
{
    if( m_hWnd )
        return false;

    m_hWndParent = hWndParent;

    m_hWnd = CreateWindow( MOVE_CLASSNAME, NULL, WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0, m_hWndParent, (HMENU)wID, m_hInstance, NULL );
    if( !m_hWnd )
        return false;
    SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this );

    return true;
}

bool CMove::MoveControl( int x, int y, int nWidht, int nHeight )
{
    if( !m_hWnd )
        return false;

    BOOL bRet = MoveWindow( m_hWnd, x, y, nWidht, nHeight, TRUE );
    return bRet?true:false;
}

void CMove::Enable( bool bEnable )
{
    if( !m_hWnd )
        return;

    EnableWindow( m_hWnd, bEnable );
}

LRESULT CALLBACK CMove::WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    static bool     s_bMouseDown = false;
    static POINT    s_OldPos;
    POINT           CursorPos;
    RECT            WndRect;
    PAINTSTRUCT     ps;
    RECT            rect;
    HDC             hdcMem;

    switch( Msg ){
    case WM_PAINT:
        BeginPaint( hWnd, &ps );
        GetClientRect( hWnd, &rect );
        hdcMem = CreateCompatibleDC( ps.hdc );
        SelectObject( hdcMem, ((PCMove)GetWindowLong(hWnd, GWL_USERDATA))->m_hBitmap );
        StretchBlt( ps.hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0,
            ((PCMove)GetWindowLong(hWnd, GWL_USERDATA))->m_bitmap.bmWidth,
            ((PCMove)GetWindowLong(hWnd, GWL_USERDATA))->m_bitmap.bmHeight, SRCCOPY );
        DeleteDC( hdcMem );
        EndPaint( hWnd, &ps );
        return 0;

    case WM_LBUTTONDOWN:
        SetCapture( hWnd );
        s_bMouseDown = true;
        GetCursorPos( &s_OldPos );
        return 0;

    case WM_LBUTTONUP:
        if( !s_bMouseDown )
            return 0;
        ReleaseCapture();
        s_bMouseDown = false;
        return 0;

    case WM_MOUSEMOVE:
        if( s_bMouseDown ){
            GetCursorPos( &CursorPos );
            GetWindowRect(
                ((PCMove)GetWindowLong(hWnd, GWL_USERDATA))->m_hWndParent, &WndRect );
            WndRect.left += CursorPos.x - s_OldPos.x;
            WndRect.top += CursorPos.y - s_OldPos.y;
            s_OldPos = CursorPos;
            SetWindowPos( ((PCMove)GetWindowLong(hWnd, GWL_USERDATA))->m_hWndParent,
                NULL, WndRect.left, WndRect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
        }
        return 0;
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );
}
