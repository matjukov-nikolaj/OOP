REM запуск программы без параметров
replace.exe
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с одним параметром
replace.exe OneParameters
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с пустой строкой в качестве одного из параметров
replace.exe ""
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с шестью параметрами
replace.exe in.txt out.txt "lol" "kek" "chebyrek"
IF NOT ERRORLEVEL 1 GOTO err

REM Рабочий тест 1! запуск программы c корректными параметрами и замена
REM подстроки в файле in.txt "will  help  the  designer"
REM на подстроку "Первый рабочий тест"
replace.exe in.txt out.txt "will  help  the  designer" "Первый рабочий тест"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest1.txt
IF ERRORLEVEL 1 GOTO err

REM Рабочий тест 2! замена подстроки "ма" на "мама"
replace.exe in.txt out.txt "ма" "мама"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest2.txt
IF ERRORLEVEL 1 GOTO err

REM Рабочий тест 3! замена подстроки "1231234" внутри "12312312345"
replace.exe in.txt out.txt "1231234" "Работает замена данной подстроки"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest3.txt
IF ERRORLEVEL 1 GOTO err


REM Рабочий тест 4! Искомая строка равна пустой строке, замена не происходит, файлы копируются
replace.exe in.txt out.txt "" "Copy"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest4.txt
IF ERRORLEVEL 1 GOTO err

REM Рабочий тест 5! Замена в конце большого файла
replace.exe war.txt out.txt "1) различия в форме собственных имен: Nicolas" "The END"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest5.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
