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

int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

int maxPalindrome(char* s, int strtIdx, int endIdx, short int (*dp)[3000])
{
    if(strtIdx >= endIdx)
        return strtIdx == endIdx;
    
    if(dp[strtIdx][endIdx] != -1)
        return dp[strtIdx][endIdx];
    
    int res;
    if(s[strtIdx] == s[endIdx])
        res = 2 + maxPalindrome(s, strtIdx + 1, endIdx - 1, dp);
    else 
        res =  max(
            maxPalindrome(s, strtIdx + 1, endIdx, dp),
            maxPalindrome(s, strtIdx, endIdx - 1, dp)
        );
    
    dp[strtIdx][endIdx] = res;
    
    return res;
}


/*
 * Complete the 'playWithWords' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int playWithWords(char* s)
{
    int sLen = strlen(s);
    int maxProduct = 0;
    short int dp[3000][3000];
    
    for(int i = 0; i < 3000; i++)
        for(int j = 0; j < 3000; j++)
            dp[i][j] = -1;
    
    for(int i = 1; s[i + 1]; i++)
    {
        int p = (
            maxPalindrome(s, 0, i, dp) * 
            maxPalindrome(s, i + 1, sLen - 1, dp) 
        );
        
        if(maxProduct < p)
            maxProduct = p;
    }
    
    return maxProduct;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    int result = playWithWords(s);

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
