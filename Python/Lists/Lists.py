if __name__ == '__main__':
    N = int(input())
    lst = []
    while N > 0:
        cmd = input().split(' ')
        if (cmd[0].startswith('insert')):
            lst.insert(int(cmd[1]), int(cmd[2]))
        elif (cmd[0].startswith('print')):
            print(lst)
        elif (cmd[0].startswith('remove')):
            lst.remove(int(cmd[1]))
        elif (cmd[0].startswith('append')):
            lst.append(int(cmd[1]))
        elif (cmd[0].startswith('sort')):
            lst.sort()
        elif (cmd[0].startswith('pop')):
            lst.pop()
        elif (cmd[0].startswith('reverse')):
            lst.reverse()
        
        N = N - 1
