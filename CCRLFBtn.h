// CCRLFBtn
//  CRLFボタン処理

#ifndef _CCRLFBtn_
#define _CCRLFBtn_

#include "CBtnBase.h"

class CCRLFBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmap;
    BITMAP      m_bitmap;

    CCRLFBtn( const CCRLFBtn & );
    CCRLFBtn & operator =( const CCRLFBtn & );

public:
    CCRLFBtn( HINSTANCE hInstance );
    virtual ~CCRLFBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CCRLFBtn *PCCRLFBtn;

#endif  // _CCRLFBtn_
