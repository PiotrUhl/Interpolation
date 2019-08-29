@echo off
SET n=7
SET a=-3
SET b=3
SET opt=1
SET np=150
SET file=n%n%_a%a%_b%b%_np%np%_opt%opt%
inter %n% %a% %b% %np% %opt% %file%.txt
gnuplot -c draw.gp %file%.txt %a% %b% %file%.png "<%a%, %b%>   n = %n%   np = %np%   opt = %opt%"
echo %file%