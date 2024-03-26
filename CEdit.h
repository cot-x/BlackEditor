// CEdit
//  EDITコントロールメイン処理クラス
//  インスタンスは一つのみ

#ifndef _CEdit_
#define _CEdit_

#include <windows.h>

#define MAX_FIND_REPLACE_LEN    256

class CEdit
{
private:
    static bool     ms_bClass;
    static UINT     ms_MsgFindReplace;
    bool            m_bUpdate, m_bUnicode, m_bReverse, m_bSearchFirst;
    HINSTANCE       m_hInstance;
    static HHOOK    ms_hHook;
    HWND            m_hWndParent, m_hWnd, m_hEdit, m_hDlgModeless;
    TCHAR           *m_szTitle, m_szFileName[_MAX_FNAME+1], m_szFilePath[_MAX_PATH+1],
                    m_szOFNFilePath[_MAX_PATH+1],
                    m_szFindText[MAX_FIND_REPLACE_LEN+1], m_szReplText[MAX_FIND_REPLACE_LEN+1];
    OPENFILENAME    m_ofn;
    FINDREPLACE     m_fr;

    CEdit( const CEdit & );
    CEdit & operator =( const CEdit & );

    bool _ReadFile( LPCTSTR lpFilePath );
    bool _WriteFile( LPCTSTR lpFilePath, bool bUnicode, bool bReverse );
    bool _FindText( PTSTR szSearchText, bool bForReplace = false );
    bool _ReplaceText( PTSTR szSearchText, PTSTR szReplaceText );

public:
    CEdit( HINSTANCE hInstance, PTSTR szTitle );
    virtual ~CEdit();

    static LRESULT CALLBACK WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
    static LRESULT CALLBACK KeyboardProc( int nCode, WPARAM wParam, LPARAM lParam );

    bool CreateControl( HWND hWndParent, WORD wID );
    bool MoveControl( int x, int y, int nWidth, int nHeight );
    void SetFocus();

    bool CheckUpdate();
    void SetUpdate();
    void SearchFileName( LPCTSTR lpFilePath );
    bool IsUnicode();
    bool IsReverse();
    void SetUnicode( bool bUnicode, bool bReverse = false );
    bool ReadFile( LPCTSTR lpFilePath );
    bool WriteFile( LPCTSTR lpFilePath = NULL );
    bool OpenFile();
    bool SaveFile();
    void New();

    void SelectAll();
    void Copy();
    void Paste();
    void Cut();
    void UnDo();

    bool DispatchDlgMsg( PMSG pMsg );
    void FindText();
    void FindNextText();
    void ReplaceText();
    void ChangeCode();
};

typedef CEdit   *PCEdit;

#endif  // _CEdit_
