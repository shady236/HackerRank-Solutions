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


long min(long a, long b)
{
    if(a < b)
        return a;
    return b;
}


long max(long a, long b)
{
    if(a > b)
        return a;
    return b;
}

/*
 * Complete the 'turnOffTheLights' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY c
 */

long turnOffTheLights(int k, int c_count, int* c) 
{
    /*
     * to turn all off with min cost, minmum 
     * number of swithces must be pressed
     * 
     * if switch at position i is pressed, all 
     * bulbs in the range [i-k -> i+k] are toggled
     * 
     * if switch at position i + 2k + 1 is pressed, all 
     * bulbs in the range [(i+2k+1)-k -> (i+2k+1)+k]
     * are toggled; i.e. the range [i+k+1 -> i+3k+1]
     * 
     * switch i & i + 2k + 1 wont't overlap, because 
     * the second range starts after where first was ended
     * 
     * As there's no overlap, no need to toggle a bulb more 
     * then one time, so min numbee of switches os pressed
     * 
     * NOTE: position of first switch to be pressed must be <= k 
     * as its range starts from i-k, so if i > k then 
     * the first switch start range will be > 0, so bulbs 
     * before this start will remain on 
     * 
     * NOTE: position of last switch to be pressed must be >= c_count-1-k 
     * as its range ends at i+k, so if i < c_count-1-k then 
     * the last switch end range will be < c_count-1, so bulbs 
     * after this start will remain on 
     */
    
    // no need for k > c_count - 1
    if(k > c_count - 1)
        k = c_count - 1;
    
    long minCost = INT64_MAX;
    
    for(int i = 0; i <= k; i++)
    {
        long cost = c[i];
        
        int currRangeEnd = i + k;
        int nextRangeStrt;
        int nextRangeCntr; 
        
        char isValid = 1;
        
        while(currRangeEnd < c_count - 1)
        {
            nextRangeStrt = currRangeEnd + 1;
            nextRangeCntr = nextRangeStrt + k; 
            
            if(nextRangeCntr < c_count)
                cost += c[nextRangeCntr];
            else 
                isValid = 0;
            
            currRangeEnd = nextRangeCntr + k;
        }
        
        if(isValid)
            minCost = min(minCost, cost);
    }
    
    return minCost;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char** c_temp = split_string(rtrim(readline()));

    int* c = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int c_item = parse_int(*(c_temp + i));

        *(c + i) = c_item;
    }

    long result = turnOffTheLights(k, n, c);

    fprintf(fptr, "%ld\n", result);

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
