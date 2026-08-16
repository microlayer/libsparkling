cls
:: Copy resources
xcopy "..\..\res\*.png" "src\main\assets" /I /Y /D
xcopy "..\..\res\*.tmx" "src\main\assets" /I /Y /D
xcopy "..\..\res\*.obj" "src\main\assets" /I /Y /D
xcopy "..\..\res\*.ply" "src\main\assets" /I /Y /D

::
set GRADLE_OPTS=--enable-native-access=ALL-UNNAMED

:: Build
call gradlew.bat 

:: Create APK
call gradlew.bat assembleDebug

adb -e install jni\build\outputs\apk\debug\libsparkling-debug.apk