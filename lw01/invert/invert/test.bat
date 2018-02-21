set PROGRAM="%~1"

REM start of the program without parameters
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM in4.txt det == 0
%PROGRAM% in4.txt
IF  NOT ERRORLEVEL 1 GOTO err

REM in1.txt -> out.txt
%PROGRAM% in1.txt > "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out1.txt
IF ERRORLEVEL 1 GOTO err

REM in2.txt -> out.txt
%PROGRAM% in2.txt > "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out2.txt
IF ERRORLEVEL 1 GOTO err

REM in3.txt -> out.txt
%PROGRAM% in3.txt > "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out3.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
