// CUnicodeBtn
//  UNICODEボタン処理

#ifndef _CUnicodeBtn_
#define _CUnicodeBtn_

#include "CBtnBase.h"

class CUnicodeBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapAnsi, m_hBitmapUni, m_hBitmapUniRev;
    BITMAP      m_bitmapAnsi, m_bitmapUni, m_bitmapUniRev;
    bool        m_bUnicode, m_bReverse;

    CUnicodeBtn( const CUnicodeBtn & );
    CUnicodeBtn & operator =( const CUnicodeBtn & );

public:
    CUnicodeBtn( HINSTANCE hInstance );
    virtual ~CUnicodeBtn();

    virtual void BtnDown( HDC hdc );    // ボタンが押されているときの処理
    virtual void BtnPush();             // ボタンが押されたときの処理
    virtual void BtnIn( HDC hdc );      // ボタンの上にカーソルが来たときの処理
    virtual void BtnOut( HDC hdc );     // ボタンの外にカーソルがあるときの処理

    void SetUnicode( bool bUnicode, bool bReverse = false );
};

typedef CUnicodeBtn *PCUnicodeBtn;

#endif  // _CUnicodeBtn_
