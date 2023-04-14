#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    
    char a, b[100], c[100];
    scanf("%c %s", &a, b);
    gets(c);
    gets(c);
    printf("%c\n%s\n%s", a, b, c);
    
    return 0;
}
