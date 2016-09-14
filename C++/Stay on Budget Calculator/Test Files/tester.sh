#!/bin/bash
printf "output expected: 2 + 3 = 5\n"
printf "output computed: "
./a.out < in1
echo 
printf "output expected: 3 + 5 = 8\n"
printf "output computed: "
./a.out < in2
echo
printf "output expected: 1 + 1 = 2\n"
printf "output computed: "
./a.out < in3
echo
printf "output expected: NO\n"
printf "output computed: "
./a.out < in4
echo
printf "output expected: 1000000000 + 1000000000 = 2000000000\n"
printf "output computed: "
./a.out < in5
echo
printf "output expected: 128869808 + 130589082 = 259458890\n"
printf "output computed: "
./a.out < in6
