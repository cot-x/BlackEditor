#include "CAboutBtn.h"
#include "Resource.h"
#include <new>

#define ABOUT_TEXT  TEXT("\r\n\t企画・製作: 流\r\n")                                      \
                    TEXT("\r\n<注意事項>\r\n")                                              \
                    TEXT("このプログラムのリバースエンジニアリング、\r\n")                  \
                    TEXT("    無許可な紹介、再配布、またはそれに類する事はできません。\r\n")\
                    TEXT("また、このプログラムを使用し、\r\n")                              \
                    TEXT("    いかなる被害を被ったとしても、その責任は一切負いません。\r\n")\
                    TEXT("\r\n<ショートカット機能>\r\n")                                    \
                    TEXT("CTRL+N:\t新規\r\n")                                               \
                    TEXT("CTRL+O:\t開く\r\n")                                               \
                    TEXT("CTRL+S:\t上書き保存\r\n")                                         \
                    TEXT("CTRL+A:\tすべて選択\r\n")                                         \
                    TEXT("CTRL+C:\t選択範囲のコピー\r\n")                                   \
                    TEXT("CTRL+V:\t貼り付け\r\n")                                           \
                    TEXT("CTRL+X:\t選択範囲のカット\r\n")                                   \
                    TEXT("CTRL+Z:\t元に戻す(直前1回のみ)\r\n")                              \
                    TEXT("CTRL+F:\t検索\r\n")                                               \
                    TEXT("CTRL+H:\t置換\r\n")                                               \
                    TEXT("F3:\t選択されている文字列と同じものをそれより下の範囲で検索\r\n")


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

    m_szAboutTitle = new(std::nothrow) TCHAR[lstrlen(m_szAppName)+9]; // メモリ確保[m_szAboutTitle]
    if( m_szAboutTitle )
        wsprintf( m_szAboutTitle, TEXT("%s - About"), m_szAppName );

    // メモリ確保[m_szAboutText]
    m_szAboutText = new(std::nothrow) TCHAR[lstrlen(m_szAppName)+lstrlen(m_szAppVer)+lstrlen(ABOUT_TEXT)+2];
    if( m_szAboutText )
        wsprintf( m_szAboutText, TEXT("%s %s") ABOUT_TEXT, m_szAppName, m_szAppVer );
}

CAboutBtn::~CAboutBtn()
{
    if( m_szAboutTitle )
        delete [] m_szAboutTitle;   // メモリ開放[m_szAboutTitle]
    if( m_szAboutText )
        delete [] m_szAboutText;    // メモリ開放[m_szAboutText]

    if( m_hBitmapOut )
        DeleteObject( m_hBitmapOut );
    if( m_hBitmapIn )
        DeleteObject( m_hBitmapIn );
    if( m_hBitmapDown )
        DeleteObject( m_hBitmapDown );
}

// ボタンが押されているときの処理
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

// ボタンが押されたときの処理
void CAboutBtn::BtnPush()
{
    PlaySound( MAKEINTRESOURCE(ABOUT_PUSH_WAV), GetModuleHandle(NULL),
        SND_SYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );

    MessageBox( GetParent(m_hWnd), (m_szAboutText?m_szAboutText:m_szAppVer),
        (m_szAboutTitle?m_szAboutTitle:m_szAppName), 0 );

    InvalidateRect( m_hWnd, NULL, TRUE );
}

// ボタンの上にカーソルが来たときの処理
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

// ボタンの外にカーソルがあるときの処理
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
