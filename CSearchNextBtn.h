// CSearchNextBtn
//  SearchNextボタン処理

#ifndef _CSearchNextBtn_
#define _CSearchNextBtn_

#include "CBtnBase.h"

class CSearchNextBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmap;
    BITMAP      m_bitmap;

    CSearchNextBtn( const CSearchNextBtn & );
    CSearchNextBtn & operator =( const CSearchNextBtn & );

public:
    CSearchNextBtn( HINSTANCE hInstance );
    virtual ~CSearchNextBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CSearchNextBtn *PCSearchNextBtn;

#endif  // _CSearchNextBtn_
