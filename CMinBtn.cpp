#include "CMinBtn.h"
#include "Resource.h"
#include <new>


// public section //

CMinBtn::CMinBtn( HINSTANCE hInstance )
: CBtnBase( hInstance )
{
    m_hBitmapOut = LoadBitmap( hInstance, MAKEINTRESOURCE(MIN_OUT_BMP) );
    GetObject( m_hBitmapOut, sizeof(BITMAP), &m_bitmapOut );
    m_hBitmapIn = LoadBitmap( hInstance, MAKEINTRESOURCE(MIN_IN_BMP) );
    GetObject( m_hBitmapIn, sizeof(BITMAP), &m_bitmapIn );
    m_hBitmapDown = LoadBitmap( hInstance, MAKEINTRESOURCE(MIN_DOWN_BMP) );
    GetObject( m_hBitmapDown, sizeof(BITMAP), &m_bitmapDown );
}

CMinBtn::~CMinBtn()
{
    if( m_hBitmapOut )
        DeleteObject( m_hBitmapOut );
    if( m_hBitmapIn )
        DeleteObject( m_hBitmapIn );
    if( m_hBitmapDown )
        DeleteObject( m_hBitmapDown );
}

// ボタンが押されているときの処理
void CMinBtn::BtnDown( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmapDown );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmapDown.bmWidth, m_bitmapDown.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(MIN_DOWN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンが押されたときの処理
void CMinBtn::BtnPush()
{
    PlaySound( MAKEINTRESOURCE(MIN_PUSH_WAV), GetModuleHandle(NULL),
        SND_SYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンの上にカーソルが来たときの処理
void CMinBtn::BtnIn( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmapIn );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmapIn.bmWidth, m_bitmapIn.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(MIN_IN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンの外にカーソルがあるときの処理
void CMinBtn::BtnOut( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmapOut );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmapOut.bmWidth, m_bitmapOut.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );
}
