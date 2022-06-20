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

typedef struct
{
    int i, j;
}Node_t;

/*
 * Complete the 'connectedCell' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */

int connectedCell(int matrix_rows, int matrix_columns, int** matrix)
{
    Node_t connected[100] = {0};
    int    connectedCount =  0 ;
    
    Node_t offset[8] = {
        {-1, -1},  {-1, 0},  {-1, 1},
        { 0, -1},            { 0, 1},
        { 1, -1},  { 1, 0},  { 1, 1}
    };
    
    char isVisited[10][10] = {0};
    int  max = 0;
    
    for(int i=0; i<matrix_rows; i++)
    {
        for(int j=0; j<matrix_columns; j++)
        {
            if(isVisited[i][j])     continue;
            isVisited[i][j] = 1;
            
            if(matrix[i][j] == 0)       continue;

            int count = 1; 
            connected[0].i = i;
            connected[0].j = j;
            connectedCount = 1;

            int connectedIdx = 0;
            while(connectedIdx < connectedCount)
            {
                for(int k=0; k<8; k++)
                {
                    int i = connected[connectedIdx].i + offset[k].i;
                    int j = connected[connectedIdx].j + offset[k].j;
                    if(i >= 0 && j>= 0 && i<matrix_rows && j<matrix_columns && !isVisited[i][j])
                    {
                        isVisited[i][j] = 1;
                        if(matrix[i][j])
                        {
                            count++;
                            connected[connectedCount].i = i;
                            connected[connectedCount].j = j;
                            connectedCount++;
                        }
                    }
                }
                connectedIdx++;                
            }
            if(count > max)     max = count;
        }
    }
    
    return max;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int m = parse_int(ltrim(rtrim(readline())));

    int** matrix = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(matrix + i) = malloc(m * (sizeof(int)));

        char** matrix_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < m; j++) {
            int matrix_item = parse_int(*(matrix_item_temp + j));

            *(*(matrix + i) + j) = matrix_item;
        }
    }

    int result = connectedCell(n, m, matrix);

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
