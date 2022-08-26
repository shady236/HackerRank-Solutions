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

/*
 * Complete the 'almostSorted' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void almostSorted(int arr_count, int* arr)
{
    int firstDiffIdx = -1;
    for(int i = 0; i < arr_count - 1; i++)
    {
        if(arr[i] > arr[i + 1])
        {
            firstDiffIdx = i;
            break;
        }
    }
    
    if(firstDiffIdx == -1)
    {
        printf("yes");
        return;
    }
    
    int swapToIdx = -1;
    for(int i = firstDiffIdx + 1; i < arr_count - 1; i++)
    {
        if(arr[i] <= arr[firstDiffIdx + 1] && arr[i + 1] > arr[firstDiffIdx])
        {
            swapToIdx = i;
            break;
        }
    }
    
    if(swapToIdx == -1 && arr[arr_count - 1] <= arr[firstDiffIdx + 1])
        swapToIdx = arr_count - 1;
    
    if(swapToIdx != -1)
    {
        int tmp = arr[firstDiffIdx];
        arr[firstDiffIdx] = arr[swapToIdx];
        arr[swapToIdx] = tmp;
        
        for(int i = 0; i < arr_count - 1; i++)
        {
            if(arr[i] > arr[i + 1])
                break;
            
            if(i == arr_count - 2)
            {
                printf("yes\n");
                printf("swap %d %d", firstDiffIdx + 1, swapToIdx + 1);
                return;
            }
        }
        
        tmp = arr[firstDiffIdx];
        arr[firstDiffIdx] = arr[swapToIdx];
        arr[swapToIdx] = tmp;
    }
    
    int lastReveeseIdx = -1;
    for(int i = firstDiffIdx + 1; i < arr_count - 1; i++)
    {
        if(arr[i] < arr[i + 1])
        {
            lastReveeseIdx = i;
            break;
        }
    }
    
    if(lastReveeseIdx == -1)
        lastReveeseIdx = arr_count - 1;
    
    for(int i = firstDiffIdx; i < (firstDiffIdx + lastReveeseIdx + 1)>>1; i++)
    {
        int tmp = arr[i];
        arr[i] = arr[lastReveeseIdx - i + firstDiffIdx];
        arr[lastReveeseIdx - i + firstDiffIdx] = tmp;
    }
    
    
    for(int i = 0; i < arr_count - 1; i++)
    {
        if(arr[i] > arr[i + 1])
            break;
        
        if(i == arr_count - 2)
        {
            printf("yes\n");
            printf("reverse %d %d", firstDiffIdx + 1, lastReveeseIdx + 1);
            return;
        }
    }
    
    printf("no");
}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    almostSorted(n, arr);

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
