// CSaveBtn
//  SAVE�{�^������

#ifndef _CSaveBtn_
#define _CSaveBtn_

#include "CBtnBase.h"

class CSaveBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CSaveBtn( const CSaveBtn & );
    CSaveBtn & operator =( const CSaveBtn & );

public:
    CSaveBtn( HINSTANCE hInstance );
    virtual ~CSaveBtn();

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CSaveBtn *PCSaveBtn;

#endif  // _CSaveBtn_
