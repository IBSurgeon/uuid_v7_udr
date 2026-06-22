set ARCH_DIR=C:\Program Files\7-Zip
set OUTPUT_DIR=%1build
set BUILD_DIR=%1build\uuid_v7\windows-x64\Release

del "%OUTPUT_DIR%\UUID_v7_Udr_Win_x64.zip"
"%ARCH_DIR%\7z.exe" a -tzip "%OUTPUT_DIR%\UUID_v7_Udr_Win_x64.zip" "%BUILD_DIR%\uuid_v7.dll" ^
 "%1README.md" "%1README_RU.md" "%1sql"

