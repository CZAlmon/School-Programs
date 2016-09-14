#!/bin/csh
echo "pa1 cs315001s15: d -smoothness..."
echo "------------------"
echo "output expected: 2"
echo "output computed"
./a.out <test2.in
echo "------------------"
echo "output expected: 4"
echo "output computed"
./a.out <test4.in
echo "------------------"
echo "output expected: 5"
echo "output computed"
./a.out <test5.in
echo "------------------"
echo "output expected: 7"
echo "output computed"
./a.out <test7.in
echo "------------------"
echo "output expected: 16"
echo "output computed"
./a.out <test16.in
echo "------------------"
echo "output expected: 19"
echo "output computed"
./a.out <test19.in
echo "------------------"
echo "output expected: 45"
echo "output computed"
./a.out <test45.in
echo "------------------"
echo "output expected: 95"
echo "output computed"
./a.out <test95.in
echo "------------------"
echo "output expected: 103"
echo "output computed"
./a.out <test103.in
echo "------------------"
echo "output expected: 192"
echo "output computed"
./a.out <test192.in
echo "------------------"
echo "output expected: 371"
echo "output computed"
./a.out <test371.in
echo "----END-----------"
