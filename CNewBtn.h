// CNewBtn
//  NEWボタン処理

#ifndef _CNewBtn_
#define _CNewBtn_

#include "CBtnBase.h"

class CNewBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CNewBtn( const CNewBtn & );
    CNewBtn & operator =( const CNewBtn & );

public:
    CNewBtn( HINSTANCE hInstance );
    virtual ~CNewBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CNewBtn *PCNewBtn;

#endif  // _CNewBtn_
