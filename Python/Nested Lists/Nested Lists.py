if __name__ == '__main__':
    scores = {}
    for _ in range(int(input())):
        name = input()
        score = float(input())
        scores[name] = score
    
    lowest = 999999999
    for n in scores:
        lowest = min(lowest, scores[n])
    
    
    secLowest = 999999999
    for n in scores:
        if scores[n] > lowest:
            secLowest = min(secLowest, scores[n])
    
    names = []
    for n in scores:
        if scores[n] == secLowest:
            names.append(n)
    
    names.sort()
    for n in names:
        print(n)
    
    
