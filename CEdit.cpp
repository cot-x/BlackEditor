#include "CEdit.h"
#include "Resource.h"
#include <new>

#define EDIT_CLASSNAME  TEXT("BlackEditor_Edit")

#define TEXTCOLOR   RGB(0xFF,0xFF,0xFF)
#define ID_MAINEDIT 1

// private section //

HHOOK   CEdit::ms_hHook = NULL;
UINT    CEdit::ms_MsgFindReplace;

bool CEdit::_ReadFile( LPCTSTR lpFilePath )
{
    HANDLE  hFile;
    PBYTE   pBuffer, pConv = NULL, pText;
    BYTE    Swap;
    DWORD   dwSize, dwBytesRead;
    int     nUniTest = IS_TEXT_UNICODE_SIGNATURE | IS_TEXT_UNICODE_REVERSE_SIGNATURE;

    hFile = CreateFile( lpFilePath, GENERIC_READ,   // CreateFile[hFile]
        FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL );
    if( hFile == INVALID_HANDLE_VALUE )
        return false;

    dwSize = GetFileSize( hFile, NULL );
    if( dwSize == 0xFFFFFFFF ){
        CloseHandle( hFile );
        return false;
    }
    if( dwSize == 0 ){
        CloseHandle( hFile );
        SetWindowText( m_hEdit, TEXT("") );
        return true;
    }

    pBuffer = new(std::nothrow) BYTE[dwSize+2]; // メモリ確保[pBuffer]
    if( !pBuffer ){
        CloseHandle( hFile );
        return false;
    }

    if( !::ReadFile(hFile, pBuffer, dwSize, &dwBytesRead, NULL) ){
        CloseHandle( hFile );
        delete [] pBuffer;
        return false;
    }
    CloseHandle( hFile );   // CloseHandle[hFile]
    pBuffer[dwBytesRead] = '\0';
    pBuffer[dwBytesRead+1] = '\0';

    IsTextUnicode(pBuffer, dwBytesRead, &nUniTest);
    if( nUniTest & IS_TEXT_UNICODE_REVERSE_SIGNATURE ){
        for( DWORD i=0; i < dwBytesRead/2; i++ ){
            Swap = pBuffer[2*i];
            pBuffer[2*i] = pBuffer[2*i+1];
            pBuffer[2*i+1] = Swap;
        }
        nUniTest = IS_TEXT_UNICODE_SIGNATURE;
        m_bReverse = true;
    }else{
        m_bReverse = false;
    }
    for( DWORD i=0;
            i < ((nUniTest&IS_TEXT_UNICODE_SIGNATURE)?(dwBytesRead-1)/2:dwBytesRead-1); i++ ){
        if( ((nUniTest&IS_TEXT_UNICODE_SIGNATURE)?((PWSTR)pBuffer)[i]:((PSTR)pBuffer)[i])
                == ((nUniTest&IS_TEXT_UNICODE_SIGNATURE)?L'\0':'\0') ){
            delete [] pBuffer;
            return false;
        }
    }
    if( nUniTest & IS_TEXT_UNICODE_SIGNATURE ){
        m_bUnicode = true;
        pText = pBuffer + 2;
        dwBytesRead -= 2;
#ifndef UNICODE
        pConv = new(std::nothrow) BYTE[dwBytesRead+1];    // メモリ確保[pConv]
        if( !pConv ){
            delete [] pBuffer;
            return false;
        }
        if( !WideCharToMultiByte(CP_ACP, 0,
                (PWSTR)pText, -1, (PSTR)pConv, dwBytesRead+1, NULL, NULL) ){
            delete [] pBuffer;
            delete [] pConv;
            return false;
        }
        delete [] pBuffer;  // メモリ開放[pBuffer]
#endif
    }else{
        m_bUnicode = false;
#ifdef UNICODE
        pConv = new(std::nothrow) BYTE[(dwBytesRead+1)*2];    // メモリ確保[pConv]
        if( !pConv ){
            delete [] pBuffer;
            return false;
        }
        if( !MultiByteToWideChar(CP_ACP, 0,
                (PSTR)pBuffer, -1, (PWSTR)pConv, dwBytesRead+1) ){
            delete [] pBuffer;
            delete [] pConv;
            return false;
        }
        delete [] pBuffer;  // メモリ開放[pBuffer]
#else
        pText = pBuffer;
#endif
    }

    if( !pConv ){
        SetWindowText( m_hEdit, (PTSTR)pText );
        delete [] pBuffer;  // メモリ開放[pBuffer]
    }else{
        SetWindowText( m_hEdit, (PTSTR)pConv );
        delete [] pConv;    // メモリ開放[pConv]
    }

    SendMessage( m_hEdit, EM_SETSEL, 0, 0 );

    return true;
}

