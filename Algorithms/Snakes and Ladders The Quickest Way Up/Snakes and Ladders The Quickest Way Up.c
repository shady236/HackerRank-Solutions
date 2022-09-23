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


int min(int a, int b)
{
    if(a > b)
        return b;
    return a;
}


int minSteps(int* des, int strt, int* dp, char* isVisited)
{
    if(dp[strt] != -2)
        return dp[strt];
    
    if(strt >= 99)
        return 0;
    
    if(strt + 6 >= 99)
        return 1;
    
    isVisited[strt] = 1;
    
    int res = -1;
    for(int step = 1; step <= 6; step++)
    {
        int nextStrt = des[strt + step];
        if(isVisited[nextStrt])
            continue;
        
        int next = minSteps(des, nextStrt, dp, isVisited);
        
        if(next != -1)
        {
            if(res == -1)
                res = next + 1;
            else 
                res = min(res, next + 1);
        }
    }
    
    isVisited[strt] = 0;
    dp[strt] = res;
    return res;
}


/*
 * Complete the 'quickestWayUp' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY ladders
 *  2. 2D_INTEGER_ARRAY snakes
 */

int quickestWayUp(int ladders_rows, int ladders_columns, int** ladders, int snakes_rows, int snakes_columns, int** snakes) 
{
    int des[100];
    for(int i = 0; i < 100; i++)
        des[i] = i;
    
    for(int i = 0; i < ladders_rows; i++)
        des[ladders[i][0] - 1] = ladders[i][1] - 1;
    
    for(int i = 0; i < snakes_rows; i++)
        des[snakes[i][0] - 1] = snakes[i][1] - 1;
    
    int dp[100];
    for(int i = 0; i < 100; i++)
        dp[i] = -2;
    
    char isVisited[100] = {0};
    
    return minSteps(des, 0, dp, isVisited);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        int** ladders = malloc(n * sizeof(int*));

        for (int i = 0; i < n; i++) {
            *(ladders + i) = malloc(2 * (sizeof(int)));

            char** ladders_item_temp = split_string(rtrim(readline()));

            for (int j = 0; j < 2; j++) {
                int ladders_item = parse_int(*(ladders_item_temp + j));

                *(*(ladders + i) + j) = ladders_item;
            }
        }

        int m = parse_int(ltrim(rtrim(readline())));

        int** snakes = malloc(m * sizeof(int*));

        for (int i = 0; i < m; i++) {
            *(snakes + i) = malloc(2 * (sizeof(int)));

            char** snakes_item_temp = split_string(rtrim(readline()));

            for (int j = 0; j < 2; j++) {
                int snakes_item = parse_int(*(snakes_item_temp + j));

                *(*(snakes + i) + j) = snakes_item;
            }
        }

        int result = quickestWayUp(n, 2, ladders, m, 2, snakes);

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
