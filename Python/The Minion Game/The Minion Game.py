def isVowel(s):
    if(s == 'A'):
        return True
    if(s == 'E'):
        return True
    if(s == 'I'):
        return True
    if(s == 'O'):
        return True
    if(s == 'U'):
        return True
    return False

def minion_game(string):
    # your code goes here
    kevinScore = 0
    stuartScore = 0
    for i in range(len(string)):
        if(isVowel(string[i])):
            kevinScore += len(string) - i
        else:
            stuartScore += len(string) - i
    
    if kevinScore > stuartScore:
        print('Kevin ' + str(kevinScore))
    elif kevinScore < stuartScore:
        print('Stuart ' + str(stuartScore))
    else:
        print('Draw')
    
    

