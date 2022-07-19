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


#define  MOD  (1000000007)

/*
 * Complete the 'hackerrankCity' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY A as parameter.
 */

int hackerrankCity(int A_count, int* A) 
{
    /* number of cities at each step. */
    int n[1000000] = {1};
    for(int i = 1; i < A_count; i++)
    {
        unsigned long long prevN = n[i - 1];
        n[i] = ((prevN<<2) + 2) % MOD;
    }
    
    
    /* 
     * sum of distances from buttom corner to opposite 
     * up corner (i.e buttom left -> up right or
     * buttom right -> up left) at each step. 
     */
    int butomUp[1000000] = {0};
    for(int i = 1; i < A_count; i++)
    {
        unsigned long long prevButomUp = butomUp[i - 1];
        butomUp[i] = (
            (prevButomUp<<1) + 3 * A[i - 1]
        ) % MOD;
    }
    
    
    /* 
     * sum of distances from buttom corner to all other 
     * cities at each step. 
     */
    int butomAll[1000000] = {0};
    for(int i = 1; i < A_count; i++)
    {
        unsigned long long prevButomAll = butomAll[i - 1];
        unsigned long long prevN        = n[i - 1];
        unsigned long long prevButomUp  = butomUp[i - 1];
        
        butomAll[i] = (
            ((prevButomAll<<2) % MOD) +
            (((3 * prevN + 2) * prevButomUp) % MOD) + 
            ((8 * prevN * A[i - 1]) % MOD) + 
            (3 * A[i - 1])
        ) % MOD;
    }
    

    /* prev & current total sum at each step */
    unsigned long long prevSum = 0;
    unsigned long long currSum = 0;
    for(int i = 0; i < A_count; i++)
    {
        prevSum = currSum;
        
        unsigned long long prevN = n[i];
        unsigned long long prevButomAll = butomAll[i];
        
        currSum = (
            ((prevSum<<2) % MOD) + 
            ((prevButomAll<<3) % MOD) + 
            ((prevButomAll * 12 * prevN) % MOD) + 
            ((A[i] * 12 * prevN) % MOD) + 
            ((((A[i] * prevN * prevN) % MOD)<<4) % MOD) + 
            (A[i])
        ) % MOD;
    }
    
    return currSum;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int A_count = parse_int(ltrim(rtrim(readline())));

    char** A_temp = split_string(rtrim(readline()));

    int* A = malloc(A_count * sizeof(int));

    for (int i = 0; i < A_count; i++) {
        int A_item = parse_int(*(A_temp + i));

        *(A + i) = A_item;
    }

    int result = hackerrankCity(A_count, A);

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
