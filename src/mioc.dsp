# Microsoft Developer Studio Project File - Name="mioc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=mioc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mioc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mioc.mak" CFG="mioc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mioc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "mioc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mioc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "bin"
# PROP BASE Intermediate_Dir "bin\mioc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bin"
# PROP Intermediate_Dir "bin\mioc"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GR /O2 /I ".\..\..\lib\vc_lib\msw" /I ".\..\..\include" /I "." /I ".\..\..\samples" /D "WIN32" /D "__WXMSW__" /D "NDEBUG" /D "_WINDOWS" /D "NOPCH" /Fd"bin\mioc.pdb" /FD /EHsc /c
# ADD CPP /nologo /MD /W4 /GR /O2 /I ".\..\..\lib\vc_lib\msw" /I ".\..\..\include" /I "." /I ".\..\..\samples" /D "WIN32" /D "__WXMSW__" /D "NDEBUG" /D "_WINDOWS" /D "NOPCH" /Fd"bin\mioc.pdb" /FD /EHsc /Zm300 /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "NDEBUG" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "NDEBUG" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i ".\..\..\lib\vc_lib\msw" /i ".\..\..\include" /i "." /i ".\..\..\samples" /d "__WXMSW__" /d "NDEBUG" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i ".\..\..\lib\vc_lib\msw" /i ".\..\..\include" /i "." /i ".\..\..\samples" /d "__WXMSW__" /d "NDEBUG" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28_richtext.lib wxmsw28_adv.lib wxmsw28_html.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /machine:I386 /libpath:".\..\..\lib\vc_lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 wxbase28_net.lib wxmsw28_richtext.lib wxmsw28_aui.lib wxmsw28_adv.lib wxmsw28_html.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw28_xrc.lib /nologo /subsystem:windows /machine:I386 /out:"./mioc.exe" /libpath:".\..\..\lib\vc_lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "mioc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "bin_d"
# PROP BASE Intermediate_Dir "bin_d\mioc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "bin_d"
# PROP Intermediate_Dir "bin_d\mioc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I ".\..\..\lib\vc_lib\mswd" /I ".\..\..\include" /I "." /I ".\..\..\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /Fd"bin_d\mioc.pdb" /FD /EHsc /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /Zi /Od /I ".\..\..\lib\vc_lib\mswd" /I ".\..\..\include" /I "." /I ".\..\..\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /Fd"bin_d\mioc.pdb" /FD /EHsc /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i ".\..\..\lib\vc_lib\mswd" /i ".\..\..\include" /i "." /i ".\..\..\samples" /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_WINDOWS" /d "NOPCH"
# ADD RSC /l 0x409 /i ".\..\..\lib\vc_lib\mswd" /i ".\..\..\include" /i "." /i ".\..\..\samples" /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_WINDOWS" /d "NOPCH"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28d_richtext.lib wxmsw28d_adv.lib wxmsw28d_html.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:".\..\..\lib\vc_lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 wxmsw28d_richtext.lib wxmsw28d_adv.lib wxmsw28d_html.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:".\..\..\lib\vc_lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "mioc - Win32 Release"
# Name "mioc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mioc.cpp
# End Source File
# Begin Source File

SOURCE=.\myframe_fb.cpp
# End Source File
# End Group
# End Target
# End Project
