set PROGRAM="%~1"

REM start of the program without parameters
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM one parameter
%PROGRAM% in1.txt
IF NOT ERRORLEVEL 1 GOTO err

REM labyrinth 1
%PROGRAM% in1.txt "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out1.txt
IF ERRORLEVEL 1 GOTO err

REM labyrinth 2
%PROGRAM% in2.txt "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out2.txt
IF ERRORLEVEL 1 GOTO err

REM no path
%PROGRAM% in3.txt "%TEMP%\out.txt"
IF NOT ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out3.txt
IF ERRORLEVEL 1 GOTO err

REM no start point
%PROGRAM% in4.txt "%TEMP%\out.txt"
IF NOT ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out4.txt
IF ERRORLEVEL 1 GOTO err

REM a lot of finish points
%PROGRAM% in5.txt "%TEMP%\out.txt"
IF NOT ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out5.txt
IF ERRORLEVEL 1 GOTO err


REM incorrect symbol
%PROGRAM% in6.txt "%TEMP%\out.txt"
IF NOT  ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out6.txt
IF ERRORLEVEL 1 GOTO err


REM big labyrinth
%PROGRAM% in7.txt "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out7.txt
IF ERRORLEVEL 1 GOTO err


REM labyrinth size larger than 100
%PROGRAM% in8.txt "%TEMP%\out.txt"
IF NOT ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" out8.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
