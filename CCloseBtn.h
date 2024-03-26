// CCloseBtn
//  CLOSE�{�^������

#ifndef _CCloseBtn_
#define _CCloseBtn_

#include "CBtnBase.h"

class CCloseBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CCloseBtn( const CCloseBtn & );
    CCloseBtn & operator =( const CCloseBtn & );

public:
    CCloseBtn( HINSTANCE hInstance );
    virtual ~CCloseBtn();

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CCloseBtn *PCCloseBtn;

#endif  // _CCloseBtn_
