@ECHO off
SET nmax=20
SET bmax=12
SET norg=4
SET borg=1
SET n=%norg%
SET /A "a=-1*borg"
SET b=%borg%
SET opt=1
SET np=150
:loop
SET file=n%n%_a%a%_b%b%_np%np%_opt%opt%
inter %n% %a% %b% %np% %opt% %file%.txt
gnuplot -c draw.gp %file%.txt %a% %b% %file%.png "<%a%, %b%>   n = %n%   np = %np%   opt = %opt%"
ECHO %file%
SET /A n+=1
IF %n% LEQ %nmax% GOTO loop
SET /A a-=1
SET /A b+=1
SET /A n=%norg%
IF %b% LEQ %bmax% GOTO loop
IF %opt% EQU 1 GOTO end
SET /A opt=1
SET /A "a=-1*borg"
SET /A b=%borg%
SET /A n=%norg%
GOTO loop
:end