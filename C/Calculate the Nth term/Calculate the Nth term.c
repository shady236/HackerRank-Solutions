#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.

int find_nth_term(int n, int a, int b, int c) {
  //Write your code here.
  
  switch (n) 
  {
    case 1:
      return a;
    break;
    
    case 2:
      return b;
    break;
    
    case 3:
      return c;
    break;
    
    default:
      return (
        find_nth_term(n - 1, a, b, c) + 
        find_nth_term(n - 2, a, b, c) + 
        find_nth_term(n - 3, a, b, c)
      );
    break;
  }
}

int main() {
    int n, a, b, c;
  
    scanf("%d %d %d %d", &n, &a, &b, &c);
    int ans = find_nth_term(n, a, b, c);
 
    printf("%d", ans); 
    return 0;
}
