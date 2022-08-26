# Enter your code here. Read input from STDIN. Print output to STDOUT

import re

t = int(input())

while t > 0:
    
    s = input()
    
    try:
        re.compile(s)
        print('True')
    except:
        print('False')
    
    t -= 1
