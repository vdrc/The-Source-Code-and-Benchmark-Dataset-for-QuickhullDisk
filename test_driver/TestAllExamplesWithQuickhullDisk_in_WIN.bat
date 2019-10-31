::**********************************************************************
::**     Windows DOS batch file to test 40 examples for QuickhullDisk **
::**********************************************************************
@echo off
echo ------------------------------------------------------------------------------------------
echo --Test 40 examples(RANDOM(10), MIXED(10), ON-BNDRY(10), ON-A-LINE(10)) for QuickhullDisk--
echo ------------------------------------------------------------------------------------------
echo 

if not exist "output" (mkdir "output") 
if not exist "output\RANDOM" (mkdir "output\RANDOM") 
for /L %%i in (10000, 10000, 100000) do (
	echo -----------------------------
	RunQuickhullDisk.exe -i ..\test_data\RANDOM\N%%i.txt -o output\RANDOM\output_N%%i.txt
	echo -----------------------------
)

if not exist "output\MIXED" (mkdir "output\MIXED")
for /L %%i in (10, 10, 100) do (
	echo -----------------------------
	RunQuickhullDisk.exe -i ..\test_data\MIXED\N100000_%%i.txt -o output\MIXED\output_N100000_%%i.txt
	echo -----------------------------
)

if not exist "output\ON-BNDRY" (mkdir "output\ON-BNDRY")
for /L %%i in (10000, 10000, 100000) do (
	echo -----------------------------
	RunQuickhullDisk.exe -i ..\test_data\ON-BNDRY\N%%i.txt -o output\ON-BNDRY\output_N%%i.txt
	echo -----------------------------
)


if not exist "output\ON-A-LINE" (mkdir "output\ON-A-LINE")
for /L %%i in (1000, 1000, 10000) do (
	echo -----------------------------
	RunQuickhullDisk.exe -i ..\test_data\ON-A-LINE\N%%i.txt -o output\ON-A-LINE\output_N%%i.txt
	echo -----------------------------
)

pause