// CNewBtn
//  NEW�{�^������

#ifndef _CNewBtn_
#define _CNewBtn_

#include "CBtnBase.h"

class CNewBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CNewBtn( const CNewBtn & );
    CNewBtn & operator =( const CNewBtn & );

public:
    CNewBtn( HINSTANCE hInstance );
    virtual ~CNewBtn();

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CNewBtn *PCNewBtn;

#endif  // _CNewBtn_
