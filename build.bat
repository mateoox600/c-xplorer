@echo off
cd build
call cmake --build .
call c-xplorer.exe
cd ..