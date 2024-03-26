#include "CAboutBtn.h"
#include "Resource.h"
#include <new>

#define ABOUT_TEXT  TEXT("\r\n\t���E����: ��\r\n")                                      \
                    TEXT("\r\n<���ӎ���>\r\n")                                              \
                    TEXT("���̃v���O�����̃��o�[�X�G���W�j�A�����O�A\r\n")                  \
                    TEXT("    �����ȏЉ�A�Ĕz�z�A�܂��͂���ɗނ��鎖�͂ł��܂���B\r\n")\
                    TEXT("�܂��A���̃v���O�������g�p���A\r\n")                              \
                    TEXT("    �����Ȃ��Q�������Ƃ��Ă��A���̐ӔC�͈�ؕ����܂���B\r\n")\
                    TEXT("\r\n<�V���[�g�J�b�g�@�\>\r\n")                                    \
                    TEXT("CTRL+N:\t�V�K\r\n")                                               \
                    TEXT("CTRL+O:\t�J��\r\n")                                               \
                    TEXT("CTRL+S:\t�㏑���ۑ�\r\n")                                         \
                    TEXT("CTRL+A:\t���ׂđI��\r\n")                                         \
                    TEXT("CTRL+C:\t�I��͈͂̃R�s�[\r\n")                                   \
                    TEXT("CTRL+V:\t�\��t��\r\n")                                           \
                    TEXT("CTRL+X:\t�I��͈͂̃J�b�g\r\n")                                   \
                    TEXT("CTRL+Z:\t���ɖ߂�(���O1��̂�)\r\n")                              \
                    TEXT("CTRL+F:\t����\r\n")                                               \
                    TEXT("CTRL+H:\t�u��\r\n")                                               \
                    TEXT("F3:\t�I������Ă��镶����Ɠ������̂������艺�͈̔͂Ō���\r\n")


// public section //

CAboutBtn::CAboutBtn( HINSTANCE hInstance, PTSTR szAppName, PTSTR szAppVer )
: CBtnBase( hInstance ), m_szAppName(szAppName), m_szAppVer(szAppVer)
{
    m_hBitmapOut = LoadBitmap( hInstance, MAKEINTRESOURCE(ABOUT_OUT_BMP) );
    GetObject( m_hBitmapOut, sizeof(BITMAP), &m_bitmapOut );
    m_hBitmapIn = LoadBitmap( hInstance, MAKEINTRESOURCE(ABOUT_IN_BMP) );
    GetObject( m_hBitmapIn, sizeof(BITMAP), &m_bitmapIn );
    m_hBitmapDown = LoadBitmap( hInstance, MAKEINTRESOURCE(ABOUT_DOWN_BMP) );
    GetObject( m_hBitmapDown, sizeof(BITMAP), &m_bitmapDown );

    m_szAboutTitle = new(std::nothrow) TCHAR[lstrlen(m_szAppName)+9]; // �������m��[m_szAboutTitle]
    if( m_szAboutTitle )
        wsprintf( m_szAboutTitle, TEXT("%s - About"), m_szAppName );

    // �������m��[m_szAboutText]
    m_szAboutText = new(std::nothrow) TCHAR[lstrlen(m_szAppName)+lstrlen(m_szAppVer)+lstrlen(ABOUT_TEXT)+2];
    if( m_szAboutText )
        wsprintf( m_szAboutText, TEXT("%s %s") ABOUT_TEXT, m_szAppName, m_szAppVer );
}

CAboutBtn::~CAboutBtn()
{
    if( m_szAboutTitle )
        delete [] m_szAboutTitle;   // �������J��[m_szAboutTitle]
    if( m_szAboutText )
        delete [] m_szAboutText;    // �������J��[m_szAboutText]

    if( m_hBitmapOut )
        DeleteObject( m_hBitmapOut );
    if( m_hBitmapIn )
        DeleteObject( m_hBitmapIn );
    if( m_hBitmapDown )
        DeleteObject( m_hBitmapDown );
}

// �{�^����������Ă���Ƃ��̏���
void CAboutBtn::BtnDown( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmapDown );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmapDown.bmWidth, m_bitmapDown.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(ABOUT_DOWN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// �{�^���������ꂽ�Ƃ��̏���
void CAboutBtn::BtnPush()
{
    PlaySound( MAKEINTRESOURCE(ABOUT_PUSH_WAV), GetModuleHandle(NULL),
        SND_SYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );

    MessageBox( GetParent(m_hWnd), (m_szAboutText?m_szAboutText:m_szAppVer),
        (m_szAboutTitle?m_szAboutTitle:m_szAppName), 0 );

    InvalidateRect( m_hWnd, NULL, TRUE );
}

// �{�^���̏�ɃJ�[�\���������Ƃ��̏���
void CAboutBtn::BtnIn( HDC hdc )
{
    HDC     hdcMem;
    RECT    rect;

    GetClientRect( m_hWnd, &rect );
    hdcMem = CreateCompatibleDC( hdc );
    SelectObject( hdcMem, m_hBitmapIn );
    StretchBlt( hdc, 0, 0, rect.right, rect.bottom,
        hdcMem, 0, 0, m_bitmapIn.bmWidth, m_bitmapIn.bmHeight, SRCCOPY );
    DeleteDC( hdcMem );

    PlaySound( MAKEINTRESOURCE(ABOUT_IN_WAV), GetModuleHandle(NULL),
        SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
}

// �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
void CAboutBtn::BtnOut( HDC hdc )
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
