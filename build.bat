@title Build CMake Script
@echo off

if not exist build (
    md build
) 

cd ./build

if not exist vs2019_x86 (
    md vs2019_x86
)

cd ./vs2019_x86

if "%1" == "-r" (
    del CMakeCache.txt
)

cmake -G "Visual Studio 16" -A Win32 ./../../

cd ../..
