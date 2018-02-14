set PROGRAM="%~1"

REM запуск программы без параметров
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы одним  параметром
%PROGRAM% 12
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с некоректным параметром
%PROGRAM% 123abc out.txt
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с отрицательным параметром
%PROGRAM% -2 out.txt
IF NOT  ERRORLEVEL 1 GOTO err

REM запуск программы с очень большим числом
%PROGRAM% 123214312515316564224561145741635784151 out.txt
IF NOT ERRORLEVEL 1 GOTO err

REM Рабочий тест 1
%PROGRAM% 6 out.txt
IF ERRORLEVEL 1 GOTO err
FC /B out.txt test1.txt
IF ERRORLEVEL 1 GOTO err

REM Рабочий тест 2
%PROGRAM% 12 out.txt
IF ERRORLEVEL 1 GOTO err
FC /B out.txt test2.txt
IF ERRORLEVEL 1 GOTO err

REM Рабочий тест 3
%PROGRAM% 231 out.txt
IF ERRORLEVEL 1 GOTO err
FC /B out.txt test3.txt
IF ERRORLEVEL 1 GOTO err

REM Рабочий тест 4
%PROGRAM% 249 out.txt
IF ERRORLEVEL 1 GOTO err
FC /B out.txt test4.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
