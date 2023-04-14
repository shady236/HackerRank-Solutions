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

int min(int x, int y)
{
    if(x < y)       return x;
    return y;
}

/*
 * Complete the 'gridlandMetro' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. INTEGER k
 *  4. 2D_INTEGER_ARRAY track
 */

unsigned long long gridlandMetro(int n, int m, int k, int track_rows, int track_columns, int** track)
{
    // sort track array 
    for(int i = 0; i < k - 1; i++)
    {
        int minIdx = i;
        for(int j = i + 1; j < k; j++)
        {
            if(track[j][0] < track[minIdx][0])
                minIdx = j;
            else if(track[j][0] == track[minIdx][0] && track[j][1] < track[minIdx][1])
                minIdx = j;
        }
        
        if(minIdx != i)
        {
            for(int l = 0; l < track_columns; l++)
            {
                int tmp = track[i][l];
                track[i][l] = track[minIdx][l];
                track[minIdx][l] = tmp;
            }
        }
    }
    
    
    unsigned long long count = 0;
    int coveredRows = 0;
    int i = 0;
    while(i < k)
    {
        unsigned long long coverage = track[i][2] - track[i][1] + 1;
        int coverageEnd = track[i][2];
        while(i + 1 < k && track[i + 1][0] == track[i][0])
        {
            coverage += track[i + 1][2] - track[i + 1][1] + 1;
            if(coverageEnd >= track[i + 1][1])
                coverage -= min(coverageEnd, track[i + 1][2]) - track[i + 1][1] + 1;
            if(track[i + 1][2] > coverageEnd)
                coverageEnd = track[i + 1][2];
            
            i++;
        }
        
        count += m - coverage;
        coveredRows++;
        i++;
    }
    
    count += (n - (unsigned long long)coveredRows) * m;
    
    return count;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int m = parse_int(*(first_multiple_input + 1));

    int k = parse_int(*(first_multiple_input + 2));

    int** track = malloc(k * sizeof(int*));

    for (int i = 0; i < k; i++) {
        *(track + i) = malloc(3 * (sizeof(int)));

        char** track_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 3; j++) {
            int track_item = parse_int(*(track_item_temp + j));

            *(*(track + i) + j) = track_item;
        }
    }

    unsigned long long result = gridlandMetro(n, m, k, k, 3, track);

    fprintf(fptr, "%llu\n", result);

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
