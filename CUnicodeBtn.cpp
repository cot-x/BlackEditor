#include "CUnicodeBtn.h"
#include "Resource.h"
#include <new>

#define BTN_IN      8/10
#define BTN_DOWN    7/10


// public section //

CUnicodeBtn::CUnicodeBtn( HINSTANCE hInstance )
: CBtnBase( hInstance )
{
    m_hBitmapAnsi = LoadBitmap( hInstance, MAKEINTRESOURCE(ANSI_BMP) );
    GetObject( m_hBitmapAnsi, sizeof(BITMAP), &m_bitmapAnsi );
    m_hBitmapUni = LoadBitmap( hInstance, MAKEINTRESOURCE(UNI_BMP) );
    GetObject( m_hBitmapUni, sizeof(BITMAP), &m_bitmapUni );
    m_hBitmapUniRev = LoadBitmap( hInstance, MAKEINTRESOURCE(UNIREV_BMP) );
    GetObject( m_hBitmapUniRev, sizeof(BITMAP), &m_bitmapUniRev );
}

CUnicodeBtn::~CUnicodeBtn()
{
    if( m_hBitmapAnsi )
        DeleteObject( m_hBitmapAnsi );
    if( m_hBitmapUni )
        DeleteObject( m_hBitmapUni );
    if( m_hBitmapUniRev )
        DeleteObject( m_hBitmapUniRev );
}

// ボタンが押されているときの処理
void CUnicodeBtn::BtnDown( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;
    int     nWidth, nHeight;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    if( m_bUnicode ){
        if( m_bReverse ){
            SelectObject( hdcMem, m_hBitmapUniRev );
            nWidth = m_bitmapUniRev.bmWidth;
            nHeight = m_bitmapUniRev.bmHeight;
        }else{
            SelectObject( hdcMem, m_hBitmapUni );
            nWidth = m_bitmapUni.bmWidth;
            nHeight = m_bitmapUni.bmHeight;
        }
    }else{
        SelectObject( hdcMem, m_hBitmapAnsi );
        nWidth = m_bitmapAnsi.bmWidth;
        nHeight = m_bitmapAnsi.bmHeight;
    }
    StretchBlt( hdc, (rect.right-rect.right*BTN_DOWN)/2, (rect.bottom-rect.bottom*BTN_DOWN)/2,
        rect.right*BTN_DOWN, rect.bottom*BTN_DOWN, hdcMem, 0, 0, nWidth, nHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(BTN2_DOWN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンが押されたときの処理
void CUnicodeBtn::BtnPush()
{
    PlaySound( MAKEINTRESOURCE(UNICODE_PUSH_WAV), GetModuleHandle(NULL),
        SND_SYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンの上にカーソルが来たときの処理
void CUnicodeBtn::BtnIn( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;
    int     nWidth, nHeight;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    if( m_bUnicode ){
        if( m_bReverse ){
            SelectObject( hdcMem, m_hBitmapUniRev );
            nWidth = m_bitmapUniRev.bmWidth;
            nHeight = m_bitmapUniRev.bmHeight;
        }else{
            SelectObject( hdcMem, m_hBitmapUni );
            nWidth = m_bitmapUni.bmWidth;
            nHeight = m_bitmapUni.bmHeight;
        }
    }else{
        SelectObject( hdcMem, m_hBitmapAnsi );
        nWidth = m_bitmapAnsi.bmWidth;
        nHeight = m_bitmapAnsi.bmHeight;
    }
    StretchBlt( hdc, (rect.right-rect.right*BTN_IN)/2, (rect.bottom-rect.bottom*BTN_IN)/2,
        rect.right*BTN_IN, rect.bottom*BTN_IN, hdcMem, 0, 0, nWidth, nHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(BTN2_IN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// ボタンの外にカーソルがあるときの処理
void CUnicodeBtn::BtnOut( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;
    int     nWidth, nHeight;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    if( m_bUnicode ){
        if( m_bReverse ){
            SelectObject( hdcMem, m_hBitmapUniRev );
            nWidth = m_bitmapUniRev.bmWidth;
            nHeight = m_bitmapUniRev.bmHeight;
        }else{
            SelectObject( hdcMem, m_hBitmapUni );
            nWidth = m_bitmapUni.bmWidth;
            nHeight = m_bitmapUni.bmHeight;
        }
    }else{
        SelectObject( hdcMem, m_hBitmapAnsi );
        nWidth = m_bitmapAnsi.bmWidth;
        nHeight = m_bitmapAnsi.bmHeight;
    }
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, nWidth, nHeight, SRCCOPY );
    DeleteDC( hdcMem );
}

void CUnicodeBtn::SetUnicode( bool bUnicode, bool bReverse )
{
    if( m_bUnicode = bUnicode )
        m_bReverse = bReverse;

    InvalidateRect( m_hWnd, NULL, TRUE );
}
