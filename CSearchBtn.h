// CSearchBtn
//  SEARCH�{�^������

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

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CSearchBtn *PCSearchBtn;

#endif  // _CSearchBtn_
