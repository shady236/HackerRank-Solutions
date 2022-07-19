#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


void printLine(int lineNumber, int n)
{
    // lines are symetric around line n
    if(lineNumber > n)
        lineNumber = (n<<1) - lineNumber;
    
    int halfLine[1000] = {n};
    int minNumInLine = n - lineNumber + 1;
    for(int i = 1; i < n; i++)
    {
        if(halfLine[i - 1] > minNumInLine)
            halfLine[i] = halfLine[i - 1] - 1;
        else 
            halfLine[i] = halfLine[i - 1];
    }
    
    // characters are symetric around character n
    for(int i = 0; i < n; i++)
        printf("%d ", halfLine[i]);
    
    for(int i = n - 2; i >= 0; i--)
        printf("%d ", halfLine[i]);
    
    printf("\n");
}

void peintPattern(int n) 
{
    int linesCnt = (n<<1) - 1;  // 2n - 1
    for(int lineNum = 1; lineNum <= linesCnt; lineNum++)
    {
        printLine(lineNum, n);
    }
}


int main() 
{

    int n;
    scanf("%d", &n);
  	// Complete the code to print the pattern.
    peintPattern(n);
    return 0;
}
