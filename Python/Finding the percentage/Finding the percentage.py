if __name__ == '__main__':
    n = int(input())
    student_marks = {}
    for _ in range(n):
        name, *line = input().split()
        scores = list(map(float, line))
        student_marks[name] = scores
    query_name = input()
    
    sum = 0
    for n in student_marks:
        if query_name == n:
            for s in student_marks[n]:
                sum += s
            print("{:.2f}".format(sum/len(student_marks[n])))
            break
    
