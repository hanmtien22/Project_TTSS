@echo off
rem Build tren Windows (cmd) bang g++ cua MSYS2 UCRT64 + MS-MPI.
rem   build.bat          build tat ca
rem   build.bat clean    xoa bin\ va build\
rem
rem Can co:
rem   - C:\msys64\ucrt64\bin trong PATH (de goi duoc g++)
rem   - MS-MPI: msmpisetup.exe (mpiexec) + msmpisdk.msi (header, lib).
rem     Bo cai SDK tu dat bien MSMPI_INC va MSMPI_LIB64.
rem File *_mpi.cpp va *_hybrid.cpp duoc build kem MPI; neu chua cai
rem MS-MPI thi bo qua cac file nay, cac chuong trinh khac van build.

setlocal enabledelayedexpansion

if /i "%~1"=="clean" (
    if exist bin rmdir /s /q bin
    if exist build rmdir /s /q build
    echo Da xoa bin\ va build\
    exit /b 0
)

if "%CXX%"=="" set "CXX=g++"
set "CXXFLAGS=-O2 -std=c++17 -Wall -Wextra -fopenmp -Iinclude"
set "SIMDFLAGS=-mavx2 -mfma"

where %CXX% >nul 2>nul || (
    echo [loi] Khong tim thay %CXX%. Them C:\msys64\ucrt64\bin vao PATH.
    exit /b 1
)

rem Bo dau \ o cuoi duong dan MS-MPI, neu khong g++ hieu \" la dau nhay.
set "HAVE_MPI=0"
if defined MSMPI_INC if defined MSMPI_LIB64 (
    set "HAVE_MPI=1"
    set "MPI_INC=!MSMPI_INC!"
    set "MPI_LIB=!MSMPI_LIB64!"
    if "!MPI_INC:~-1!"=="\" set "MPI_INC=!MPI_INC:~0,-1!"
    if "!MPI_LIB:~-1!"=="\" set "MPI_LIB=!MPI_LIB:~0,-1!"
)
if "%HAVE_MPI%"=="0" echo [canh bao] Chua thay MS-MPI SDK, bo qua cac ban MPI/Hybrid.

if not exist bin mkdir bin
if not exist build\kernels mkdir build\kernels

rem Kernel nhan khoi: build rieng voi co AVX2/FMA
set "KOBJS="
for %%f in (src\kernels\*.cpp) do (
    echo [kernel] %%~nf
    %CXX% %CXXFLAGS% %SIMDFLAGS% -c %%f -o build\kernels\%%~nf.o || goto :fail
    set "KOBJS=!KOBJS! build\kernels\%%~nf.o"
)

for %%f in (src\dot\*.cpp) do (
    call :build_one "%%f" ""
    if errorlevel 1 goto :fail
)
for %%f in (src\matmul\*.cpp) do (
    call :build_one "%%f" "!KOBJS!"
    if errorlevel 1 goto :fail
)

echo Build xong, chuong trinh nam trong bin\
exit /b 0

rem :build_one <file nguon> <object kem theo>
:build_one
set "NAME=%~n1"
set "IS_MPI=0"
echo %NAME%| findstr /i "_mpi _hybrid" >nul && set "IS_MPI=1"
if "%IS_MPI%"=="1" (
    if "%HAVE_MPI%"=="0" (
        echo [bo qua] %NAME%
        exit /b 0
    )
    echo [mpi] %NAME%
    %CXX% %CXXFLAGS% -I"!MPI_INC!" %1 %~2 -o bin\%NAME%.exe -L"!MPI_LIB!" -lmsmpi
    exit /b !errorlevel!
)
echo [g++] %NAME%
%CXX% %CXXFLAGS% %1 %~2 -o bin\%NAME%.exe
exit /b %errorlevel%

:fail
echo [loi] Build that bai.
exit /b 1
