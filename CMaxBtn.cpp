#include "CMaxBtn.h"
#include "Resource.h"
#include <new>


// public section //

CMaxBtn::CMaxBtn( HINSTANCE hInstance )
: CBtnBase( hInstance )
{
    m_hBitmapOut = LoadBitmap( hInstance, MAKEINTRESOURCE(MAX_OUT_BMP) );
    GetObject( m_hBitmapOut, sizeof(BITMAP), &m_bitmapOut );
    m_hBitmapIn = LoadBitmap( hInstance, MAKEINTRESOURCE(MAX_IN_BMP) );
    GetObject( m_hBitmapIn, sizeof(BITMAP), &m_bitmapIn );
    m_hBitmapDown = LoadBitmap( hInstance, MAKEINTRESOURCE(MAX_DOWN_BMP) );
    GetObject( m_hBitmapDown, sizeof(BITMAP), &m_bitmapDown );
}

CMaxBtn::~CMaxBtn()
{
    if( m_hBitmapOut )
        DeleteObject( m_hBitmapOut );
    if( m_hBitmapIn )
        DeleteObject( m_hBitmapIn );
    if( m_hBitmapDown )
        DeleteObject( m_hBitmapDown );
}

// �{�^����������Ă���Ƃ��̏���
void CMaxBtn::BtnDown( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmapDown );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmapDown.bmWidth, m_bitmapDown.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(MAX_DOWN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// �{�^���������ꂽ�Ƃ��̏���
void CMaxBtn::BtnPush()
{
    PlaySound( MAKEINTRESOURCE(MAX_PUSH_WAV), GetModuleHandle(NULL),
        SND_SYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// �{�^���̏�ɃJ�[�\���������Ƃ��̏���
void CMaxBtn::BtnIn( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmapIn );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmapIn.bmWidth, m_bitmapIn.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(MAX_IN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
void CMaxBtn::BtnOut( HDC hdc )
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
