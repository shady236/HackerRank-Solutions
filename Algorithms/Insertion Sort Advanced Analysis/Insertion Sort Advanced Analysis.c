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


long mergeInversionCnt(int* arr, int left, int mid, int right)
{
    long invCnt = 0;
    
    int leftSeg[100000];
    for (int i = 0; i + left <= mid; i++)
        leftSeg[i] = arr[i + left];
    
    int rightSeg[100000];
    for (int i = 0; i + mid + 1 <= right; i++)
        rightSeg[i] = arr[i + mid + 1];
    
    
    int leftSize  = mid - left + 1;
    int rightSize = right - mid;
    int leftIdx   = 0;
    int rightIdx  = 0;
    int arrIdx = left;
    
    while (leftIdx < leftSize && rightIdx < rightSize) 
    {
        if(leftSeg[leftIdx] <= rightSeg[rightIdx])
        {
            arr[arrIdx] = leftSeg[leftIdx];
            leftIdx++;
        }
        else 
        {
            arr[arrIdx] = rightSeg[rightIdx];
            rightIdx++;
            invCnt += leftSize - leftIdx;
        }
        
        arrIdx++;
    }
    
    
    while (leftIdx < leftSize) 
    {
        arr[arrIdx] = leftSeg[leftIdx];
        leftIdx++;
        arrIdx++;
    }
    
    
    while (rightIdx < rightSize) 
    {
        arr[arrIdx] = rightSeg[rightIdx];
        rightIdx++;
        arrIdx++;
    }
    
    return invCnt;
}


long inversionsCnt(int* arr, int left, int right)
{
    // count inversions using merge sort
    
    if(left >= right)
        return 0;
    
    int mid = (left + right) >> 1;
    
    long leftInv  = inversionsCnt(arr, left, mid);
    long rightInv = inversionsCnt(arr, mid + 1, right);
    long mergeInv = mergeInversionCnt(arr, left, mid, right);
    
    return leftInv + rightInv + mergeInv;
}


/*
 * Complete the 'insertionSort' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

long insertionSort(int arr_count, int* arr) 
{
    return inversionsCnt(arr, 0, arr_count - 1);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** arr_temp = split_string(rtrim(readline()));

        int* arr = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int arr_item = parse_int(*(arr_temp + i));

            *(arr + i) = arr_item;
        }

        long result = insertionSort(n, arr);

        fprintf(fptr, "%ld\n", result);
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
