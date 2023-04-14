

def average(array):
    # your code goes here
    st = set(array)
    sm = 0
    for s in st:
        sm += s
    return (sm / len(st))

