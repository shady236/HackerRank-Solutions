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

#define  MOD              (1000000007ULL)
#define  MAX_N            (2000)
#define  MAX_REPEATS      ((MAX_N) >> 1)

void initDp(int dp[MAX_N + 1][MAX_REPEATS + 1])
{
    /* 
     * if repeated length (repeared count * 2) >= len
     * there's no valid permutations
     */
    for(int len = 0; len <= MAX_N; len++)
    {
        for(int rep = len<<1; rep <= MAX_REPEATS; rep++)
        {
            dp[len][rep] = 0;
        }
    }
    
    /*
     * if there's no repetains, all permuations are valid,
     * thier count is n!
     */ 
    dp[0][0] = 1;
    for(int len = 1; len <= MAX_N; len++)
    {
        dp[len][0] = (
            dp[len - 1][0] * (unsigned long long)len
        ) % MOD;
    }
    
    
    /*
     * for any other lenghts & repeations count, first 
     * element can be chosen from either the repeated 
     * characters or from the upreapeted ones:
     *   - if it's chosen from unrepated ones, repeated
     *     count won't change, but length is decreased by 1
     *   - if it's chosen from repated ones, repeated
     *     count decreases by 1, length is decreased by 1
     */ 
    for(long long len = 1; len <= MAX_N; len++)
    {
        for(long long rep = 1; rep <= (len >> 1); rep++)
        {
            dp[len][rep] = (
                (len - (rep<<1)) * dp[len - 1][rep] + 
                rep * (
                    (
                        dp[len - 1][rep - 1] - 
                        dp[len - 2][rep - 1] + 
                        MOD 
                    ) % MOD
                )
            ) % MOD;
        }
    }
}


int partinion(int* arr, int leftIdx, int rightIdx)
{
    int pivot = arr[leftIdx];
    int pivotIdx = leftIdx;
    
    for(int i = leftIdx + 1; i <= rightIdx; i++)
    {
        if(arr[i] < pivot)
        {
            int tmp = arr[leftIdx];
            arr[leftIdx] = arr[i];
            arr[i] = tmp;
            
            if(pivotIdx == leftIdx)
                pivotIdx = i;
            
            leftIdx++;
        }
    }
    
    arr[pivotIdx] = arr[leftIdx];
    arr[leftIdx] = pivot;
    
    return leftIdx;
}

void quikSort(int* arr, int leftIdx, int rightIdx)
{
    if(leftIdx >= rightIdx)
        return;
    
    int pivotIdx = partinion(arr, leftIdx, rightIdx);
    quikSort(arr, leftIdx, pivotIdx - 1);
    quikSort(arr, pivotIdx + 1, rightIdx);
}


void sortArr(int arrSize, int* arr)
{
    quikSort(arr, 0, arrSize - 1);
}


/*
 * Complete the 'beautifulPermutations' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int beautifulPermutations(int arr_count, int* arr) 
{
    static int dp[MAX_N + 1][MAX_REPEATS + 1] = {-1};
    
    if(dp[0][0] == -1)
        initDp(dp);
    
    
    sortArr(arr_count, arr);
    
    int repeatsCnt = 0;
    for(int i = 1; i < arr_count; i++)
    {
        if(arr[i] == arr[i - 1])
            repeatsCnt++;
    }
    
    return dp[arr_count][repeatsCnt];
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

        int result = beautifulPermutations(arr_count, arr);

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