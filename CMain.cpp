#include "CMain.h"
#include "Resource.h"
#include <new>

#define MAIN_CLASSNAME  TEXT("BlackEditor_Main")


// private section //

TCHAR   CMain::ms_szAppName[] = APPNAME;
TCHAR   CMain::ms_szAppVer[] = APPVER;


// public section //

CMain::CMain( HINSTANCE hInstance )
:   m_hInstance(hInstance),
    m_edit(hInstance, ms_szAppName), m_move(hInstance), m_close(hInstance), m_open(hInstance),
    m_unicode(hInstance), m_save(hInstance), m_saveas(hInstance), m_new(hInstance),
    m_min(hInstance), m_max(hInstance), m_orgsize(hInstance),
    m_about(hInstance, ms_szAppName, ms_szAppVer),
    m_replace(hInstance), m_search(hInstance), m_search_next(hInstance), m_crlf(hInstance)
{
}

CMain::~CMain()
{
}

// static
LRESULT CALLBACK CMain::WndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    static PCMain   s_pmain;
    static POINT    s_MinSize;
    static bool     s_bMaximized = false;
    int             nWidth, nHeight;
    UINT            uiRetBufSize;
    HDROP           hDrop;
    PTSTR           lpFilePath;
    RECT            rectClient, rectWindow;
    POINT           point;
    LONG            lFrame;

    switch( Msg ){
    case WM_CREATE:
        s_pmain = (PCMain)((LPCREATESTRUCT)lParam)->lpCreateParams;
        if( !s_pmain->m_edit.CreateControl(hWnd, ID_EDIT) ){
            MessageBox( hWnd,
                TEXT("EDITコントロールの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_move.CreateControl(hWnd, ID_MOVE) ){
            MessageBox( hWnd,
                TEXT("MOVEコントロールの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_close.CreateControl(hWnd, IDB_CLOSE) ){
            MessageBox( hWnd,
                TEXT("CLOSEボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_max.CreateControl(hWnd, IDB_MAX) ){
            MessageBox( hWnd,
                TEXT("MAXボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_orgsize.CreateControl(hWnd, IDB_ORGSIZE) ){
            MessageBox( hWnd,
                TEXT("OrgSizeボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        s_pmain->m_orgsize.Show( false );
        if( !s_pmain->m_min.CreateControl(hWnd, IDB_MIN) ){
            MessageBox( hWnd,
                TEXT("MINボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_about.CreateControl(hWnd, IDB_ABOUT) ){
            MessageBox( hWnd,
                TEXT("ABOUTボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_replace.CreateControl(hWnd, ID_REPLACE) ){
            MessageBox( hWnd,
                TEXT("REPLACEボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_search.CreateControl(hWnd, ID_SEARCH) ){
            MessageBox( hWnd,
                TEXT("SEARCHボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_search_next.CreateControl(hWnd, ID_SEARCH_NEXT) ){
            MessageBox( hWnd,
                TEXT("SearchNextボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_new.CreateControl(hWnd, IDB_NEW) ){
            MessageBox( hWnd,
                TEXT("NEWボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_open.CreateControl(hWnd, IDB_OPEN) ){
            MessageBox( hWnd,
                TEXT("OPENボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_save.CreateControl(hWnd, IDB_SAVE) ){
            MessageBox( hWnd,
                TEXT("SAVEボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_saveas.CreateControl(hWnd, IDB_SAVEAS) ){
            MessageBox( hWnd,
                TEXT("SaveAsボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_unicode.CreateControl(hWnd, IDB_UNICODE) ){
            MessageBox( hWnd,
                TEXT("UNICODEボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( !s_pmain->m_crlf.CreateControl(hWnd, IDB_CRLF) ){
            MessageBox( hWnd,
                TEXT("CRLFボタンの作成に失敗しました。"), NULL, MB_ICONERROR );
            return -1;
        }
        if( s_pmain->m_lpFilePath != NULL )
            s_pmain->m_edit.ReadFile( s_pmain->m_lpFilePath );
        s_pmain->m_unicode.SetUnicode(
            s_pmain->m_edit.IsUnicode(), s_pmain->m_edit.IsReverse() );
        GetClientRect( hWnd, &rectClient );
        GetWindowRect( hWnd, &rectWindow );
        point.y = rectClient.top;
        ClientToScreen( hWnd, &point );
        lFrame = point.y - rectWindow.top;
        s_MinSize.x = lFrame*2+MARGIN*9+BTN_SIZE*10;
        s_MinSize.y = lFrame*2+MARGIN*8+BTN_SIZE*7;
        point.x = MAIN_WIDTH;
        point.y = MAIN_HEIGHT;
        if( (rectWindow.right - rectWindow.left) < s_MinSize.x )
            point.x = s_MinSize.x;
        if( (rectWindow.bottom - rectWindow.top) < s_MinSize.y )
            point.y = s_MinSize.y;
        if( point.x > MAIN_WIDTH || point.y > MAIN_HEIGHT )
            SetWindowPos( hWnd, NULL, 0, 0, point.x, point.y, SWP_NOMOVE | SWP_NOZORDER );

        PlaySound( MAKEINTRESOURCE(START_WAV), GetModuleHandle(NULL),
            SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
        return 0;

    case WM_SIZE:
        if( wParam == SIZE_MINIMIZED )
            return 0;
        if( wParam == SIZE_MAXIMIZED ){
            s_bMaximized = true;
            s_pmain->m_max.Show( false );
            s_pmain->m_orgsize.Show( true );
            s_pmain->m_move.Enable( false );
        }else if( s_bMaximized && wParam == SIZE_RESTORED ){
            s_bMaximized = false;
            s_pmain->m_orgsize.Show( false );
            s_pmain->m_max.Show( true );
            s_pmain->m_move.Enable( true );
        }
        nWidth = LOWORD(lParam);
        nHeight = HIWORD(lParam);
        s_pmain->m_edit.MoveControl( MARGIN, MARGIN,
            nWidth-BTN_SIZE-3*MARGIN, nHeight-BTN_SIZE-3*MARGIN );
        s_pmain->m_move.MoveControl( nWidth-BTN_SIZE-MARGIN,
            nHeight-MARGIN-BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_close.MoveControl( nWidth-2*BTN_SIZE-2*MARGIN,
            nHeight-MARGIN-BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_max.MoveControl( nWidth-3*BTN_SIZE-3*MARGIN,
            nHeight-MARGIN-BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_orgsize.MoveControl( nWidth-3*BTN_SIZE-3*MARGIN,
            nHeight-MARGIN-BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_min.MoveControl( nWidth-4*BTN_SIZE-4*MARGIN,
            nHeight-MARGIN-BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_about.MoveControl( MARGIN,
            nHeight-MARGIN-BTN_SIZE, BTN_SIZE*3, BTN_SIZE );
        s_pmain->m_replace.MoveControl( 3*BTN_SIZE+2*MARGIN,
            nHeight-MARGIN-BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_search.MoveControl( 4*BTN_SIZE+3*MARGIN,
            nHeight-MARGIN-BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_search_next.MoveControl( 5*BTN_SIZE+4*MARGIN,
            nHeight-MARGIN-BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_new.MoveControl( nWidth-BTN_SIZE-MARGIN,
            MARGIN, BTN_SIZE, BTN_SIZE );
        s_pmain->m_open.MoveControl( nWidth-BTN_SIZE-MARGIN,
            2*MARGIN+BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_save.MoveControl( nWidth-BTN_SIZE-MARGIN,
            3*MARGIN+2*BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_saveas.MoveControl( nWidth-BTN_SIZE-MARGIN,
            4*MARGIN+3*BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_unicode.MoveControl( nWidth-BTN_SIZE-MARGIN,
            5*MARGIN+4*BTN_SIZE, BTN_SIZE, BTN_SIZE );
        s_pmain->m_crlf.MoveControl( nWidth-BTN_SIZE-MARGIN,
            6*MARGIN+5*BTN_SIZE, BTN_SIZE, BTN_SIZE );
        return 0;

    case WM_COMMAND:
        switch( LOWORD(wParam) ){
        case IDB_CLOSE:
            SendMessage( hWnd, WM_CLOSE, 0, 0 );
            return 0;

        case IDB_MAX:
            ShowWindow( hWnd, SW_MAXIMIZE );
            s_pmain->m_max.Show( false );
            s_pmain->m_orgsize.Show( true );
            s_pmain->m_move.Enable( false );
            return 0;

        case IDB_ORGSIZE:
            ShowWindow( hWnd, SW_SHOWNORMAL );
            s_pmain->m_orgsize.Show( false );
            s_pmain->m_max.Show( true );
            s_pmain->m_move.Enable( true );
            return 0;

        case IDB_MIN:
            ShowWindow( hWnd, SW_MINIMIZE );
            return 0;

        case IDB_NEW:
            if( !s_pmain->m_edit.CheckUpdate() )
                return 0;
            PlaySound( MAKEINTRESOURCE(NEW_WAV), GetModuleHandle(NULL),
                SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
            s_pmain->m_edit.New();
            return 0;

        case IDB_OPEN:
            if( !s_pmain->m_edit.CheckUpdate() )
                return 0;
            if( s_pmain->m_edit.OpenFile() )
                PlaySound( MAKEINTRESOURCE(OPEN_WAV), GetModuleHandle(NULL),
                    SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
            s_pmain->m_unicode.SetUnicode(
                s_pmain->m_edit.IsUnicode(), s_pmain->m_edit.IsReverse() );
            return 0;

        case IDB_SAVE:
            if( s_pmain->m_edit.WriteFile() )
                PlaySound( MAKEINTRESOURCE(SAVE_WAV), GetModuleHandle(NULL),
                    SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
            return 0;

        case IDB_SAVEAS:
            if( s_pmain->m_edit.SaveFile() )
                PlaySound( MAKEINTRESOURCE(SAVE_WAV), GetModuleHandle(NULL),
                    SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
            return 0;

        case IDB_UNICODE:
            // …->ANSI->Unicode->ReverseUnicode->ANSI->…
            if( !s_pmain->m_edit.IsUnicode() ){
                s_pmain->m_edit.SetUnicode( true, false );
                s_pmain->m_unicode.SetUnicode( true, false );
            }else{
                if( !s_pmain->m_edit.IsReverse() ){
                    s_pmain->m_edit.SetUnicode( true, true );
                    s_pmain->m_unicode.SetUnicode( true, true );
                }else{
                    s_pmain->m_edit.SetUnicode( false );
                    s_pmain->m_unicode.SetUnicode( false );
                }
            }
            s_pmain->m_edit.SetUpdate();
            return 0;

        case IDB_CRLF:
            s_pmain->m_edit.ChangeCode();
            return 0;

        case ID_EDIT_SELECT_ALL:
            s_pmain->m_edit.SelectAll();
            return 0;

        case ID_EDIT_COPY:
            s_pmain->m_edit.Copy();
            return 0;

        case ID_EDIT_PASTE:
            s_pmain->m_edit.Paste();
            return 0;

        case ID_EDIT_CUT:
            s_pmain->m_edit.Cut();
            return 0;

        case ID_EDIT_UNDO:
            s_pmain->m_edit.UnDo();
            return 0;

        case ID_SEARCH:
            s_pmain->m_edit.FindText();
            return 0;

        case ID_SEARCH_NEXT:
            s_pmain->m_edit.FindNextText();
            return 0;

        case ID_REPLACE:
            s_pmain->m_edit.ReplaceText();
            return 0;
        }
        return 0;

    case WM_DROPFILES:
        hDrop = (HDROP)wParam;
        if( !s_pmain->m_edit.CheckUpdate() ){
            DragFinish( hDrop );
            return 0;
        }
        uiRetBufSize = DragQueryFile( hDrop, 0, NULL, 0 );
        lpFilePath = new(std::nothrow) TCHAR[uiRetBufSize+1];
        DragQueryFile( hDrop, 0, lpFilePath, uiRetBufSize+1 );
        if( s_pmain->m_edit.ReadFile(lpFilePath) )
            PlaySound( MAKEINTRESOURCE(OPEN_WAV), GetModuleHandle(NULL),
                SND_ASYNC | SND_NODEFAULT | SND_NOWAIT | SND_RESOURCE );
        if( lpFilePath )
            delete [] lpFilePath;
        DragFinish( hDrop );
        s_pmain->m_unicode.SetUnicode(
            s_pmain->m_edit.IsUnicode(), s_pmain->m_edit.IsReverse() );
        return 0;

    case WM_SETFOCUS:
        s_pmain->m_edit.SetFocus();
        return 0;

    case WM_SIZING:
        point.x = ((PRECT)lParam)->right - ((PRECT)lParam)->left;
        point.y = ((PRECT)lParam)->bottom - ((PRECT)lParam)->top;
        if( point.x < s_MinSize.x ){
            if( wParam == WMSZ_BOTTOMLEFT || wParam == WMSZ_LEFT || wParam == WMSZ_TOPLEFT )
                ((PRECT)lParam)->left -= s_MinSize.x - point.x;
            else
                ((PRECT)lParam)->right += s_MinSize.x - point.x;
        }
        if( point.y < s_MinSize.y ){
            if( wParam == WMSZ_TOP || wParam == WMSZ_TOPLEFT || wParam == WMSZ_TOPRIGHT )
                ((PRECT)lParam)->top -= s_MinSize.y - point.y;
            else
                ((PRECT)lParam)->bottom += s_MinSize.y - point.y;
        }
        return TRUE;

    case WM_CLOSE:
        if( !s_pmain->m_edit.CheckUpdate() )
            return 0;
        break;

    case WM_QUERYENDSESSION:
        return (s_pmain->m_edit.CheckUpdate()?TRUE:FALSE);

    case WM_DESTROY:
        PostQuitMessage( 1 );
        return 0;
    }
    return DefWindowProc( hWnd, Msg, wParam, lParam );
}

int CMain::Run( LPCTSTR lpFilePath )
{
    MSG     msg;
    BOOL    bmsg;
    HWND    hWnd;
    HDC     hIdc;
    HACCEL  hAccel;

    m_lpFilePath = lpFilePath;

    hIdc = CreateIC( TEXT("DISPLAY"), NULL, NULL, NULL );
    if( !(GetDeviceCaps(hIdc, RASTERCAPS) & RC_STRETCHBLT) ){
        MessageBox( NULL,
            TEXT("StretchBltをサポートしていないため実行できません。"), NULL, MB_ICONERROR );
        return 0;
    }
    DeleteDC( hIdc );

    WNDCLASSEX  wc;
    wc.cbSize           = sizeof(wc);
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = CMain::WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = m_hInstance;
    wc.hIcon            = LoadIcon( m_hInstance, MAKEINTRESOURCE(MAIN_ICON) );
    wc.hCursor          = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground    = CreateSolidBrush( RGB(0,0,0) );
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = MAIN_CLASSNAME;
    wc.hIconSm          = NULL;
    RegisterClassEx( &wc );

    hWnd = CreateWindowEx( WS_EX_ACCEPTFILES | WS_EX_OVERLAPPEDWINDOW,
        MAIN_CLASSNAME, ms_szAppName, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WIDTH,
        MAIN_HEIGHT + GetSystemMetrics(SM_CYCAPTION), NULL, NULL, m_hInstance, this );
    if( !hWnd ){
        MessageBox( NULL, TEXT("ウィンドウの作成に失敗しました。"), NULL, MB_ICONERROR );
        return 0;
    }
    SetWindowLong( hWnd, GWL_STYLE, (WS_OVERLAPPEDWINDOW & ~WS_CAPTION) | WS_BORDER );
    SetWindowPos( hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED
        | SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW );

    hAccel = LoadAccelerators( m_hInstance, MAKEINTRESOURCE(ACCELERATOR) );

    while( (bmsg = GetMessage(&msg, NULL, 0, 0)) != 0 ){
        if( bmsg == -1 ){
            MessageBox( NULL,
                TEXT("メッセージループでエラーが発生しました。"), NULL, MB_ICONERROR );
            DestroyWindow( hWnd );
            return -1;
        }
        if( m_edit.DispatchDlgMsg(&msg) )
            continue;
        if( TranslateAccelerator(hWnd, hAccel, &msg) )
            continue;
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
    return msg.wParam;
}
