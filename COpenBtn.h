// COpenBtn
//  OPEN�{�^������

#ifndef _COpenBtn_
#define _COpenBtn_

#include "CBtnBase.h"

class COpenBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    COpenBtn( const COpenBtn & );
    COpenBtn & operator =( const COpenBtn & );

public:
    COpenBtn( HINSTANCE hInstance );
    virtual ~COpenBtn();

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef COpenBtn *PCOpenBtn;

#endif  // _COpenBtn_
