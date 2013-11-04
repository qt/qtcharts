@echo off

SETLOCAL

set CHARTS_TEMP_DIR=temp_dir
set CHARTS_TEMP_DIR_FULL=..\%CHARTS_TEMP_DIR%

if "%1"=="" (
    echo Usage: generate_package_win version [branch or SHA]
    echo Branch defaults to master.
    echo Creates the package in parent dir.
    echo A temporary dir %CHARTS_TEMP_DIR_FULL% is utilized for intermediate steps.
    goto :end
)

if "%2"=="" (
    set CHARTS_BRANCH=origin/master
) else (
    set CHARTS_BRANCH=%2
)

set CHARTS_VERSION=%1
set CHARTS_BUILD_DIR=%CHARTS_TEMP_DIR_FULL%\tempbuild
set CHARTS_PACKAGE_UNZIP_DIR=%CHARTS_TEMP_DIR_FULL%\qt-charts-enterprise-src-%CHARTS_VERSION%
set CHARTS_TEMP_ZIP=qt-charts-enterprise-src-%CHARTS_VERSION%.zip
set CHARTS_TEMP_ZIP_FULL=%CHARTS_TEMP_DIR_FULL%\%CHARTS_TEMP_ZIP%
set CHARTS_XCOPY_CMD=xcopy /s /i /q
set CHARTS_FINAL_ZIP=..\qt-charts-enterprise-src-%CHARTS_VERSION%.zip

echo Exporting %CHARTS_BRANCH% to %CHARTS_TEMP_ZIP_FULL%...
rmdir /q /s %CHARTS_TEMP_DIR_FULL% 2> NUL
md %CHARTS_TEMP_DIR_FULL% 2> NUL
call git fetch
call git archive --format zip --output ../%CHARTS_TEMP_DIR%/%CHARTS_TEMP_ZIP% %CHARTS_BRANCH%

echo Unzipping %CHARTS_TEMP_ZIP_FULL% to %CHARTS_PACKAGE_UNZIP_DIR% and %CHARTS_BUILD_DIR%...
md %CHARTS_PACKAGE_UNZIP_DIR% 2> NUL
md %CHARTS_BUILD_DIR% 2> NUL
call 7z x -y -o%CHARTS_PACKAGE_UNZIP_DIR% %CHARTS_TEMP_ZIP_FULL%  > NUL
call 7z x -y -o%CHARTS_BUILD_DIR% %CHARTS_TEMP_ZIP_FULL%  > NUL
::Workaround for git archive bug
rmdir /q /s %CHARTS_PACKAGE_UNZIP_DIR%\tests 2> NUL
rmdir /q /s %CHARTS_PACKAGE_UNZIP_DIR%\tools 2> NUL
rmdir /q /s %CHARTS_BUILD_DIR%\tests 2> NUL
rmdir /q /s %CHARTS_BUILD_DIR%\tools 2> NUL

echo Generating includes, mkspecs, and docs in %CHARTS_BUILD_DIR%...
pushd %CHARTS_BUILD_DIR%
::Fake git build to get syncqt to run
md .git 2> NUL
qmake > NUL 2> NUL
nmake docs > NUL 2> NUL
popd

echo Copying generated files to %CHARTS_PACKAGE_UNZIP_DIR%
%CHARTS_XCOPY_CMD% %CHARTS_BUILD_DIR%\doc\qch %CHARTS_PACKAGE_UNZIP_DIR%\doc\qch
%CHARTS_XCOPY_CMD% %CHARTS_BUILD_DIR%\doc\html %CHARTS_PACKAGE_UNZIP_DIR%\doc\html

echo Repackaging %CHARTS_PACKAGE_UNZIP_DIR% to %CHARTS_FINAL_ZIP%
del /q %CHARTS_FINAL_ZIP% 2> NUL
call 7z a -r -y -tzip %CHARTS_FINAL_ZIP% %CHARTS_PACKAGE_UNZIP_DIR% >NUL

:end
