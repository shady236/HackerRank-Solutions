#!/bin/python3

import math
import os
import random
import re
import sys


def isKarekar(n):
    nSquare = str(n * n)
    nLen = len(nSquare)
    leftNum = 0
    try:
        leftNum = int(nSquare[0 : nLen//2])
    except:
        pass
    rigthNum = int(nSquare[nLen//2 : ])
    
    return leftNum + rigthNum == n

#
# Complete the 'kaprekarNumbers' function below.
#
# The function accepts following parameters:
#  1. INTEGER p
#  2. INTEGER q
#

def kaprekarNumbers(p, q):
    # Write your code here
    isAnyPrinted = False
    for i in range(p, q + 1):
        if isKarekar(i):
            print(f'{i} ', end='')
            isAnyPrinted = True
    if isAnyPrinted == False:
        print('INVALID RANGE')

if __name__ == '__main__':
    p = int(input().strip())

    q = int(input().strip())

    kaprekarNumbers(p, q)
