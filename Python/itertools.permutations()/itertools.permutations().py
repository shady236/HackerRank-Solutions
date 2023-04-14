# Enter your code here. Read input from STDIN. Print output to STDOUT
from itertools import permutations

s, k = input().split(' ')

lst = list(permutations(s, int(k)))
lst.sort()

for item in lst:
    print(''.join(item))
