set QTDIR=%1
set PATH=%1\bin;%PATH%;
set QMAKESPEC=win32-msvc2005
call "C:\Program Files (x86)\Microsoft Visual Studio 8\VC\vcvarsall.bat" x86
@echo on
set INCLUDE=%INCLUDE%;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include
set LIB=%LIB%;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib
qmake -r charts.pro CONFIG+=%2
@echo on
nmake
