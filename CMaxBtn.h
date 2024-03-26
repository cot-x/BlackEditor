// CMaxBtn
//  MAXボタン処理

#ifndef _CMaxBtn_
#define _CMaxBtn_

#include "CBtnBase.h"

class CMaxBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CMaxBtn( const CMaxBtn & );
    CMaxBtn & operator =( const CMaxBtn & );

public:
    CMaxBtn( HINSTANCE hInstance );
    virtual ~CMaxBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CMaxBtn *PCMaxBtn;

#endif  // _CMaxBtn_
