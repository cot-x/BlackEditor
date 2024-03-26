// CMinBtn
//  MIN�{�^������

#ifndef _CMinBtn_
#define _CMinBtn_

#include "CBtnBase.h"

class CMinBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CMinBtn( const CMinBtn & );
    CMinBtn & operator =( const CMinBtn & );

public:
    CMinBtn( HINSTANCE hInstance );
    virtual ~CMinBtn();

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CMinBtn *PCMinBtn;

#endif  // _CMinBtn_
