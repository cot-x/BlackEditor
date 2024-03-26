// CMinBtn
//  MINボタン処理

#ifndef _CMinBtn_
#define _CMinBtn_

#include "CBtnBase.h"

class CMinBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CMinBtn( const CMinBtn & );
    CMinBtn & operator =( const CMinBtn & );

public:
    CMinBtn( HINSTANCE hInstance );
    virtual ~CMinBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CMinBtn *PCMinBtn;

#endif  // _CMinBtn_
