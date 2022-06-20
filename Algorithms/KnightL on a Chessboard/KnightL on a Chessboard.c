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

int parse_int(char*);

/*
 * Complete the 'knightlOnAChessboard' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts INTEGER n as parameter.
 */

/*
 * To return the 2d integer array from the function, you should:
 *     - Store the number of rows of the array to be returned in the result_rows variable
 *     - Store the number of columns of the array to be returned in the result_columns variable
 *     - Allocate the array dynamically
 *
 * For example,
 * int** return_2d_integer_array(int* result_rows, int* result_columns) {
 *     *result_rows = 2;
 *     *result_columns = 3;
 *
 *     int** a = malloc(2 * sizeof(int*));
 *
 *     for (int i = 0; i < 2; i++) {
 *         *(a + i) = malloc(3 * sizeof(int));
 *
 *         for (int j = 0; j < 3; j++) {
 *             *(*(a + i) + j) = 3 * i + j + 1;
 *         }
 *     }
 *
 *     return a;
 * }
 *
 */
int minPositive(int* arr, int siz)
{
    int res = -1;
    
    for(int i = 0; i < siz; i++)
    {
        if(res == -1 || (arr[i] < res && arr[i] >= 0))
            res = arr[i];
    }
    
    return res;
}

char isFound(int* arr1, int* arr2, int siz, int target1, int target2)
{
    for(int i = 0; i < siz; i++)
    {
        if(target1 == arr1[i] && target2 == arr2[i])
            return 1;
    }
    
    return 0;
}

int minPath(int n, int step1, int step2)
{
    int paths[26][26];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            paths[i][j] = -1;
        }
    }
    
    paths[n - 1][n - 1] = 0;
    
    int connectedSquaresOffset[8][2] = {
        { step1 ,  step2},
        { step1 , -step2},
        {-step1 ,  step2},
        {-step1 , -step2},
        { step2 ,  step1},
        { step2 , -step1},
        {-step2 ,  step1},
        {-step2 , -step1}
    };
        
    char isThereMore   = 1;
    int  lastAddedPath = 0;
    while(isThereMore)
    {
        isThereMore = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(paths[i][j] != lastAddedPath)
                    continue;
                
                for(int k = 0; k < 8; k++)
                {
                    int x = i + connectedSquaresOffset[k][0];
                    int y = j + connectedSquaresOffset[k][1];
                    if(x >= 0 && x < n && y >= 0 && y < n && paths[x][y] == -1)
                    {
                        paths[x][y] = lastAddedPath + 1;
                        isThereMore = 1;
                    }
                }
            }
        }
        lastAddedPath++;
    }
    
    return paths[0][0];
}


int** knightlOnAChessboard(int n, int* result_rows, int* result_columns)
{
    int** res = malloc((n - 1) * sizeof(int*));
    *result_rows    = n - 1;
    *result_columns = n - 1;
    
    for(int i = 0; i < n - 1; i++)
        res[i] = malloc((n - 1) * sizeof(int));
    
    
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i; j < n - 1; j++)
        {
            res[i][j] = minPath(n, i + 1, j + 1);
            res[j][i] = res[i][j];
        }
    }
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int result_rows;
    int result_columns;
    int** result = knightlOnAChessboard(n, &result_rows, &result_columns);

    for (int i = 0; i < result_rows; i++) {
        for (int j = 0; j < result_columns; j++) {
            fprintf(fptr, "%d", *(*(result + i) + j));

            if (j != result_columns - 1) {
                fprintf(fptr, " ");
            }
        }

        if (i != result_rows - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
