def swap_case(s):
    res = ''
    for char in s:
        if char.isupper():
            res += char.lower()
        elif char.islower():
            res += char.upper()
        else :
            res += char
    return res