bool CEdit::_WriteFile( LPCTSTR lpFilePath, bool bUnicode, bool bReverse )
{
    DWORD   dwBytesWritten;
    HANDLE  hFile;
    int     nSize;
    size_t  strLen;
    PBYTE   pBuffer, pConv = NULL, RevBuf;
    BYTE    Swap;
    WORD    wByteOrderMark = 0xFEFF, wReverseByteOrderMark = 0xFFFE;
    BOOL    bRet = TRUE;

    hFile = CreateFile( lpFilePath, GENERIC_WRITE, 0, NULL, // CreateFile[hFile]
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL );
    if( hFile == INVALID_HANDLE_VALUE )
        return false;

    nSize = GetWindowTextLength( m_hEdit );
    nSize++;
#ifdef UNICODE
    nSize <<= 1;
#endif
    pBuffer = new(std::nothrow) BYTE[nSize];   // メモリ確保[pBuffer]
    if( !pBuffer ){
        CloseHandle( hFile );
        return false;
    }

#ifdef UNICODE
    GetWindowText( m_hEdit, (PWSTR)pBuffer, (nSize>>1) );
#else
    GetWindowText( m_hEdit, (PSTR)pBuffer, nSize );
#endif

#ifdef UNICODE
    if( !bUnicode ){
        pConv = new(std::nothrow) BYTE[nSize];    // メモリ確保[pConv]
        if( !pConv ){
            CloseHandle( hFile );
            delete [] pBuffer;
            return false;
        }
        if( !WideCharToMultiByte(CP_ACP, 0,
                (PWSTR)pBuffer, -1, (PSTR)pConv, nSize, NULL, NULL) ){
            CloseHandle( hFile );
            delete [] pBuffer;
            delete [] pConv;
            return false;
        }
        delete [] pBuffer;  // メモリ開放[pBuffer]
    }
#else
    if( bUnicode ){
        pConv = new(std::nothrow) BYTE[nSize<<1];    // メモリ確保[pConv]
        if( !pConv ){
            CloseHandle( hFile );
            delete [] pBuffer;
            return false;
        }
        if( !MultiByteToWideChar(CP_ACP, 0, (PSTR)pBuffer, -1, (PWSTR)pConv, nSize) ){
            CloseHandle( hFile );
            delete [] pBuffer;
            delete [] pConv;
            return false;
        }
        delete [] pBuffer;  // メモリ開放[pBuffer]
    }
#endif

    if( bUnicode ){
        if( !bReverse ){
            ::WriteFile( hFile, &wByteOrderMark, 2, &dwBytesWritten, NULL );
        }else{
#ifdef UNICODE
            RevBuf = pBuffer;
#else
            RevBuf = pConv;
#endif
            for( size_t i=0; i < wcslen((PWSTR)RevBuf); i++ ){
                Swap = RevBuf[2*i];
                RevBuf[2*i] = RevBuf[2*i+1];
                RevBuf[2*i+1] = Swap;
            }
            ::WriteFile( hFile, &wReverseByteOrderMark, 2, &dwBytesWritten, NULL );
        }
        if( dwBytesWritten != 2 ){
            CloseHandle( hFile );
            if( pConv )
                delete [] pConv;
            else
                delete [] pBuffer;
            return false;
        }
    }

#ifdef UNICODE
    if( pConv )
        strLen = strlen( (PSTR)pConv );
    else
        strLen = wcslen( (PWSTR)pBuffer ) * 2;
    ::WriteFile( hFile,
        ((pConv)?pConv:pBuffer), strLen, &dwBytesWritten, NULL );
    if( dwBytesWritten != strLen )
        bRet = FALSE;
#else
    if( pConv )
        strLen = wcslen( (PWSTR)pConv ) * 2;
    else
        strLen = strlen( (PSTR)pBuffer );
    ::WriteFile( hFile,
        ((pConv)?pConv:pBuffer), strLen, &dwBytesWritten, NULL );
    if( dwBytesWritten != strLen )
        bRet = FALSE;
#endif
    CloseHandle( hFile );   // CloseHandle[hFile]
    if( pConv )
        delete [] pConv;    // メモリ開放[pConv]
    else
        delete [] pBuffer;  // メモリ開放[pBuffer]
    if( !bRet )
        return false;

    return true;
}

