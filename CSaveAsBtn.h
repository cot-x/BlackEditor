// CSaveAsBtn
//  SaveAs�{�^������

#ifndef _CSaveAsBtn_
#define _CSaveAsBtn_

#include "CBtnBase.h"

class CSaveAsBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CSaveAsBtn( const CSaveAsBtn & );
    CSaveAsBtn & operator =( const CSaveAsBtn & );

public:
    CSaveAsBtn( HINSTANCE hInstance );
    virtual ~CSaveAsBtn();

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CSaveAsBtn *PCSaveAsBtn;

#endif  // _CSaveAsBtn_
