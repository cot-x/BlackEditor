// CUnicodeBtn
//  UNICODE�{�^������

#ifndef _CUnicodeBtn_
#define _CUnicodeBtn_

#include "CBtnBase.h"

class CUnicodeBtn : public CBtnBase
{
private:
    HBITMAP     m_hBitmapAnsi, m_hBitmapUni, m_hBitmapUniRev;
    BITMAP      m_bitmapAnsi, m_bitmapUni, m_bitmapUniRev;
    bool        m_bUnicode, m_bReverse;

    CUnicodeBtn( const CUnicodeBtn & );
    CUnicodeBtn & operator =( const CUnicodeBtn & );

public:
    CUnicodeBtn( HINSTANCE hInstance );
    virtual ~CUnicodeBtn();

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���

    void SetUnicode( bool bUnicode, bool bReverse = false );
};

typedef CUnicodeBtn *PCUnicodeBtn;

#endif  // _CUnicodeBtn_
