:: Copy resources
xcopy "..\..\res\*.png" "res\drawable" /I /Y /D
xcopy "..\..\res\*.tmx" "src\main\assets" /I /Y /D
xcopy "..\..\res\*.obj" "src\main\assets" /I /Y /D

:: Build
gradlew.bat 

:: Create APK
gradlew.bat assembleDebug