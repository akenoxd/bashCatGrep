#!/bin/bash

SUCCESS=0
FAIL=0
DIFF_RES=""

touch test.txt
echo -e "
ghhhg gghh ashd




jea sartre
test1.txt
1 2 3 4 5
asdasdasdasd  asdasdasd
" > test.txt
TEST_FILE="test.txt"

for i in -b -e -n -s -t -v
do
    for j in -b -e -n -s -t -v
    do
          TEST1="$i $j $TEST_FILE"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( SUCCESS++ ))
              echo "$TEST1" PASS
            else
              (( FAIL++ ))
              echo "$TEST1" FAIL
          fi
    done
done
          rm test.txt cat.txt s21_cat.txt

make clean

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"


