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
 * original eqn is  ((m1 & m2) ^ (m1 | m2)) & (m1 ^ m2)
 * this expression can be simplified.
 * 
 * for ((m1 & m2) ^ (m1 | m2)), the 4 cases are
 *  - ((0 & 0) ^ (0 | 0)) = (0) ^ (0) = 0
 *  - ((0 & 1) ^ (0 | 1)) = (0) ^ (1) = 1
 *  - ((1 & 0) ^ (1 | 0)) = (0) ^ (1) = 1
 *  - ((1 & 1) ^ (1 | 1)) = (1) ^ (1) = 0
 * so, ((m1 & m2) ^ (m1 | m2)) is equilvelant to (m1 ^ m2)
 * 
 * so, ((m1 & m2) ^ (m1 | m2)) & (m1 ^ m2) equilvelant to 
 * (m1 ^ m2) & (m1 ^ m2) which is equilvelant to (m1 ^ m2)
 */
#define eqn(m1, m2)    ((m1) ^ (m2))


/*
 * Complete the 'andXorOr' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

int andXorOr(int a_count, int* a)
{
    /*
     * our goal is to find smallest & next smallest of each
     * interval, to get max value of eqn.
     * 
     * algorithm is based on using a stack to store the 
     * increasing elements of the array in thier original
     * order. that's top of stack always is an element of
     * the array let's say a[j]. for each element a[i]
     *  - if a[i] > top of stack (a[j])
     *      * caculate eqn for a[i] & top of stack (a[j]) 
     *        because a[j] is the smallest & a[i] is next
     *        smallest in the interval [j, i]
     *      * push a[i] to stack
     *  - if a[i] < top of stack (a[j])
     *      * caculate eqn for a[i] & top of stack (a[j]) 
     *        because a[i] is the smallest & a[j] is next
     *        smallest in the interval [j, i]
     *      * pop from stack, then repeat again until to of
     *        stack becomes < a[i] or untill stack is empty,
     *        then push a[i]
     */
    
    int maxS = 0;
    int stack[1000000];
    int stackTop = -1;
    
    for(int i = 0; i < a_count; i++)
    {
        while(stackTop >= 0 && stack[stackTop] > a[i])
        {
            int s = eqn(stack[stackTop], a[i]);
            if(s > maxS)
                maxS = s;
            
            stackTop--; // pop from stack
        }
        
        if(stackTop >= 0)
        {
            int s = eqn(stack[stackTop], a[i]);
            if(s > maxS)
                maxS = s;
        }
        
        // push
        stackTop++;
        stack[stackTop] = a[i];
    }
    
    return maxS;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int a_count = parse_int(ltrim(rtrim(readline())));

    char** a_temp = split_string(rtrim(readline()));

    int* a = malloc(a_count * sizeof(int));

    for (int i = 0; i < a_count; i++) {
        int a_item = parse_int(*(a_temp + i));

        *(a + i) = a_item;
    }

    int result = andXorOr(a_count, a);

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
