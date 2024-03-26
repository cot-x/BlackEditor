#include "CSearchBtn.h"
#include "Resource.h"
#include <new>

#define BTN_IN      8/10
#define BTN_DOWN    7/10


// public section //

CSearchBtn::CSearchBtn( HINSTANCE hInstance )
: CBtnBase( hInstance )
{
    m_hBitmap = LoadBitmap( hInstance, MAKEINTRESOURCE(SEARCH_BMP) );
    GetObject( m_hBitmap, sizeof(BITMAP), &m_bitmap );
}

CSearchBtn::~CSearchBtn()
{
    if( m_hBitmap )
        DeleteObject( m_hBitmap );
}

// ボタンが押されているときの処理
void CSearchBtn::BtnDown( HDC hdc )
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

    PlaySound( MAKEINTRESOURCE(SEARCH_REPLACE_DOWN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンが押されたときの処理
void CSearchBtn::BtnPush()
{
    PlaySound( MAKEINTRESOURCE(SEARCH_REPLACE_PUSH_WAV), GetModuleHandle(NULL),
        SND_SYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンの上にカーソルが来たときの処理
void CSearchBtn::BtnIn( HDC hdc )
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

    PlaySound( MAKEINTRESOURCE(SEARCH_REPLACE_IN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンの外にカーソルがあるときの処理
void CSearchBtn::BtnOut( HDC hdc )
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
