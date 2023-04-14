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

/*
 * Complete the 'candies' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER_ARRAY arr
 */

int max(int a, int b)
{
    if(a > b)       return a;
    return b;
}

long candies(int n, int arr_count, int* arr) 
{
    if(n == 1)      return 1;
    
    int minBefore[100001] = {0};
    int minAfter [100001] = {0};
    
    minAfter[0] = 0;
    for(int i=0; i<arr_count-1; i++)
        if(arr[i] > arr[i+1])
            minAfter[0]++;
        else 
            break;
    
    for(int i=1; i<arr_count; i++)
    {
        if(arr[i] > arr[i-1])
        {
            minBefore[i] = minBefore[i-1] + 1;
            
            minAfter[i] = 0;
            for(int j=i; j<arr_count-1; j++)
                if(arr[j] > arr[j+1])
                    minAfter[i]++;
                else 
                    break;
        }
        else if(arr[i] == arr[i-1])
        {
            minBefore[i] = 0;
            
            minAfter[i] = 0;
            for(int j=i; j<arr_count-1; j++)
                if(arr[j] > arr[j+1])
                    minAfter[i]++;
                else 
                    break;
        }
        else
        { 
            minBefore[i] = 0;
            minAfter [i] = minAfter[i-1] - 1;
        }
    }
    
    long count = arr_count;
    for(int i=0; i<arr_count; i++)
        count += max(minAfter[i], minBefore[i]);
    
    return count;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(ltrim(rtrim(readline())));

        *(arr + i) = arr_item;
    }

    long result = candies(n, n, arr);

    fprintf(fptr, "%ld\n", result);

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
