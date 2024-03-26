// CCRLFBtn
//  CRLF�{�^������

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

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CCRLFBtn *PCCRLFBtn;

#endif  // _CCRLFBtn_
