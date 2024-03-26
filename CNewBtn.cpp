#include "CNewBtn.h"
#include "Resource.h"
#include <new>


// public section //

CNewBtn::CNewBtn( HINSTANCE hInstance )
: CBtnBase( hInstance )
{
    m_hBitmapOut = LoadBitmap( hInstance, MAKEINTRESOURCE(NEW_OUT_BMP) );
    GetObject( m_hBitmapOut, sizeof(BITMAP), &m_bitmapOut );
    m_hBitmapIn = LoadBitmap( hInstance, MAKEINTRESOURCE(NEW_IN_BMP) );
    GetObject( m_hBitmapIn, sizeof(BITMAP), &m_bitmapIn );
    m_hBitmapDown = LoadBitmap( hInstance, MAKEINTRESOURCE(NEW_DOWN_BMP) );
    GetObject( m_hBitmapDown, sizeof(BITMAP), &m_bitmapDown );
}

CNewBtn::~CNewBtn()
{
    if( m_hBitmapOut )
        DeleteObject( m_hBitmapOut );
    if( m_hBitmapIn )
        DeleteObject( m_hBitmapIn );
    if( m_hBitmapDown )
        DeleteObject( m_hBitmapDown );
}

// �{�^����������Ă���Ƃ��̏���
void CNewBtn::BtnDown( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmapDown );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmapDown.bmWidth, m_bitmapDown.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(BTN_DOWN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// �{�^���������ꂽ�Ƃ��̏���
void CNewBtn::BtnPush()
{
    PlaySound( MAKEINTRESOURCE(BTN_PUSH_WAV), GetModuleHandle(NULL),
        SND_SYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// �{�^���̏�ɃJ�[�\���������Ƃ��̏���
void CNewBtn::BtnIn( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmapIn );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmapIn.bmWidth, m_bitmapIn.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(BTN_IN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
void CNewBtn::BtnOut( HDC hdc )
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
