#!/bin/bash 

gcc test.cpp
for (( i = 0; i < 100; i++ )); do
    python gendata.py
    ./a.out < input > myout      
    a=$(diff output myout | wc -l)
    echo "result :"{$a}
    if [[ $a -eq  0 ]]; then echo $i":AC"
    else echo $i":WA";  exit;
    fi
done
   
