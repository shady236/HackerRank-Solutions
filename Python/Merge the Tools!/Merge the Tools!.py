def merge_the_tools(string, k):
    # your code goes here
    for i in range(len(string)//k):
        u = ""
        for j in range(i*k, (i+1)*k):
            if u.find(string[j]) == -1:
                u += string[j]
        print(u)
    

