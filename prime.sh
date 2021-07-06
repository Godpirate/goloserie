#!/bin/bash

rm -f myfifo
rm -f prime.txt
make prime
make memo
./memo & ./prime 500
exit 0
