// CReplaceBtn
//  REPLACEボタン処理

#ifndef _CReplaceBtn_
#define _CReplaceBtn_

#include "CBtnBase.h"

class CReplaceBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmap;
    BITMAP      m_bitmap;

    CReplaceBtn( const CReplaceBtn & );
    CReplaceBtn & operator =( const CReplaceBtn & );

public:
    CReplaceBtn( HINSTANCE hInstance );
    virtual ~CReplaceBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CReplaceBtn *PCReplaceBtn;

#endif  // _CReplaceBtn_
