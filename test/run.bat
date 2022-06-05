echo off
nasm -f win64 -g out.asm -o out.obj && GoLink /console /mix /entry main msvcr100.dll out.obj && out.exe
echo Return code: %ERRORLEVEL%