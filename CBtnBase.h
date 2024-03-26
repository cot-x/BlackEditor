// CBtnBase
//  ボタン処理ベースクラス

#ifndef _CBtnBase_
#define _CBtnBase_

#include <windows.h>

class CBtnBase
{
private:
    static bool ms_bClass;
    HINSTANCE   m_hInstance;
    int         m_nWidth, m_nHeight;
    bool        m_bMouseDown, m_bMouseIn;

    CBtnBase( const CBtnBase & );
    CBtnBase & operator =( const CBtnBase & );

protected:
    HWND    m_hWnd;

public:
    CBtnBase( HINSTANCE hInstance );
    virtual ~CBtnBase();

    static LRESULT CALLBACK WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

    bool CreateControl( HWND hWndParent, WORD wID );
    bool MoveControl( int x, int y, int nWidth, int nHeight );
    void Show( bool bShow );

    virtual void BtnDown( HDC hdc ) = 0;    // ボタンが押されているときの処理
    virtual void BtnPush() = 0;             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc ) = 0;      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc ) = 0;     // ボタンの外にカーソルがあるときの処理
};

typedef CBtnBase    *PCBtnBase;

#endif  // _CBtnBase_
