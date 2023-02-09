#!/bin/bash
gcc -c tellbook2.c
gcc -o tb tellbook2.o error.o
./tb $1 $2 $3 $4 $5 $6
# enter filename filesize flag(-r or -w) record_number Person_name Telephone_number
