REM ����� �ணࠬ�� ��� ��ࠬ��஢
replace.exe
IF NOT ERRORLEVEL 1 GOTO err

REM ����� �ணࠬ�� � ����� ��ࠬ��஬
replace.exe OneParameters
IF NOT ERRORLEVEL 1 GOTO err

REM ����� �ணࠬ�� � ���⮩ ��ப�� � ����⢥ ������ �� ��ࠬ��஢
replace.exe ""
IF NOT ERRORLEVEL 1 GOTO err

REM ����� �ணࠬ�� � ����� ��ࠬ��ࠬ�
replace.exe in.txt out.txt "lol" "kek" "chebyrek"
IF NOT ERRORLEVEL 1 GOTO err

REM ����稩 ��� 1! ����� �ணࠬ�� c ���४�묨 ��ࠬ��ࠬ� � ������
REM �����ப� � 䠩�� in.txt "will  help  the  designer"
REM �� �����ப� "���� ࠡ�稩 ���"
replace.exe in.txt out.txt "will  help  the  designer" "���� ࠡ�稩 ���"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest1.txt
IF ERRORLEVEL 1 GOTO err

REM ����稩 ��� 2! ������ �����ப� "��" �� "����"
replace.exe in.txt out.txt "��" "����"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest2.txt
IF ERRORLEVEL 1 GOTO err

REM ����稩 ��� 3! ������ �����ப� "1231234" ����� "12312312345"
replace.exe in.txt out.txt "1231234" "����⠥� ������ ������ �����ப�"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest3.txt
IF ERRORLEVEL 1 GOTO err


REM ����稩 ��� 4! �᪮��� ��ப� ࠢ�� ���⮩ ��ப�, ������ �� �ந�室��, 䠩�� ����������
replace.exe in.txt out.txt "" "Copy"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest4.txt
IF ERRORLEVEL 1 GOTO err

REM ����稩 ��� 5! ������ � ���� ����讣� 䠩��
replace.exe war.txt out.txt "1) ࠧ���� � �ଥ ᮡ�⢥���� ����: Nicolas" "The END"
IF ERRORLEVEL 1 GOTO err
FC /B out.txt outtest5.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
