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

#define  MAX_ROWS    (100)
#define  MAX_COLUMS  (100)

#define  BLOCKED  ('X')
#define  EMPTY    ('.')
#define  TARGET   ('*')
#define  START    ('M')


char isPathEqualsK(int matrixRows, int matrixCols, char** matrix, int k, int strtI, int strtJ, char** isViaited)
{
    if(k < 0)
        return 0;
    if(k == 0 && matrix[strtI][strtJ] == TARGET)
        return 1;
    
    
    int  destinations[4][2];
    char destinationsCnt = 0;
    
    // Check if going up is available 
    if(strtI > 0 && matrix[strtI - 1][strtJ] != BLOCKED && !isViaited[strtI - 1][strtJ])
    {
        destinations[destinationsCnt][0] = strtI - 1;
        destinations[destinationsCnt][1] = strtJ;
        destinationsCnt++;
    }
    
    // Check if going down is available 
    if(strtI + 1 < matrixRows && matrix[strtI + 1][strtJ] != BLOCKED && !isViaited[strtI + 1][strtJ])
    {
        destinations[destinationsCnt][0] = strtI + 1;
        destinations[destinationsCnt][1] = strtJ;
        destinationsCnt++;
    }
    
    // Check if going left is available 
    if(strtJ > 0 && matrix[strtI][strtJ - 1] != BLOCKED && !isViaited[strtI][strtJ - 1])
    {
        destinations[destinationsCnt][0] = strtI;
        destinations[destinationsCnt][1] = strtJ - 1;
        destinationsCnt++;
    }
    
    // Check if going right is available 
    if(strtJ + 1 < matrixCols && matrix[strtI][strtJ + 1] != BLOCKED && !isViaited[strtI][strtJ + 1])
    {
        destinations[destinationsCnt][0] = strtI;
        destinations[destinationsCnt][1] = strtJ + 1;
        destinationsCnt++;
    }
    
    
    char res = 0;
    int  desI, desJ;
    switch (destinationsCnt)
    {
        case 0:
            res = 0;
        break;
        
        case 1:
            desI = destinations[0][0];
            desJ = destinations[0][1];
            
            isViaited[desI][desJ] = 1;
            
            res = isPathEqualsK(matrixRows, matrixCols, matrix, k, desI, desJ, isViaited);
            
            isViaited[desI][desJ] = 0;
        break;
        
        default:
            for(int i = 0; i < destinationsCnt && !res; i++)
            {
                desI = destinations[i][0];
                desJ = destinations[i][1];
                
                isViaited[desI][desJ] = 1;
                
                res = isPathEqualsK(matrixRows, matrixCols, matrix, k - 1, desI, desJ, isViaited);
                
                isViaited[desI][desJ] = 0;
            }
        break;
    }
    
    return res;
}

/*
 * Complete the 'countLuck' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING_ARRAY matrix
 *  2. INTEGER k
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* countLuck(int matrix_count, char** matrix, int k)
{
    static char* str[] = {"Oops!", "Impressed"};
    
    int matrixCols = strlen(matrix[0]);
    
    
    char** isVisited = malloc(matrix_count * sizeof(char*));
    for(int i = 0; i < matrix_count; i++)
    {
        isVisited[i] = malloc(matrixCols * sizeof(char));
        for(int j = 0; j < matrixCols; j++)
            isVisited[i][j] = 0;
    }
    
    
    for(int i = 0; i < matrix_count; i++)
    {
        for(int j = 0; j < matrixCols; j++)
        {
            if(matrix[i][j] == START)
            {
                isVisited[i][j] = 1;
                return str[
                    isPathEqualsK(matrix_count, matrixCols, matrix, k, i, j, isVisited)
                ];
            }
        }
    }
    
    return str[0];
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        char** matrix = malloc(n * sizeof(char*));

        for (int i = 0; i < n; i++) {
            char* matrix_item = readline();

            *(matrix + i) = matrix_item;
        }

        int k = parse_int(ltrim(rtrim(readline())));

        char* result = countLuck(n, matrix, k);

        fprintf(fptr, "%s\n", result);
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
