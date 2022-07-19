# Enter your code here. Read input from STDIN. Print output to STDOUT

n = int(input())

while n > 0:
    l = input().split(' ')
    
    try:
        print(int(l[0]) // int(l[1]))
    except Exception as e:
        print("Error Code:", e)
    
    n -= 1
