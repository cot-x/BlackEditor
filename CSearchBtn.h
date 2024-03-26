// CSearchBtn
//  SEARCHボタン処理

#ifndef _CSearchBtn_
#define _CSearchBtn_

#include "CBtnBase.h"

class CSearchBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmap;
    BITMAP      m_bitmap;

    CSearchBtn( const CSearchBtn & );
    CSearchBtn & operator =( const CSearchBtn & );

public:
    CSearchBtn( HINSTANCE hInstance );
    virtual ~CSearchBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CSearchBtn *PCSearchBtn;

#endif  // _CSearchBtn_
