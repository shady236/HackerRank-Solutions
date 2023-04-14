#!/bin/python3

import os
import sys

#
# Complete the xorMatrix function below.
#
 
#define  GET_BIT(x, bit)        (((x)>>(bit)) & 1ULL)

def xorMatrix(m, first_row):
    m = m - 1
    for j in range(63, -1, -1):
        if((m>>j) & 1 == 1):
            intialRow = first_row.copy()
            
            for i in range(0, len(first_row)):
                first_row[i] ^= intialRow[(i + (1<<j)) % len(first_row)];
    return first_row

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    first_row = list(map(int, input().rstrip().split()))

    last_row = xorMatrix(m, first_row)

    fptr.write(' '.join(map(str, last_row)))
    fptr.write('\n')

    fptr.close()