bool CEdit::_FindText( PTSTR szSearchText, bool bForReplace )
{
    int     nLength;
    DWORD   dwSearchOffset, dwPos;
    PTSTR   pBuffer, pSearched;

    if( !m_hEdit )
        return false;

    nLength = GetWindowTextLength( m_hEdit );
    pBuffer = new(std::nothrow) TCHAR[nLength+1]; // メモリ確保[pBuffer]
    if( !pBuffer ){
        MessageBox( m_hDlgModeless,
            TEXT("メモリ不足により処理を続行することができませんでした。"),
            NULL, MB_ICONERROR );
        return false;
    }
    GetWindowText( m_hEdit, pBuffer, nLength+1 );

    SendMessage( m_hEdit, EM_GETSEL,
        (bForReplace?(WPARAM)&dwSearchOffset:NULL),
        (bForReplace?NULL:(LPARAM)&dwSearchOffset) );

#ifdef UNICODE
    pSearched = wcsstr( pBuffer + dwSearchOffset, szSearchText );
#else
    pSearched = strstr( pBuffer + dwSearchOffset, szSearchText );
#endif
    delete [] pBuffer;  // メモリ開放[pBuffer]

    if( !pSearched )
        return false;

    dwPos = pSearched - pBuffer;

    SendMessage( m_hEdit, EM_SETSEL, dwPos, dwPos + lstrlen(szSearchText) );
    SendMessage( m_hEdit, EM_SCROLLCARET, 0, 0 );

    return true;
}

bool CEdit::_ReplaceText( PTSTR szSearchText, PTSTR szReplaceText )
{
    bool    bReplace = true;
    DWORD   dwPos;

    bReplace = lstrcmp(szSearchText, szReplaceText) != 0;

    if( !_FindText(szSearchText, bReplace) )
        return false;

    SendMessage( m_hEdit, EM_GETSEL, (WPARAM)&dwPos, 0 );
    SendMessage( m_hEdit, EM_REPLACESEL, (WPARAM)TRUE, (LPARAM)szReplaceText );
    SendMessage( m_hEdit, EM_SETSEL, (WPARAM)dwPos, (LPARAM)(dwPos+lstrlen(szReplaceText)) );

    return true;
}


// public section //

