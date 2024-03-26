#include "CCRLFBtn.h"
#include "Resource.h"
#include <new>

#define BTN_IN      8/10
#define BTN_DOWN    7/10


// public section //

CCRLFBtn::CCRLFBtn( HINSTANCE hInstance )
: CBtnBase( hInstance )
{
    m_hBitmap = LoadBitmap( hInstance, MAKEINTRESOURCE(CRLF_BMP) );
    GetObject( m_hBitmap, sizeof(BITMAP), &m_bitmap );
}

CCRLFBtn::~CCRLFBtn()
{
    if( m_hBitmap )
        DeleteObject( m_hBitmap );
}

// ボタンが押されているときの処理
void CCRLFBtn::BtnDown( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmap );
    StretchBlt( hdc, (rect.right-rect.right*BTN_DOWN)/2, (rect.bottom-rect.bottom*BTN_DOWN)/2,
        rect.right*BTN_DOWN, rect.bottom*BTN_DOWN,
        hdcMem, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(BTN2_DOWN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンが押されたときの処理
void CCRLFBtn::BtnPush()
{
    PlaySound( MAKEINTRESOURCE(CRLF_PUSH_WAV), GetModuleHandle(NULL),
        SND_SYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンの上にカーソルが来たときの処理
void CCRLFBtn::BtnIn( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmap );
    StretchBlt( hdc, (rect.right-rect.right*BTN_IN)/2, (rect.bottom-rect.bottom*BTN_IN)/2,
        rect.right*BTN_IN, rect.bottom*BTN_IN,
        hdcMem, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(BTN2_IN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンの外にカーソルがあるときの処理
void CCRLFBtn::BtnOut( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmap );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );
}
