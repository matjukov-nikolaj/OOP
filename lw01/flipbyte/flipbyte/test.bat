set PROGRAM="%~1"

REM start of the program without parameters
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM start of the program with incorrect parameter
%PROGRAM% 123abc > "%TEMP%\out.txt"
IF NOT ERRORLEVEL 1 GOTO err

REM start of the program with negative parameter
%PROGRAM% -2 > "%TEMP%\out.txt"
IF NOT  ERRORLEVEL 1 GOTO err

REM start of the program with very large number
%PROGRAM% 123214312515316564224561145741635784151 > "%TEMP%\out.txt"
IF NOT ERRORLEVEL 1 GOTO err

REM 6 -> 96
%PROGRAM% 6 > "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" test1.txt
IF ERRORLEVEL 1 GOTO err

REM 12 -> 48
%PROGRAM% 12 > "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" test2.txt
IF ERRORLEVEL 1 GOTO err

REM 231 -> 231
%PROGRAM% 231 > "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" test3.txt
IF ERRORLEVEL 1 GOTO err

REM 249 -> 159
%PROGRAM% 249 > "%TEMP%\out.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" test4.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