CEdit::CEdit( HINSTANCE hInstance, PTSTR szTitle )
:   m_hInstance(hInstance), m_hWnd(NULL), m_hEdit(NULL),
    m_bUpdate(false), m_szTitle(szTitle), m_bReverse(false), m_hDlgModeless(NULL)
{
    m_szFileName[0] = '\0';
    m_szFilePath[0] = '\0';
    m_szOFNFilePath[0] = '\0';
    m_szFindText[0] = '\0';
    m_szReplText[0] = '\0';

#ifdef UNICODE
    m_bUnicode = true;
#else
    m_bUnicode = false;
#endif

    WNDCLASSEX  wc;
    wc.cbSize           = sizeof(wc);
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = CEdit::WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = m_hInstance;
    wc.hIcon            = NULL;
    wc.hCursor          = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground    = CreateSolidBrush( RGB(0,0,0) );
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = EDIT_CLASSNAME;
    wc.hIconSm          = NULL;
    RegisterClassEx( &wc );

    ms_MsgFindReplace = RegisterWindowMessage( FINDMSGSTRING );
}

CEdit::~CEdit()
{
    if( ms_hHook )
        UnhookWindowsHookEx( ms_hHook );
}

// static
LRESULT CALLBACK CEdit::WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    TCHAR           *szTitle, szChanged[] = TEXT("(変更あり)");
    PCEdit          This = (PCEdit)GetWindowLong(hWnd, GWL_USERDATA);
    LPFINDREPLACE   lpfr;
    bool            bRet;

    switch( Msg ){
    case WM_CTLCOLOREDIT:
        SetTextColor( (HDC)wParam, TEXTCOLOR );
        SetBkColor( (HDC)wParam, RGB(0,0,0) );
        return (LRESULT)GetStockObject( BLACK_BRUSH );

    case WM_COMMAND:
        if( LOWORD(wParam) == ID_MAINEDIT ){
            switch( HIWORD(wParam) ){
            case EN_ERRSPACE:
            case EN_MAXTEXT:
                MessageBeep( -1 );
                return 0;

            case EN_UPDATE:
                if( !This->m_bUpdate ){
                    // メモリ確保[szTitle]
                    szTitle = new(std::nothrow) TCHAR[lstrlen(This->m_szTitle)+lstrlen(This->m_szFileName)
                        +lstrlen(szChanged)+4];
                    if( szTitle ){
                        wsprintf( szTitle, TEXT("%s%s - %s"),
                            szChanged, This->m_szFileName, This->m_szTitle );
                        SetWindowText( This->m_hWndParent, szTitle );
                        delete [] szTitle;  // メモリ開放[szTitle]
                    }
                }
                This->m_bUpdate = true;
                return 0;
            }
        }
        return 0;
    }
    if( Msg == ms_MsgFindReplace ){
        lpfr = (LPFINDREPLACE)lParam;

        if( lpfr->Flags & FR_DIALOGTERM && !(lpfr->Flags & FR_FINDNEXT) )
            This->m_hDlgModeless = NULL;

        if( ((lpfr->Flags & FR_FINDNEXT || lpfr->Flags & FR_REPLACE) && This->m_bSearchFirst)
            || lpfr->Flags & FR_REPLACEALL ){
            This->m_bSearchFirst = false;
            SendMessage( This->m_hEdit, EM_SETSEL, 0, 0 );
            SendMessage( This->m_hEdit, EM_SCROLLCARET, 0, 0 );
        }

        if( lpfr->Flags & FR_FINDNEXT )
            if( !This->_FindText(lpfr->lpstrFindWhat) )
                MessageBox( This->m_hDlgModeless,
                    TEXT("検索が終了しました。"), TEXT("検索"), MB_ICONINFORMATION );

        if( lpfr->Flags & FR_REPLACE || lpfr->Flags & FR_REPLACEALL )
            bRet = This->_ReplaceText( lpfr->lpstrFindWhat, lpfr->lpstrReplaceWith );
        if( lpfr->Flags & FR_REPLACEALL )
            while( bRet )
                bRet = This->_ReplaceText( lpfr->lpstrFindWhat, lpfr->lpstrReplaceWith );
        if( !bRet )
            MessageBox( This->m_hDlgModeless,
                    TEXT("置換作業が終了しました。"), TEXT("置換"), MB_ICONINFORMATION );

        return 0;
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );
}

