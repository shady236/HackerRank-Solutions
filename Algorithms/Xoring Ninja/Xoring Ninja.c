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

#define  MOD    (1000000007)
#define  GET_BIT(x, bit)        (((x)>>(bit)) & 1)

unsigned long long powerOf2(int pow)
{
    if(pow == 0)
        return 1;
    if(pow == 1)
        return 2;
    
    int pow1 = pow>>1;
    int pow2 = pow - pow1;
    
    unsigned long long half1 = powerOf2(pow1);
    unsigned long long half2 = powerOf2(pow1);
    if(pow1 != pow2)
        half2 = half2<<1;
    
    return (half1 * half2) % MOD;
}


/*
 * Complete the 'xoringNinja' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int xoringNinja(int arr_count, int* arr) 
{
    unsigned long long res = 0;
    
    for(int bit = 0; bit < 32; bit++)
    {
        int onesCnt = 0;
        for(int i = 0; i < arr_count; i++)
        {
            onesCnt += GET_BIT(arr[i], bit);
        }
        
        if(onesCnt == 0)
            continue;
        
        int zerosCnt = arr_count - onesCnt;
        
        unsigned long long x = powerOf2(onesCnt - 1);
        x *= powerOf2(zerosCnt);
        x %= MOD;
        x *= 1<<bit;
        x %= MOD;
        
        res += x;
        res %= MOD;
    }
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int arr_count = parse_int(ltrim(rtrim(readline())));

        char** arr_temp = split_string(rtrim(readline()));

        int* arr = malloc(arr_count * sizeof(int));

        for (int i = 0; i < arr_count; i++) {
            int arr_item = parse_int(*(arr_temp + i));

            *(arr + i) = arr_item;
        }

        int result = xoringNinja(arr_count, arr);

        fprintf(fptr, "%d\n", result);
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
