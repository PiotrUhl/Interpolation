set terminal pngcairo;
set output ARG4;
set title ARG5;
plot [ARG2:ARG3][0:] ARG1 using 1:2 title "f(x)" with points pointsize 0.1 linecolor rgb "blue", ARG1 using 1:3 title "Ln(x)" with points pointsize 0.1 linecolor rgb "green", ARG1 using 1:4 title "blad(x)" with points pointsize 0.1 linecolor rgb "red", ARG1 using 5:6 notitle with points pointsize 1.5 pointtype 3 linecolor rgb "black"