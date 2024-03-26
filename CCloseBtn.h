// CCloseBtn
//  CLOSEボタン処理

#ifndef _CCloseBtn_
#define _CCloseBtn_

#include "CBtnBase.h"

class CCloseBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CCloseBtn( const CCloseBtn & );
    CCloseBtn & operator =( const CCloseBtn & );

public:
    CCloseBtn( HINSTANCE hInstance );
    virtual ~CCloseBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CCloseBtn *PCCloseBtn;

#endif  // _CCloseBtn_
