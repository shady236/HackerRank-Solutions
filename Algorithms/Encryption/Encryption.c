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
 * Complete the 'encryption' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* encryption(char* s)
{
    int len = 0;
    for(int i = 0; s[i]; i++)
    {
        if(s[i] != ' ')
            len++;
    }
    
    int colsCount = ceil(sqrt(len));
    int rowsCount = floor(sqrt(len));
    
    if((colsCount * rowsCount) < len)
        rowsCount++;
    
    char** arr = malloc(rowsCount * sizeof(char*)); 
    for(int i = 0; i < rowsCount; i++)
    {
        arr[i] = malloc(colsCount * sizeof(char));
        for(int j = 0; j < colsCount; j++)
            arr[i][j] = 0;
    }
    
    for(int i = 0, col = 0, row = 0; s[i]; i++)
    {
        if(s[i] != ' ')
        {
            arr[row][col] = s[i];
            col++;
            if(col >= colsCount)
            {
                col = 0;
                row++;
            }
        }
    }
    
    char* res = malloc((len + colsCount + 1) * sizeof(char));
    res[len + colsCount + 1] = 0;
    res[len + colsCount] = 0;
    
    for(int i = 0, col = 0; col < colsCount; col++)
    {
        for(int row = 0; row < rowsCount; row++)
        {
            if(arr[row][col])
                res[i++] = arr[row][col];
        }
        
        res[i++] = ' ';
    }
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = encryption(s);

    fprintf(fptr, "%s\n", result);

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
