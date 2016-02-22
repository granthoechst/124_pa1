#!/bin/bash
echo "prim 0 65536 1 0"
time ./randmst 0 65536 1 0
echo "--"
echo "prim 0 65536 1 2"
time ./randmst 65536 1 2
echo "--"
echo "prim 0 65536 1 3"
time ./randmst 0 65536 1 3
echo "--"
echo "prim 0 65536 1 4"
time ./randmst 0 65536 1 4
