REM Building...
cd build
nmake
copy app.exe ..\app.exe
copy test\test.exe ..\test.exe

REM Runing...
cd ..
