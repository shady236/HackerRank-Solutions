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


#define  MOD        (1000000007ULL)
#define  MAX_SIZE   (1000000)


int min(int a, int b)
{
    if(a > b)
        return b;
    return a;
}


unsigned long long powOfTwo(int n)
{
    static int dp[MAX_SIZE + 1] = {1, 2, 4, 8, 16, 32};
    
    if(dp[n] != 0)
        return dp[n];
    
    unsigned long long half = powOfTwo(n>>1);
    if(n % 2 == 0)
        dp[n] = (half * half) % MOD;
    else 
        dp[n] = (((half * half) % MOD) << 1) % MOD;
    
    return dp[n];
}


unsigned long long fun(int n)
{
    if(n == 0)
        return 1;
    return powOfTwo(n - 1);
}


/*
 * Complete the 'summingPieces' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int summingPieces(int arr_count, int* arr) 
{
    int repeatCnt[MAX_SIZE] = {0};
    repeatCnt[0] = (powOfTwo(arr_count) + MOD - 1) % MOD;
    
    for(int i = 1; i < ((arr_count + 1) >> 1); i++)
    {
        repeatCnt[i] = (
            repeatCnt[i - 1] + 
            (powOfTwo(i - 1) * (powOfTwo(arr_count - i) - 1) % MOD) +
            MOD -
            (powOfTwo(arr_count - i - 1) * (powOfTwo(i) - 1)) % MOD 
        ) % MOD;
    }
    
    
    unsigned long long res = 0;
    
    for(int i = 0; i < arr_count; i++)
    {
        unsigned long long repCnt = repeatCnt[min(i, arr_count - i - 1)];
        
        res += (repCnt * arr[i]) % MOD;
        res %= MOD;
    }
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int arr_count = parse_int(ltrim(rtrim(readline())));

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(arr_count * sizeof(int));

    for (int i = 0; i < arr_count; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    int result = summingPieces(arr_count, arr);

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
