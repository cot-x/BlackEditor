#include "CSearchNextBtn.h"
#include "Resource.h"
#include <new>

#define BTN_IN      8/10
#define BTN_DOWN    7/10


// public section //

CSearchNextBtn::CSearchNextBtn( HINSTANCE hInstance )
: CBtnBase( hInstance )
{
    m_hBitmap = LoadBitmap( hInstance, MAKEINTRESOURCE(SEARCH_NEXT_BMP) );
    GetObject( m_hBitmap, sizeof(BITMAP), &m_bitmap );
}

CSearchNextBtn::~CSearchNextBtn()
{
    if( m_hBitmap )
        DeleteObject( m_hBitmap );
}

// �{�^����������Ă���Ƃ��̏���
void CSearchNextBtn::BtnDown( HDC hdc )
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

// �{�^���������ꂽ�Ƃ��̏���
void CSearchNextBtn::BtnPush()
{
    PlaySound( MAKEINTRESOURCE(SEARCH_REPLACE_PUSH_WAV), GetModuleHandle(NULL),
        SND_SYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// �{�^���̏�ɃJ�[�\���������Ƃ��̏���
void CSearchNextBtn::BtnIn( HDC hdc )
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

// �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
void CSearchNextBtn::BtnOut( HDC hdc )
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
