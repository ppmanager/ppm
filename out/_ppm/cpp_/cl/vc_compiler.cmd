@ echo off

set files=%1
set files=%files:"=%

set vcvarsall_path=%2
set vcvarsall_path=%vcvarsall_path:"=%

set bits_version=%3
set bits_version=%bits_version:"=%

set cl_params=%4
set cl_params=%cl_params:"=%

set full_output=%5
set full_output=%full_output:"=%

set link_params=%6
set link_params=%link_params:"=%

call "%vcvarsall_path%" %bits_version%

rem cd D:/Projects/mixed/injection/ZombifyProcess-master/ZombifyProcess-master/ZombieProcess/g
rem cl /GS /analyze- /W3 /Zc:wchar_t /ZI /Gm /Od /Fd"Debug\vc120.pdb" /fp:precise /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /Fp"Debug\ZombieProcess.pch" /I "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include" /I "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include" /I "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib" src/Main.cpp
cl /nologo %cl_params% %files% /link /out:%full_output% %link_params%

