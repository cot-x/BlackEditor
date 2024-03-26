// COrgSizeBtn
//  OrgSize�{�^������

#ifndef _COrgSizeBtn_
#define _COrgSizeBtn_

#include "CBtnBase.h"

class COrgSizeBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    COrgSizeBtn( const COrgSizeBtn & );
    COrgSizeBtn & operator =( const COrgSizeBtn & );

public:
    COrgSizeBtn( HINSTANCE hInstance );
    virtual ~COrgSizeBtn();

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef COrgSizeBtn *PCOrgSizeBtn;

#endif  // _COrgSizeBtn_
