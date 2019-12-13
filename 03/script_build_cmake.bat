REM Clining...
call script_clean.bat

REM Configuring..
cmake -G "NMake Makefiles" -B build

REM Building...
cd build
nmake
copy app.exe ..\app.exe

REM Runing...
cd ..
app.exe
pause