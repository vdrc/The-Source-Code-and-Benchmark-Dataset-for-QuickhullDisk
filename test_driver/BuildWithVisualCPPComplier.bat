::**********************************************************************************
::** Windows DOS batch file to build an example program using Visual C++ complier **
::**********************************************************************************
if not exist "object" (mkdir "object") 
set SOURCES=TestDriverForQuickhullDisk.cpp ..\implementation\cpp\Circle2D.cpp ..\implementation\cpp\CircularArc2D.cpp ..\implementation\cpp\CircularDisk2D.cpp ..\implementation\cpp\ConvexHullOfDisks.cpp ..\implementation\cpp\FileIOForConvexHullOfDisks.cpp ..\implementation\cpp\GeometricFunction2D.cpp ..\implementation\cpp\Line2D.cpp ..\implementation\cpp\Point2D.cpp ..\implementation\cpp\QuickhullDisk.cpp ..\implementation\cpp\RelativeOperator.cpp ..\implementation\cpp\TimeStatistics.cpp 
set PROGRAM=RunQuickhullDisk.exe
cl /permissive- /std:c++14 /W3 /O2 /Oi /EHsc /I"..\implementation\header" %SOURCES% /link /out:%PROGRAM%

@echo off
for %%i in (*.obj) do move /y %%i object\

pause