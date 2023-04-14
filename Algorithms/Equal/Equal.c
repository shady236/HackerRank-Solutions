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
 * Complete the 'equal' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int equal(int arr_count, int* arr)
{
    int min = arr[0];
    for(int i = 1; i < arr_count; i++)
    {
        if(arr[i] < min)
            min = arr[i];
    }
    
    /* 
     * operations required depend on diffrence between
     * chochalates each one have, not actual values
     */
    for(int i = 0; i < arr_count; i++)
    {
        arr[i] -= min;
    }
    
    /*
     * adding x chocaolates to all but one equivilant to 
     * taking x chocaolates from one.
     * 
     * To make all must have the same chocaolates count, 
     * they all must have 0 or less chocaolates as min one
     * has 0 now (after subtracting min from all)
     * 
     * making all have x chocaolates for x <= -5
     * isn't optimum as it requires the same number of 
     * operations to make all have (x + 5) chocholates + 
     * other operations to take 5 chocaolates from all 
     */
    
    int minOpCnt = 100000000;
    for(int equalizeTo = 0; equalizeTo > -5; equalizeTo--)
    {
        int opCnt = 0;
        for(int i = 0; i < arr_count; i++)
        {
            opCnt += (
                (arr[i] - equalizeTo) / 5 +
                ((arr[i] - equalizeTo) % 5) / 2 + 
                ((arr[i] - equalizeTo) % 5) % 2
            );
        }
        
        if(opCnt < minOpCnt)
            minOpCnt = opCnt;
    }
    
    return minOpCnt;
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

        int result = equal(n, arr);

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
