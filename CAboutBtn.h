// CAboutBtn
//  ABOUT�{�^������

#ifndef _CAboutBtn_
#define _CAboutBtn_

#include "CBtnBase.h"

class CAboutBtn : public CBtnBase
{
private:
    PTSTR       m_szAppName, m_szAppVer, m_szAboutTitle, m_szAboutText;
    HBITMAP     m_hBitmapOut;
    BITMAP      m_bitmapOut;
    HBITMAP     m_hBitmapIn;
    BITMAP      m_bitmapIn;
    HBITMAP     m_hBitmapDown;
    BITMAP      m_bitmapDown;

    CAboutBtn( const CAboutBtn & );
    CAboutBtn & operator =( const CAboutBtn & );

public:
    CAboutBtn( HINSTANCE hInstance, PTSTR szAppName, PTSTR szAppVer );
    virtual ~CAboutBtn();

    virtual void BtnDown( HDC hdc );    // �{�^����������Ă���Ƃ��̏���
    virtual void BtnPush();             // �{�^���������ꂽ�Ƃ��̏���
    virtual void BtnIn( HDC hdc );      // �{�^���̏�ɃJ�[�\���������Ƃ��̏���
    virtual void BtnOut( HDC hdc );     // �{�^���̊O�ɃJ�[�\��������Ƃ��̏���
};

typedef CAboutBtn *PCAboutBtn;

#endif  // _CAboutBtn_
