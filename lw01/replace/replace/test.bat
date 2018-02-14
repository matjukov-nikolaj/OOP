set PROGRAM="%~1"

REM ����� �ணࠬ�� ��� ��ࠬ��஢
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

REM ����� �ணࠬ�� � ����� ��ࠬ��஬
%PROGRAM% OneParameters
IF NOT ERRORLEVEL 1 GOTO err

REM ����� �ணࠬ�� � ���⮩ ��ப�� � ����⢥ ������ �� ��ࠬ��஢
%PROGRAM% ""
IF NOT ERRORLEVEL 1 GOTO err

REM ����� �ணࠬ�� � ����� ��ࠬ��ࠬ�
%PROGRAM% in.txt out.txt "lol" "kek" "chebyrek"
IF NOT ERRORLEVEL 1 GOTO err

REM ����稩 ��� 1! ����� �ணࠬ�� c ���४�묨 ��ࠬ��ࠬ� � ������
REM �����ப� � 䠩�� in.txt "will  help  the  designer"
REM �� �����ப� "���� ࠡ�稩 ���"
%PROGRAM% in.txt out.txt "will  help  the  designer" "���� ࠡ�稩 ���"
IF ERRORLEVEL 1 GOTO err
FC out.txt outtest1.txt
IF ERRORLEVEL 1 GOTO err

REM ����稩 ��� 2! ������ �����ப� "��" �� "����"
%PROGRAM% in.txt out.txt "��" "����"
IF ERRORLEVEL 1 GOTO err
FC out.txt outtest2.txt
IF ERRORLEVEL 1 GOTO err

REM ����稩 ��� 3! ������ �����ப� "1231234" ����� "12312312345"
%PROGRAM% in.txt out.txt "1231234" "����⠥� ������ ������ �����ப�"
IF ERRORLEVEL 1 GOTO err
FC out.txt outtest3.txt
IF ERRORLEVEL 1 GOTO err


REM ����稩 ��� 4! �᪮��� ��ப� ࠢ�� ���⮩ ��ப�, ������ �� �ந�室��, 䠩�� ����������
%PROGRAM% in.txt out.txt "" "Copy"
IF ERRORLEVEL 1 GOTO err
FC out.txt outtest4.txt
IF ERRORLEVEL 1 GOTO err

REM ����稩 ��� 5! ������ � ���� ����讣� 䠩��
%PROGRAM% war.txt out.txt "1) ࠧ���� � �ଥ ᮡ�⢥���� ����: Nicolas" "The END"
IF ERRORLEVEL 1 GOTO err
FC out.txt outtest5.txt
IF ERRORLEVEL 1 GOTO err

REM ����稩 ��� 5! ������ ������⢥���� �宦����� � ��ப�
%PROGRAM% in1.txt out.txt a bb
IF ERRORLEVEL 1 GOTO err
FC out.txt outtest6.txt
IF ERRORLEVEL 1 GOTO err


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
