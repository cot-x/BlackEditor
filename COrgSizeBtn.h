// COrgSizeBtn
//  OrgSizeボタン処理

#ifndef _COrgSizeBtn_
#define _COrgSizeBtn_

#include "CBtnBase.h"

class COrgSizeBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    COrgSizeBtn( const COrgSizeBtn & );
    COrgSizeBtn & operator =( const COrgSizeBtn & );

public:
    COrgSizeBtn( HINSTANCE hInstance );
    virtual ~COrgSizeBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef COrgSizeBtn *PCOrgSizeBtn;

#endif  // _COrgSizeBtn_
