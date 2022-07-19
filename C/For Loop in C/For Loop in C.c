#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



int main() 
{
    int a, b;
    scanf("%d\n%d", &a, &b);
  	// Complete the code.
    char num[10][15] = {
        "",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };
    
    int i;
    for(i = a; i <= 9 && i <= b; i++)
    {
        printf("%s\n", num[i]);
    }
    
    for(; i <= b; i++)
    {
        if(i % 2 == 0)        printf("even\n");
        else                  printf("odd\n");
    }
    

    return 0;
}

