#!/bin/sh
STR1='echo a; echo b; echo c; exit'
STR2='ls -a; echo b || echo c && exit'
STR3='echo b && echo l && echo a; exit'
STR4='echo a; echo b && echo c || exit; echo d'
STR5='exit'
echo "Multiple Command Tests"
printf "%s\n%s\n%s\n%s\n%s\n" "Inputs:" "$STR1" "$STR2" "$STR3" "$STR4" "$STR5"

echo "$STR1" | ../bin/rshell
echo exited
echo "$STR2" | ../bin/rshell
echo exited 
echo "$STR3" | ../bin/rshell
echo exited
echo "$STR4
$STR5" | ../bin/rshell
echo exited
echo " 
Testing Complete"
