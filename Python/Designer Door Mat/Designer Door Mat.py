# Enter your code here. Read input from STDIN. Print output to STDOUT

x = input().split()
n = int(x[0])
m = int(x[1])

# top pattern
cntr = '.|.'
side = '-' * (m//2 - 1)
for i in range(n//2):
    print(side + cntr + side)
    cntr += '.|..|.'
    side = side.replace('---', '', 1)
    
# welcome
print('-' * ((m - len('WELCOME'))//2), end = '') 
print('WELCOME', end='')
print('-' * ((m - len('WELCOME'))//2)) 

# buttom
for i in range(n//2):
    cntr = cntr.replace('.|..|.', '', 1)
    side += '---'
    print(side + cntr + side)
