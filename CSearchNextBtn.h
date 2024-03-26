// CSearchNextBtn
//  SearchNext�{�^������

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

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CSearchNextBtn *PCSearchNextBtn;

#endif  // _CSearchNextBtn_
