// COpenBtn
//  OPENボタン処理

#ifndef _COpenBtn_
#define _COpenBtn_

#include "CBtnBase.h"

class COpenBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    COpenBtn( const COpenBtn & );
    COpenBtn & operator =( const COpenBtn & );

public:
    COpenBtn( HINSTANCE hInstance );
    virtual ~COpenBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef COpenBtn *PCOpenBtn;

#endif  // _COpenBtn_
