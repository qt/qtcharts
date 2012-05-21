set QTDIR=%1
set PATH=%1\bin;%PATH%;
set QMAKESPEC=win32-msvc2010
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" amd64
@echo on
qmake -r charts.pro CONFIG+=%2
@echo on
nmake
