if __name__ == '__main__':
    n = int(input())
    arr = list(map(int, input().split()))
        
    max_ = arr[0]
    for i in arr:
        max_ = max(max_, i)
    
    secondMax = -100
    for i in arr:
        if i < max_:
            secondMax = max(secondMax, i)
    
    print(secondMax)
