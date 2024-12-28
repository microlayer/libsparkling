SET LIBSPARKLING_HEADER_EXPORT_PATH=export-header
SET INCLUDE_DIR_LIBSPARKLING_ROOT=%LIBSPARKLING_HEADER_EXPORT_PATH%\include
::----------------------------------------------------------------------------------------------------------------
::
::----------------------------------------------------------------------------------------------------------------
:START_COPY_HEADER_FILES
echo [INFO] Start copy header files
xcopy include\*.hpp %INCLUDE_DIR_LIBSPARKLING_ROOT%\spark /S /I /Y
xcopy source\*.hpp %INCLUDE_DIR_LIBSPARKLING_ROOT%\spark /S /I /Y

xcopy lib\box2d\*.h %INCLUDE_DIR_LIBSPARKLING_ROOT%\box2d /S /I /Y
