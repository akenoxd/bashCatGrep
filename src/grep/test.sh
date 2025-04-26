#!/bin/bash

TEST_DIR=tests/

declare -a FLAGS=("-i" "-v" "-l" "-n" "-h" "-s"  "-c"
                  "-iv" "-il" "-in" "-ih" "-is" "-vc"
                  "-vl" "-vn" "-vh" "-vs"
                  "-vh" "-ln" "-cl"
                  "-ivnh" "-ch")

declare -a PATTERNS=("file" "path" "Cxzczx" "123" "fi" "Fi")

declare -a PATTERN_FILES=("./tests/pattern")

TOTAL_TESTS=0
PASSED_TESTS=0

for test_file in "$TEST_DIR"/*
do
    file_name=$(basename "$test_file")
    for flag in "${FLAGS[@]}"
    do
        for pattern in "${PATTERNS[@]}"
        do
            ((TOTAL_TESTS++))
            
            ORIG="grep $flag $pattern $test_file"
            CLONE="./s21_grep $flag $pattern $test_file"
            
            RES1=$(eval $ORIG)
            RES2=$(eval $CLONE)

            TEST_CASE="grep $flag '$pattern' $file_name"
            
            if [ "$RES1" = "$RES2" ]; then
                ((PASSED_TESTS++))
                printf "%-60s %-20s\n" "$TEST_CASE" "PASS"
            else
                printf "%-60s %-20s\n" "$TEST_CASE" "           FAIL"
            fi
        done
    done
done

for test_file in "$TEST_DIR"/*
do
    file_name=$(basename "$test_file")
    for flag in "${FLAGS[@]}"
    do
        for pattern_file in "${PATTERN_FILES[@]}"
        do
            ((TOTAL_TESTS++))
            
            ORIG="grep $flag -f $pattern_file $test_file"
            CLONE="./s21_grep $flag -f $pattern_file $test_file"
            
            RES1=$(eval $ORIG)
            RES2=$(eval $CLONE)

            TEST_CASE="grep $flag -f $pattern_file $file_name"
            
            if [ "$RES1" = "$RES2" ]; then
                ((PASSED_TESTS++))
                printf "%-60s %-20s\n" "$TEST_CASE" "PASS"
            else
                printf "%-60s %-20s\n" "$TEST_CASE" "       FAIL"
            fi
        done
    done
done

printf "\n"
PERCENTAGE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
printf "Total tests: %d | Passed: %d | Failed: %d | Success rate: %d%%\n" \
    $TOTAL_TESTS $PASSED_TESTS $((TOTAL_TESTS - PASSED_TESTS)) $PERCENTAGE