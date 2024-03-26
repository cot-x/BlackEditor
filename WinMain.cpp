// WinMain
//  エントリーポイント

#include "CMain.h"
#include <new>

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int )
{
    CMain   cmain( hInstance );
    PTSTR   lpFilePath = NULL;
    char    szFilePath[_MAX_PATH+1];
#ifdef UNICODE
    WCHAR   UniFilePath[_MAX_PATH+1];
#endif

    if( *lpCmdLine && strlen(lpCmdLine) <= _MAX_PATH ){
        if( *lpCmdLine == '\"' ){
            strncpy( szFilePath, lpCmdLine+1, strlen(lpCmdLine)-2 );
            szFilePath[strlen(lpCmdLine)-2] = '\0';
        }else{
            strncpy( szFilePath, lpCmdLine, strlen(lpCmdLine) );
            szFilePath[strlen(lpCmdLine)] = '\0';
        }
#ifdef UNICODE
        if( MultiByteToWideChar(CP_ACP, 0, szFilePath, -1, UniFilePath, _MAX_PATH+1) )
            lpFilePath = UniFilePath;
#else
        lpFilePath = szFilePath;
#endif
    }

    return cmain.Run( lpFilePath );
}
