@echo off
set URL=https://www.microlayer.org/libsparkling/res.zip
set DOWNLOAD_FOLDER=download
set ZIP_FILE=%DOWNLOAD_FOLDER%/res.zip
set EXTRACT_DIR=.

mkdir %DOWNLOAD_FOLDER%

echo Downloading ZIP file...
powershell -Command "Invoke-WebRequest -Uri \"%URL%\" -OutFile \"%ZIP_FILE%\""

echo Extracting ZIP file...
powershell -Command "Expand-Archive -Path '%ZIP_FILE%' -DestinationPath '%EXTRACT_DIR%' -Force"

echo Done.
pause