set PROGRAM="%~1"

REM start of the program without parameters
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM start of the program with one parameter
%PROGRAM% OneParameters
IF NOT ERRORLEVEL 1 GOTO err

REM start of the program with an empty line as one of parameters
%PROGRAM% ""
IF NOT ERRORLEVEL 1 GOTO err

REM start of the program with six parameters
%PROGRAM% in.txt "%TEMP%\out.txt" "1231234" "ReplaceNumber" "123"
IF NOT ERRORLEVEL 1 GOTO err

REM replace 1231234 -> ReplaceNumber
%PROGRAM% in.txt "%TEMP%\out.txt" "1231234" "ReplaceNumber"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" outtest1.txt
IF ERRORLEVEL 1 GOTO err

REM replace ma->mama
%PROGRAM% in.txt "%TEMP%\out.txt" "ma" "mama"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" outtest2.txt
IF ERRORLEVEL 1 GOTO err

REM replace brother -> sister
%PROGRAM% in.txt "%TEMP%\out.txt" "brother" "sister"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" outtest3.txt
IF ERRORLEVEL 1 GOTO err

REM replace a->bb
%PROGRAM% in.txt "%TEMP%\out.txt" "a" "bb"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" outtest4.txt
IF ERRORLEVEL 1 GOTO err

REM replace ""->a
%PROGRAM% in.txt "%TEMP%\out.txt" "" "a"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\out.txt" outtest5.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
