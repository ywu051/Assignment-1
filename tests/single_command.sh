#!/bin/sh
STR1='echo a'
STR2='ls -a'
STR3='echo b;'
STR4='exit'
echo "Single Command Tests"
printf "%s\n%s\n%s\n%s\n%s\n" "Inputs:" "$STR1" "$STR2" "$STR3" "$STR4"

echo "$STR1
$STR2
$STR3
$STR4" | ../bin/rshell

echo " 
Testing Complete"
