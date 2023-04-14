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
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

unsigned long solve(int arr_count, int* arr) 
{
    unsigned long routesCnt = 0;
    
    int stack[300000];
    int stackTop = -1;
    
    for(int i = 0; i < arr_count; i++)
    {
        /* 
         * pop from stack all skyscrapers with height lower
         * than current height as they can cross to any of
         * the skyscrapers behind current skyscraper
         * 
         * But before removing, calculte number of similar 
         * skyscrapers in height, to add them to the 
         * available routes count
         */
        while(stackTop > -1 && stack[stackTop] < arr[i])
        {
            unsigned long similarCnt = 0;
            int j;
            for(j = stackTop; j >= 0; j--)
            {
                if(stack[j] == stack[stackTop])
                    similarCnt++;
                else 
                    break;
            }
            routesCnt += similarCnt * (similarCnt - 1);
            
            stackTop = j;
        }
        
        stackTop++;
        stack[stackTop] = arr[i];
    }
    
    /* 
     * if stack isn't empty, add similar skyscrapers in
     * height to the available routes count
     */
    for(int i = stackTop; i >= 0; )
    {
        unsigned long similarCnt = 0;
        int j;
        for(j = i; j >= 0; j--)
        {
            if(stack[i] == stack[j])
                similarCnt++;
            else 
                break;
        }
        routesCnt += similarCnt * (similarCnt - 1);
        i = j;
    }
    
    return routesCnt;
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

    unsigned long result = solve(arr_count, arr);

    fprintf(fptr, "%lu\n", result);

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
