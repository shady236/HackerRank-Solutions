#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

/*
 * Complete the 'commonChild' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */

int max(int a, int b)
{
    if(a > b)       return a;
    return b;
}

int solve(char* s1, char* s2, int i1, int i2, int (*dp)[5001])
{
    if(dp[i1][i2] == -1)
    {
        if(s1[i1] == 0 || s2[i2] == 0)
            dp[i1][i2] = 0;
        
        else if(s1[i1] == s2[i2])  
            dp[i1][i2] = 1 + solve(s1, s2, i1 + 1, i2 + 1, dp);
        
        else 
            dp[i1][i2] = max(
                solve(s1, s2, i1 + 1, i2, dp), 
                solve(s1, s2, i1, i2 + 1, dp)
            );
    }
    
    return dp[i1][i2];
}

int commonChild(char* s1, char* s2)
{
    static int dp[5001][5001] = {0};
    for(int i = 0; s1[i]; i++)
    {
        for(int j = 0; s2[j]; j++)
        {
            dp[i][j] = -1;
        }
    }
    
    return solve(s1, s2, 0, 0, dp);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s1 = readline();

    char* s2 = readline();

    int result = commonChild(s1, s2);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}
