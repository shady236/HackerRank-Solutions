

# Complete the solve function below.
def solve(s):
    for i in range(0, len(s)):
        if (i==0 or s[i-1] == ' '):
            ss = list(s)
            ss[i] = s[i].capitalize()
            s = ''.join(ss)
    return s
