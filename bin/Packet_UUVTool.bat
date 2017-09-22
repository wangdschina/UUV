@ECHO off

rem Author: wangds
rem Date :  2017-04

ECHO ---------Simple Pack---------
ECHO.
SET /p "as_ver=请输入版本号: "
ECHO.

SET new_ver_pack=UUVTool_%as_ver%

SET ISCOVER=Y

IF EXIST %new_ver_pack% SET /p ISCOVER=%new_ver_pack%已存在，覆盖吗？(Y/N)

IF NOT EXIST "%new_ver_pack%" MD "%new_ver_pack%"

IF %ISCOVER%==Y (
GOTO COVER
) ELSE (
GOTO MERGE
)

:COVER
ECHO.
ECHO (覆盖模式)
ECHO 正在打包 %new_ver_pack% ...
COPY /Y UUVTool.exe %new_ver_pack% >nul
COPY /Y UUV.dll %new_ver_pack% >nul
COPY /Y PocoFoundation.dll %new_ver_pack% >nul
COPY /Y PocoNet.dll %new_ver_pack% >nul
COPY /Y DuiLib.dll %new_ver_pack% >nul
COPY /Y avcodec-55.dll %new_ver_pack% >nul
COPY /Y avformat-55.dll %new_ver_pack% >nul
COPY /Y avutil-52.dll %new_ver_pack% >nul
COPY /Y swscale-2.dll %new_ver_pack% >nul
COPY /Y opencv_core2413.dll %new_ver_pack% >nul
COPY /Y opencv_imgproc2413.dll %new_ver_pack% >nul
COPY /Y opencv_highgui2413.dll %new_ver_pack% >nul
COPY /Y opencv_objdetect2413.dll %new_ver_pack% >nul
XCOPY /Y Skin\UUVTool %new_ver_pack%\Skin\UUVTool\ /E >nul
XCOPY /Y data %new_ver_pack%\data\ /E >nul
ECHO.
ECHO 打包 %new_ver_pack% 完成
GOTO LOOPEND

:MERGE
ECHO.
ECHO (合并模式)
ECHO.
ECHO 正在拷贝文件至 %new_ver_pack% ...
COPY /-Y:N UUVTool.exe %new_ver_pack% >nul
COPY /-Y:N UUV.dll %new_ver_pack% >nul
COPY /-Y:N PocoFoundation.dll %new_ver_pack% >nul
COPY /-Y:N PocoNet.dll %new_ver_pack% >nul
COPY /-Y:N DuiLib.dll %new_ver_pack% >nul
COPY /-Y:N avcodec-55.dll %new_ver_pack% >nul
COPY /-Y:N avformat-55.dll %new_ver_pack% >nul
COPY /-Y:N avutil-52.dll %new_ver_pack% >nul
COPY /-Y:N swscale-2.dll %new_ver_pack% >nul
COPY /-Y:N opencv_core2413.dll %new_ver_pack% >nul
COPY /-Y:N opencv_imgproc2413.dll %new_ver_pack% >nul
COPY /-Y:N opencv_highgui2413.dll %new_ver_pack% >nul
COPY /-Y:N opencv_objdetect2413.dll %new_ver_pack% >nul
XCOPY /Y Skin\UUVTool %new_ver_pack%\Skin\UUVTool\ /E >nul
XCOPY /Y data %new_ver_pack%\data\ /E >nul
ECHO.
ECHO 已拷贝文件至 %new_ver_pack%
GOTO LOOPEND

:LOOPEND
set ver_gen_info=%new_ver_pack%\VersionGenInfo.txt
echo ------------------->>%ver_gen_info%
echo.>>%ver_gen_info%
echo Version %new_ver_pack% >>%ver_gen_info%
echo Generated at %date% -- %time% >>%ver_gen_info%
echo.>>%ver_gen_info%

ECHO.
ECHO.
ECHO --Pack Done!
ECHO ---------Simple Pack---------
PAUSE
@ECHO on