if __name__ == '__main__':
    s = input()
    
    alpanum = False
    alpa    = False
    digit   = False
    lower   = False
    upper   = False
    
    for i in range(0, len(s)):
        if s[i].isalnum():
            alpanum = True
        if s[i].isalpha():
            alpa = True
        if s[i].isdigit():
            digit = True
        if s[i].islower():
            lower = True
        if s[i].isupper():
            upper = True
    
    print(alpanum)
    print(alpa)
    print(digit)
    print(lower)
    print(upper)
