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
char** split_string(char*);

int parse_int(char*);
unsigned long parse_long(char* str);

/*
 * Complete the 'bricksGame' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

unsigned long long min(unsigned long long x, unsigned long long y)
{
    if(x > y)       return y;
    return x;
}

unsigned long long minOfThree(unsigned long long x, unsigned long long y, unsigned long long z)
{
    return min(min(x, y), z);
}

unsigned long long max(unsigned long long x, unsigned long long y)
{
    if(x < y)       return y;
    return x;
}

unsigned long long maxOfThree(unsigned long long x, unsigned long long y, unsigned long long z)
{
    return max(max(x, y), z);
}

unsigned long long bricksGame(int arrSize, unsigned long* arr)
{
    if(arrSize <= 4)
    {
        unsigned long long sumOffirstThree = arr[0];
        for(int i=1; i<arrSize && i<3; i++)
            sumOffirstThree += arr[i];
        return sumOffirstThree;
    }
    
    unsigned long long dp[100004] = {0};
    dp[arrSize - 1] = arr[arrSize - 1];
    dp[arrSize - 2] = arr[arrSize - 1] + arr[arrSize - 2];
    dp[arrSize - 3] = arr[arrSize - 1] + arr[arrSize - 2] + arr[arrSize - 3];
    
    for(int i=arrSize-4; i>=0; i--)
    {
        dp[i] = arr[i] + maxOfThree(
            minOfThree(dp[i+2], dp[i+3], dp[i+4]),
            arr[i+1] + minOfThree(dp[i+3], dp[i+4], dp[i+5]),
            arr[i+1] + arr[i+2] + minOfThree(dp[i+4], dp[i+5], dp[i+6])
        );  
    }
    
    return dp[0];
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int arrSize = parse_int(ltrim(rtrim(readline())));

        char** arr_temp = split_string(rtrim(readline()));

        unsigned long* arr = malloc(arrSize * sizeof(unsigned long));

        for (int i = 0; i < arrSize; i++) {
            unsigned long arr_item = parse_long(*(arr_temp + i));

            *(arr + i) = arr_item;
        }

        unsigned long long result = bricksGame(arrSize, arr);

        fprintf(fptr, "%llu\n", result);
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

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

unsigned long parse_long(char* str) {
    char* endptr;
    unsigned long value = strtoul(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

