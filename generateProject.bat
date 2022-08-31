@echo off
mkdir build
cd build
call cmake .. -G "MinGW Makefiles"
cd ..