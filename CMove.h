// CMove
//  MOVEコントロール処理クラス
//  インスタンスは一つのみ

#ifndef _CMove_
#define _CMove_

#include <windows.h>

class CMove
{
private:
    HINSTANCE   m_hInstance;
    HWND        m_hWnd, m_hWndParent;
    HBITMAP     m_hBitmap;
    BITMAP      m_bitmap;

    CMove( const CMove & );
    CMove & operator =( const CMove & );

public:
    CMove( HINSTANCE hInstance );
    virtual ~CMove();

    bool CreateControl( HWND hWndParent, WORD wID );
    bool MoveControl( int x, int y, int nWidht, int nHeight );
    void Enable( bool bEnable );

    static LRESULT CALLBACK WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
};

typedef CMove   *PCMove;

#endif  // _CMove_
