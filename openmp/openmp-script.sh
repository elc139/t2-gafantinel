#!/bin/bash
echo '~~~~~~ START ~~~~~~'
for i in $(seq 1 10); do threads=1; for i in $(seq 1 8); do ./ompnew $threads $((1000000/$threads)) 2000 | grep 'thread'; echo ''; threads=$(($threads+1)); done; done
echo '~~~~~~ END ~~~~~~'
echo ''
