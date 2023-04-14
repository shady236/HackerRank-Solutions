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
long parse_long(char*);


#define BIT(x, i)       (((x) >> (i)) & 1)


int onesCnt(long n) {
    int cnt = 0;
    for (int i = 0; i < 64; i++) {
        cnt += BIT(n, i);
    }
    return cnt;
}


int subsetVal(long* set, int size) {
    long val = 0;
    for (int i = 0; i < size; i++) {
        if (onesCnt(set[i]) > 1) {
            val |= set[i];
        }
    }
    
    if (val == 0) {
        return 64;
    }
    return 65 - onesCnt(val);
}


int subsetSum(long* arr, int arrSize, int idx, long* set, int setSize) {
    if (idx == arrSize) {
        return subsetVal(set, setSize);
    }
    
    int sum = 0;
    sum += subsetSum(arr, arrSize, idx + 1, set, setSize);
    
    set[setSize++] = arr[idx];
    sum += subsetSum(arr, arrSize, idx + 1, set, setSize);
    setSize--;
    
    return sum;
}


/*
 * Complete the 'findConnectedComponents' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts LONG_INTEGER_ARRAY d as parameter.
 */

int findConnectedComponents(int d_count, long* d) {
    long set[20];
    return subsetSum(d, d_count, 0, set, 0);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int d_count = parse_int(ltrim(rtrim(readline())));

    char** d_temp = split_string(rtrim(readline()));

    long* d = malloc(d_count * sizeof(long));

    for (int i = 0; i < d_count; i++) {
        long d_item = parse_long(*(d_temp + i));

        *(d + i) = d_item;
    }

    int components = findConnectedComponents(d_count, d);

    fprintf(fptr, "%d\n", components);

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

long parse_long(char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
