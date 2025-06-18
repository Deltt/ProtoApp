@echo off
call C:\Users\Michael\emsdk\emsdk_env.bat

rmdir /s /q build_desktop
echo Building desktop...
call cmake -B build_desktop -DTARGET=desktop
echo Configured desktop
call cmake --build build_desktop
echo -------------
echo Built desktop
echo -------------

rmdir /s /q build_web
echo Building web...
call emcmake cmake -G Ninja -B build_web -DTARGET=web
echo Configured web
call cmake --build build_web
echo -------------
echo Built web
echo -------------