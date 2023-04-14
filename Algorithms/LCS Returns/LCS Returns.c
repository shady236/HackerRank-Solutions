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

/*
 * Complete the 'tutzkiAndLcs' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING a
 *  2. STRING b
 */

int tutzkiAndLcs(char* a, char* b) 
{
    static int prefixLCS[5001][5001] = {0};
    
    int aLen = strlen(a);
    int bLen = strlen(b);
    
    for(int i = 1; i <= aLen; i++)
    {
        for(int j = 1; j <= bLen; j++)
        {
            if(a[i - 1] == b[j - 1])
                prefixLCS[i][j] = 1 + prefixLCS[i - 1][j - 1];
            else 
                prefixLCS[i][j] = max(prefixLCS[i][j - 1], prefixLCS[i - 1][j]);
        }
    }
    
    
    static int suffixLCS[5001][5001] = {0};
    
    for(int i = aLen - 1; i >= 0; i--)
    {
        for(int j = bLen - 1; j >= 0; j--)
        {
            if(a[i] == b[j])
                suffixLCS[i][j] = 1 + suffixLCS[i + 1][j + 1];
            else 
                suffixLCS[i][j] = max(suffixLCS[i][j + 1], suffixLCS[i + 1][j]);
        }
    }
    
    
    int lcs = suffixLCS[0][0];
    int cnt = 0;
    
    for(int i = 0; i <= aLen; i++)
    {
        char canCharBeInserted['z' + 1] = {0};
        
        for(int j = 0; j < bLen; j++)
        {
            char chr = b[j];
            
            int prefixLcs = prefixLCS[i][j];
            int suffixLcs = suffixLCS[i][j + 1];
            
            int lcsWithChr = 1 + prefixLcs + suffixLcs;
            if(lcsWithChr == lcs + 1)
                canCharBeInserted[chr] = 1;
        }
        
        for(int j = 0; j <= 'z'; j++)
            cnt += canCharBeInserted[j];
    }
    
    return cnt;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* a = readline();

    char* b = readline();

    int result = tutzkiAndLcs(a, b);

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
