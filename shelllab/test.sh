#!/bin/bash
# JangHo Seo <jangho.se@snu.ac.kr>

for i in {1..16}
do
    if [ $i -lt 10 ]
    then
        j='0'$i;
    else
        j=$i;
    fi
    printf "test ${j}: "
    echo "------------$j------------" >> my
    echo "------------$j------------" >> ref
    printf "(ref..."
    make rtest$j >> ref
    printf ", my..."
    make test$j >> my
    echo ") done!"
done
