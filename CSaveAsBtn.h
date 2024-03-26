// CSaveAsBtn
//  SaveAsボタン処理

#ifndef _CSaveAsBtn_
#define _CSaveAsBtn_

#include "CBtnBase.h"

class CSaveAsBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CSaveAsBtn( const CSaveAsBtn & );
    CSaveAsBtn & operator =( const CSaveAsBtn & );

public:
    CSaveAsBtn( HINSTANCE hInstance );
    virtual ~CSaveAsBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理
};

typedef CSaveAsBtn *PCSaveAsBtn;

#endif  // _CSaveAsBtn_