// static
LRESULT CALLBACK CEdit::KeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
    if( nCode < 0 || nCode == HC_NOREMOVE || lParam>>31 & 1 )
        return CallNextHookEx( ms_hHook, nCode, wParam, lParam );

    if( wParam == VK_RETURN ){
        PlaySound( MAKEINTRESOURCE(TYPE_ENTER_WAV),
            GetModuleHandle(NULL), SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
        return 0;
    }else if( (wParam == VK_BACK) || (wParam == VK_DELETE) ){
        PlaySound( MAKEINTRESOURCE(TYPE_DEL_WAV),
            GetModuleHandle(NULL), SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
        return 0;
    }else if( !(wParam==VK_SHIFT || wParam==VK_CONTROL || wParam==VK_MENU ) ){
        PlaySound( MAKEINTRESOURCE(TYPE_WAV),
            GetModuleHandle(NULL), SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
        return 0;
    }

    return CallNextHookEx( ms_hHook, nCode, wParam, lParam );
}

bool CEdit::CreateControl( HWND hWndParent, WORD wID )
{
    static TCHAR
        s_szFilter[] =
            TEXT("テキストファイル (*.txt)\0*.txt\0")
            TEXT("C/C++ ファイル (*.c;*.cpp;*.h;*.hpp;*.rc)\0*.c;*.cpp;*.h;*.hpp;*.rc\0")
            TEXT("アセンブリ ファイル (*.asm)\0*.asm\0")
            TEXT("HTML ファイル (*.html;*.htm)\0*.html;*.htm\0")
            TEXT("すべてのファイル (*.*)\0*.*\0\0"),
        s_szDefExt[] =  TEXT("");

    if( m_hWnd || ms_hHook )
        return false;

    m_hWndParent = hWndParent;

    m_hWnd = CreateWindow( EDIT_CLASSNAME, NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
        0, 0, 0, 0, m_hWndParent, (HMENU)wID, m_hInstance, NULL );
    if( !m_hWnd )
        return false;
    SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this );

    m_hEdit = CreateWindowEx( WS_EX_CLIENTEDGE, TEXT("EDIT"), NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL
        | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LEFT | ES_MULTILINE | ES_NOHIDESEL,
        0, 0, 0, 0, m_hWnd, (HMENU)ID_MAINEDIT, m_hInstance, NULL );
    if( !m_hEdit )
        return false;

    SendMessage( m_hEdit, EM_LIMITTEXT, 0, 0 ); // エディットボックスの限界を最大に
    SendMessage( m_hEdit, WM_SETFONT,
        (WPARAM)GetStockObject(OEM_FIXED_FONT), MAKELPARAM(TRUE, 0) );  // フォント変更

    ms_hHook = SetWindowsHookEx( WH_KEYBOARD,
        CEdit::KeyboardProc, NULL, GetWindowThreadProcessId(m_hEdit, NULL) );

    m_ofn.lStructSize       = sizeof(m_ofn);
    m_ofn.hwndOwner         = m_hWndParent;
    m_ofn.hInstance         = NULL;
    m_ofn.lpstrFilter       = s_szFilter;
    m_ofn.lpstrCustomFilter = NULL;
    m_ofn.nMaxCustFilter    = 0;
    m_ofn.nFilterIndex      = 0;
    m_ofn.lpstrFile         = m_szOFNFilePath;
    m_ofn.nMaxFile          = sizeof(m_szOFNFilePath) / sizeof(TCHAR);
    m_ofn.lpstrFileTitle    = NULL;
    m_ofn.nMaxFileTitle     = 0;
    m_ofn.lpstrInitialDir   = NULL;
    m_ofn.lpstrTitle        = NULL;
    m_ofn.Flags             = 0;    // 各処理時に設定
    m_ofn.nFileOffset       = 0;
    m_ofn.nFileExtension    = 0;
    m_ofn.lpstrDefExt       = s_szDefExt;
    m_ofn.lCustData         = 0L;
    m_ofn.lpfnHook          = NULL;
    m_ofn.lpTemplateName    = NULL;

    m_fr.lStructSize        = sizeof(m_fr);
    m_fr.hwndOwner          = m_hWnd;
    m_fr.hInstance          = NULL;
    m_fr.Flags              = FR_HIDEUPDOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD;
    m_fr.lpstrFindWhat      = m_szFindText;
    m_fr.lpstrReplaceWith   = m_szReplText;
    m_fr.wFindWhatLen       = MAX_FIND_REPLACE_LEN;
    m_fr.wReplaceWithLen    = MAX_FIND_REPLACE_LEN;
    m_fr.lCustData          = 0;
    m_fr.lpfnHook           = NULL;
    m_fr.lpTemplateName     = NULL;

    return true;
}

bool CEdit::MoveControl( int x, int y, int nWidth, int nHeight )
{
    BOOL bRet;

    if( !m_hEdit )
        return false;

    bRet = MoveWindow( m_hWnd, x, y, nWidth, nHeight, FALSE );
    if( !bRet )
        return false;
    bRet = MoveWindow( m_hEdit, 0, 0, nWidth, nHeight, TRUE );
    if( !bRet )
        return false;

    return true;
}

void CEdit::SetFocus()
{
    if( !m_hEdit )
        return;

    ::SetFocus( m_hEdit );
}

// 操作続行可能の場合trueを返す
bool CEdit::CheckUpdate()
{
    int nRet;

    if( m_bUpdate ){
        nRet = MessageBox( m_hWndParent,
            TEXT("内容が変更されています。\r\nファイルを保存しますか？"), m_szFileName,
            MB_YESNOCANCEL | MB_ICONEXCLAMATION | MB_SETFOREGROUND );
        switch( nRet ){
        case IDYES:
            if( !WriteFile() )
                return false;
            return true;
        case IDNO:
            return true;
        case IDCANCEL:
            return false;
        }
    }

    return true;
}

void CEdit::SetUpdate()
{
    if( !m_hEdit )
        return;

    SendMessage( m_hWnd, WM_COMMAND, MAKEWPARAM(ID_MAINEDIT, EN_UPDATE), (LPARAM)m_hEdit );
}

void CEdit::SearchFileName( LPCTSTR lpFilePath )
{
    DWORD n = 0, m;

    while( lpFilePath[n] ){
        if( lpFilePath[n] == '\\' )
            m = n;
        n++;
    }

    if( n-(m+1)+1 > _MAX_FNAME+1 ){
        m_szFileName[0] = '\0';
        return;
    }

    lstrcpyn( m_szFileName, lpFilePath+m+1, n-(m+1)+1 );
}

bool CEdit::IsUnicode()
{
    if( m_bUnicode )
        return true;

    return false;
}

bool CEdit::IsReverse()
{
    if( m_bReverse )
        return true;

    return false;
}

void CEdit::SetUnicode( bool bUnicode, bool bReverse )
{
    if( m_bUnicode = bUnicode )
        m_bReverse = bReverse;
}

bool CEdit::ReadFile( LPCTSTR lpFilePath )
{
    bool    bRet;
    PTSTR   szTitle;

    if( !m_hEdit )
        return false;

    bRet = _ReadFile( lpFilePath );

    if( bRet ){
        lstrcpyn( m_szFilePath, lpFilePath, _MAX_PATH+1 );
        SearchFileName( lpFilePath );
        // メモリ確保[szTitle]
        szTitle = new(std::nothrow) TCHAR[lstrlen(m_szTitle)+lstrlen(m_szFileName)+4];
        if( szTitle ){
            wsprintf( szTitle, TEXT("%s - %s"), m_szFileName, m_szTitle );
            SetWindowText( m_hWndParent, szTitle );
            delete [] szTitle;  // メモリ開放[szTitle]
        }else{
            SetWindowText( m_hWndParent, m_szTitle );
        }
        m_bUpdate = false;
    }

    if( !bRet )
        MessageBox( m_hWndParent,
            TEXT("ファイルの読み込みに失敗しました。"), NULL, MB_ICONERROR );

    return bRet;
}

bool CEdit::WriteFile( LPCTSTR lpFilePath )
{
    bool    bRet, bFilePathNULL = false;
    PTSTR   szTitle;

    if( !m_hEdit )
        return false;

    if( !lpFilePath ){
        if( !*m_szFilePath )
            return SaveFile();
        bFilePathNULL = true;
        lpFilePath = m_szFilePath;
    }

    bRet = _WriteFile( lpFilePath, m_bUnicode, m_bReverse );

    if( bRet ){
        lstrcpyn( m_szFilePath, lpFilePath, _MAX_PATH+1 );
        SearchFileName( lpFilePath );
        // メモリ確保[szTitle]
        szTitle = new(std::nothrow) TCHAR[lstrlen(m_szTitle)+lstrlen(m_szFileName)+4];
        if( szTitle ){
            wsprintf( szTitle, TEXT("%s - %s"), m_szFileName, m_szTitle );
            SetWindowText( m_hWndParent, szTitle );
            delete [] szTitle;  // メモリ開放[szTitle]
        }else{
            SetWindowText( m_hWndParent, m_szTitle );
        }
        m_bUpdate = false;
    }

    if( !bRet && bFilePathNULL )
        return SaveFile();

    if( !bRet )
        MessageBox( m_hWndParent,
            TEXT("ファイルの保存に失敗しました。"), NULL, MB_ICONERROR );

    return bRet;
}

bool CEdit::OpenFile()
{
    if( !m_hEdit )
        return false;

    m_ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

    if( !GetOpenFileName(&m_ofn) )
        return false;

    return ReadFile( m_szOFNFilePath );
}

bool CEdit::SaveFile()
{
    if( !m_hEdit )
        return false;

    m_ofn.Flags = OFN_OVERWRITEPROMPT;

    if( !GetSaveFileName(&m_ofn) )
        return false;

    return WriteFile( m_szOFNFilePath );
}

void CEdit::New()
{
    if( !m_hEdit )
        return;

    SetWindowText( m_hEdit, TEXT("") );

    m_szFileName[0] = '\0';
    m_szFilePath[0] = '\0';
    m_szOFNFilePath[0] = '\0';

    SetWindowText( m_hWndParent, m_szTitle );

    m_bUpdate = false;
}

void CEdit::SelectAll()
{
    if( !m_hEdit )
        return;

    SendMessage( GetFocus(), EM_SETSEL, 0, -1 );
}

void CEdit::Copy()
{
    if( !m_hEdit )
        return;

    SendMessage( GetFocus(), WM_COPY, 0, 0 );
}

void CEdit::Paste()
{
    if( !m_hEdit )
        return;

    SendMessage( GetFocus(), WM_PASTE, 0, 0 );
}

void CEdit::Cut()
{
    if( !m_hEdit )
        return;

    SendMessage( GetFocus(), WM_CUT, 0, 0 );
}

void CEdit::UnDo()
{
    if( !m_hEdit )
        return;

    SendMessage( GetFocus(), WM_UNDO, 0, 0 );
}

bool CEdit::DispatchDlgMsg( PMSG pMsg )
{
    if( m_hDlgModeless && IsDialogMessage(m_hDlgModeless, pMsg) )
        return true;

    return false;
}

void CEdit::FindText()
{
    if( m_hDlgModeless )
        return;

    m_bSearchFirst = true;

    m_hDlgModeless = ::FindText( &m_fr );
}

void CEdit::FindNextText()
{
    int     nLength;
    PTSTR   pBuffer, pSearchText;
    DWORD   dwStart, dwEnd;

    if( !m_hEdit )
        return;

    SendMessage( m_hEdit, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd );
    if( dwStart == dwEnd ){
        MessageBox( m_hWndParent,
            TEXT("検索文字列を選択してください。"), TEXT("検索"), MB_ICONINFORMATION );
        return;
    }

    nLength = GetWindowTextLength( m_hEdit );
    pBuffer = new(std::nothrow) TCHAR[nLength+1]; // メモリ確保[pBuffer]
    if( !pBuffer ){
        MessageBox( m_hWndParent,
            TEXT("メモリ不足により処理を続行することができませんでした。"),
            NULL, MB_ICONERROR );
        return;
    }
    GetWindowText( m_hEdit, pBuffer, nLength+1 );

    pBuffer[dwEnd] = '\0';
    pSearchText = pBuffer+dwStart;

    if( !_FindText(pSearchText) )
        MessageBox( m_hWndParent,
            TEXT("検索が終了しました。"), TEXT("検索"), MB_ICONINFORMATION );

    delete [] pBuffer;  // メモリ開放[pBuffer]
}

void CEdit::ReplaceText()
{
    if( m_hDlgModeless )
        return;

    m_bSearchFirst = true;

    m_hDlgModeless = ::ReplaceText( &m_fr );
}

void CEdit::ChangeCode()
{
    int     nLength;
    PTSTR   pBuffer;
    DWORD   dwPos, dwNum;

    if( !m_hEdit )
        return;

    dwNum = 0;
    nLength = GetWindowTextLength( m_hEdit );
    pBuffer = new(std::nothrow) TCHAR[nLength+1]; // メモリ確保[pBuffer]
    if( !pBuffer ){
        MessageBox( m_hWndParent,
            TEXT("メモリ不足により処理を完了することができませんでした。"),
            NULL, MB_ICONERROR );
        return;
    }
    GetWindowText( m_hEdit, pBuffer, nLength+1 );
    SendMessage( m_hEdit, EM_SETSEL, 0, 0 );
    while( _FindText(TEXT("\n")) ){
        SendMessage( m_hEdit, EM_GETSEL, (WPARAM)&dwPos, 0 );
        if( dwPos == 0 || pBuffer[dwPos-1-dwNum] != *TEXT("\r") ){
            SendMessage( m_hEdit, EM_SETSEL, dwPos, dwPos );
            SendMessage( m_hEdit, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)TEXT("\r") );
            dwNum++;
            SendMessage( m_hEdit, EM_SETSEL, dwPos+2, dwPos+2 );
        }
    }
    delete [] pBuffer;  // メモリ開放[pBuffer]

    dwNum = 0;
    nLength = GetWindowTextLength( m_hEdit );
    pBuffer = new(std::nothrow) TCHAR[nLength+1]; // メモリ確保[pBuffer]
    if( !pBuffer ){
        MessageBox( m_hWndParent,
            TEXT("メモリ不足により処理を完了することができませんでした。"),
            NULL, MB_ICONERROR );
        return;
    }
    GetWindowText( m_hEdit, pBuffer, nLength+1 );
    SendMessage( m_hEdit, EM_SETSEL, 0, 0 );
    SendMessage( m_hEdit, EM_SETSEL, 0, 0 );
    while( _FindText(TEXT("\r")) ){
        SendMessage( m_hEdit, EM_GETSEL, 0, (LPARAM)&dwPos );
        if( pBuffer[dwPos-dwNum] != *TEXT("\n") ){
            SendMessage( m_hEdit, EM_SETSEL, dwPos, dwPos );
            SendMessage( m_hEdit, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)TEXT("\n") );
            dwNum++;
        }
    }
    delete [] pBuffer;  // メモリ開放[pBuffer]

    SendMessage( m_hEdit, EM_SETSEL, 0, 0 );
    SendMessage( m_hEdit, EM_SCROLLCARET, 0, 0 );
    MessageBox( m_hWndParent,
        TEXT("改行コードをすべてWindowsの改行コード(CRLF)に変換しました。"),
        TEXT("改行コード変換"), MB_ICONINFORMATION );
}
