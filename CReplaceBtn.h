// CReplaceBtn
//  REPLACE�{�^������

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

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CReplaceBtn *PCReplaceBtn;

#endif  // _CReplaceBtn_
