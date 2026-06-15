#!/bin/bash

if [[ -f ./save/mygif.gif ]]; then
    rm ./save/mygif.gif
fi

file=./save/gif/0.jpg

for (( i = 1; i < 41; i++))
do
    file+=" ./save/gif/"$i".jpg"
done

convert -delay 10 -loop 0  $file ./save/mygif.gif;


