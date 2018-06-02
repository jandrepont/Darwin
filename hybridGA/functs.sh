#!/bin/bash


b=2

j="./dist/hybridGA >> results/final/hybf"
#j="foo"; k='$j\>'
for i in {1..30}
do
    if [ "$i" != "$b" ] 
    then 
        k="$j$i.csv"
        echo $k
        eval $k <<EOF &
        0
        $i  
EOF
    fi
    ((number++))

done

exit 0
