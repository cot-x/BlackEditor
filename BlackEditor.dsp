# Microsoft Developer Studio Project File - Name="BlackEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BlackEditor - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "BlackEditor.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "BlackEditor.mak" CFG="BlackEditor - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "BlackEditor - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "BlackEditor - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BlackEditor - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comdlg32.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BlackEditor - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comdlg32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BlackEditor - Win32 Release"
# Name "BlackEditor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CAboutBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CBtnBase.cpp
# End Source File
# Begin Source File

SOURCE=.\CCloseBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CCRLFBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\CMain.cpp
# End Source File
# Begin Source File

SOURCE=.\CMaxBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CMinBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CMove.cpp
# End Source File
# Begin Source File

SOURCE=.\CNewBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\COpenBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\COrgSizeBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CReplaceBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CSaveAsBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CSaveBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CSearchBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CSearchNextBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CUnicodeBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CAboutBtn.h
# End Source File
# Begin Source File

SOURCE=.\CBtnBase.h
# End Source File
# Begin Source File

SOURCE=.\CCloseBtn.h
# End Source File
# Begin Source File

SOURCE=.\CCRLFBtn.h
# End Source File
# Begin Source File

SOURCE=.\CEdit.h
# End Source File
# Begin Source File

SOURCE=.\CMain.h
# End Source File
# Begin Source File

SOURCE=.\CMaxBtn.h
# End Source File
# Begin Source File

SOURCE=.\CMinBtn.h
# End Source File
# Begin Source File

SOURCE=.\CMove.h
# End Source File
# Begin Source File

SOURCE=.\CNewBtn.h
# End Source File
# Begin Source File

SOURCE=.\COpenBtn.h
# End Source File
# Begin Source File

SOURCE=.\COrgSizeBtn.h
# End Source File
# Begin Source File

SOURCE=.\CReplaceBtn.h
# End Source File
# Begin Source File

SOURCE=.\CSaveAsBtn.h
# End Source File
# Begin Source File

SOURCE=.\CSaveBtn.h
# End Source File
# Begin Source File

SOURCE=.\CSearchBtn.h
# End Source File
# Begin Source File

SOURCE=.\CSearchNextBtn.h
# End Source File
# Begin Source File

SOURCE=.\CUnicodeBtn.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Resource\BlackEditor.ico
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Resource.rc
# End Source File
# End Group
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# End Target
# End Project
