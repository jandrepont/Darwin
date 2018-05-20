#!/bin/bash
b=2

j="./dist/binGA >> results/gmem2_16/binf"
#j="foo"; k='$j\>'
for i in {7..10}
do
	n=$((i%5))
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
    #if [ "$n" == 0 ]
    #then
    #    PID=$!
    #    #wait $PID
    #	echo "hello $PID"	
    #fi	
exit 0
