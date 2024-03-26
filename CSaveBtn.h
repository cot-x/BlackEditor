// CSaveBtn
//  SAVEボタン処理

#ifndef _CSaveBtn_
#define _CSaveBtn_

#include "CBtnBase.h"

class CSaveBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CSaveBtn( const CSaveBtn & );
    CSaveBtn & operator =( const CSaveBtn & );

public:
    CSaveBtn( HINSTANCE hInstance );
    virtual ~CSaveBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CSaveBtn *PCSaveBtn;

#endif  // _CSaveBtn_
