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
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

int min(int a, int b)
{
    if(a < b)       return a;
    return b;
}

char isThereAWay(char* a, char* b, int n, int aIdx, int bIdx)
{
    char res = 0;
    
    if(bIdx < n && b[bIdx] == '1')
        return isThereAWay(a, b, n, aIdx, bIdx + 1);
    
    if(aIdx < n && a[aIdx] == '1')
        return isThereAWay(a, b, n, aIdx + 1, bIdx);
    
    if(aIdx < n)
    {
        if(aIdx == bIdx || aIdx == bIdx + 1)
        {
            res = isThereAWay(a, b, n, aIdx + 1, bIdx + 1);
        }
        else if(bIdx < n - 1 && b[bIdx + 1] == '0')
        {
            res = isThereAWay(a, b, n, aIdx, bIdx + 2);
        }
        
        if(res)         return 1;
        
        if(aIdx < n-1 && a[aIdx + 1] == '0')
        {
            res = isThereAWay(a, b, n, aIdx + 2, bIdx);
        }
        
        return res;
    }
    
    if(bIdx < n)
    {
        if(bIdx < n-1 && b[bIdx + 1] == '0')
        {
            return isThereAWay(a, b, n, aIdx, bIdx + 2);
        }
        
        return 0;
    }
    
    return 1;
}

/*
 * Complete the 'hexagonalGrid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING a
 *  2. STRING b
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
char* hexagonalGrid(char* a, char* b)
{
    static char res[2][4] = {"NO", "YES"};
    return res[isThereAWay(a, b, strlen(a), 0, 0)];
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char* a = readline();

        char* b = readline();

        char* result = hexagonalGrid(a, b);

        fprintf(fptr, "%s\n", result);
    }

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

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
