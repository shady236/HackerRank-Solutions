#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'changeBits' function below.
#
# The function accepts following parameters:
#  1. STRING a
#  2. STRING b
#  3. STRING_ARRAY queries
#
def setbit(val, i, bit):
    num = 1 << i
    if bit:
        return val | num
    return val & ~num


def changeBits(a, b, queries):
    # Write your code here
    out = ''
    for q in queries:
        cmd = q.split(' ')
        inx = int(cmd[1])
        cmd.append(7)
        bit = int(cmd[2])
        
        if cmd[0] =='set_a':
            a = setbit(a, inx, bit)
        elif cmd[0] =='set_b':
            b = setbit(b, inx, bit)
        else:
            c = a+b
            print((c>>inx) & 1, end='')

if __name__ == '__main__':
    first_multiple_input = input().rstrip().split()

    ab_size = int(first_multiple_input[0])

    queries_size = int(first_multiple_input[1])

    a = int(input(), 2)

    b = int(input(), 2)

    queries = []

    for _ in range(queries_size):
        queries_item = input()
        queries.append(queries_item)
        
    changeBits(a, b, queries)
