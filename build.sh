#!/bin/bash
flags="*.c -o game "
can=1
play=0
if [[ $# -le 0 ]]; then
    echo -e "\033[1;31mNo flags supplied!\033[0m"
    exit -1
fi
for option in "$@"; do
    case $option in
        -d) if [[ can -eq 1 ]]; then
                flags+="-std=c99 -Wall -pedantic-errors -D_DEBUG_ -lSDL2 -lSDL2_ttf -lSDL2_image -lm"
                can=0
            fi;;
        -r) if [[ can -eq 1 ]]; then
                flags+="-std=c99 -O2 -Wall -pedantic-errors -lSDL2 -lSDL2_ttf -lSDL2_image -lm"
                can=0
           fi;;
        -p) play=1;;
        -entity) flags+=" -D_ENT" ;;
    esac
done 
#pile my cum in your momma
gcc $flags
compiled=$?
if [[ $compiled -eq 1 ]]; then
    echo -e "\033[1;31mCompilation failed!\033[0m"
    exit -1
elif [[ $compiled -eq 0 ]]; then
    echo -e "\033[1;32mCompilation Succeeded!\033[0m"
fi
if [[ $play -eq 1 ]]; then
    ./game
fi
