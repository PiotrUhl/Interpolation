@echo off
SET nmax=20
SET n=4
SET a=-6
SET b=6
SET opt=0
SET np=150
:loop
SET file=n%n%_a%a%_b%b%_np%np%_opt%opt%
inter %n% %a% %b% %np% %opt% %file%.txt
gnuplot -c draw.gp %file%.txt %file%.png "<%a%, %b%>   n = %n%   np = %np%   opt = %opt%"
echo %file%
SET /A n+=1
IF %n% LEQ %nmax% GOTO loop