set QTDIR=%1
set PATH=%1\bin;
set PATH=%PATH%;%3
set PATH=%PATH%;%SystemRoot%\System32
set QMAKESPEC=win32-g++
qmake -r charts.pro CONFIG+=%2
@echo on
mingw32-make