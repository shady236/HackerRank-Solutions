

//Complete the following function.

int marks_summation(int* marks, int number_of_students, char gender) {
  //Write your code here.
  
  int sum = 0;
  
  int firstGradeIdx = 0;
  if(gender == 'g')     firstGradeIdx = 1;
  
  for(int i = firstGradeIdx; i < number_of_students; i += 2)
    sum += marks[i];
  
  return sum;
}

