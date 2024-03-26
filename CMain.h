// CMain
//  MAIN処理、各処理の統率クラス
//  インスタンスは一つのみ

#ifndef _CMain_
#define _CMain_

// 型チェックを厳密に
#define STRICT

#define APPNAME     TEXT("BlackEditor")
#define APPVER      TEXT("Ver.1.2.2")
#define MAIN_WIDTH  800
#define MAIN_HEIGHT 600
#define MARGIN      8
#define BTN_SIZE    64

#include <windows.h>
#include "CEdit.h"
#include "CMove.h"
#include "CNewBtn.h"
#include "COpenBtn.h"
#include "CUnicodeBtn.h"
#include "CSaveBtn.h"
#include "CSaveAsBtn.h"
#include "CMinBtn.h"
#include "CMaxBtn.h"
#include "COrgSizeBtn.h"
#include "CCloseBtn.h"
#include "CAboutBtn.h"
#include "CReplaceBtn.h"
#include "CSearchBtn.h"
#include "CSearchNextBtn.h"
#include "CCRLFBtn.h"

class CMain
{
private:
    static TCHAR    ms_szAppName[], ms_szAppVer[];
    HINSTANCE       m_hInstance;
    LPCTSTR         m_lpFilePath;
    CEdit           m_edit;
    CMove           m_move;
    CNewBtn         m_new;
    COpenBtn        m_open;
    CUnicodeBtn     m_unicode;
    CSaveBtn        m_save;
    CSaveAsBtn      m_saveas;
    CMinBtn         m_min;
    CMaxBtn         m_max;
    COrgSizeBtn     m_orgsize;
    CCloseBtn       m_close;
    CAboutBtn       m_about;
    CReplaceBtn     m_replace;
    CSearchBtn      m_search;
    CSearchNextBtn  m_search_next;
    CCRLFBtn        m_crlf;

    CMain( const CMain & );
    CMain & operator =( const CMain & );

public:
    CMain( HINSTANCE hInstance );
    virtual ~CMain();

    static LRESULT CALLBACK WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

    int Run( LPCTSTR lpFilePath = NULL );
};

typedef CMain   *PCMain;

#endif  // _CMain_
