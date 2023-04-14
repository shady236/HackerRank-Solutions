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


long max(long a, long b)
{
    if(a > b)
        return a;
    return b;
}


long maxOfThree(long a, long b, long c)
{
    return max(max(a, b), c);
}

#define  MAX_CELLS_CNT      (4000000)

/*
 * allocate dp arrays as 1D to be able to allocate it 
 * statically outside stack & heap as thier size is small
 */
int maxScore[MAX_CELLS_CNT];
int maxScoreToRight[MAX_CELLS_CNT];
int maxScoreToLeft[MAX_CELLS_CNT];
int maxScoreToRightDown[MAX_CELLS_CNT];
int maxScoreToLeftDown[MAX_CELLS_CNT];


/*
 * define mapping between 1D & 2D arrays
 * i, j is the indeces of the required cell, where 
 * rows, cols are rows & columns sizes of the 2D grid
 * arr is the target arr which will be one of the dp arrays
 */
long getElement(int rows, int cols, int i, int j, int* arr)
{
    if(i < 0 || j < 0 || i >= rows || j >= cols)
        return 0;
    
    return arr[i * cols + j];
}


void setElement(int rows, int cols, int i, int j, int* arr, int val)
{
    if(i >= 0 && j >= 0 && i < rows && j < cols)
        arr[i * cols + j] = val;
}


int sum(int A_rows, int A_columns, int** A) 
{
    int sum = 0;
    
    for(int i = 0; i < A_rows; i++)
    {
        for(int j = 0; j < A_columns; j++)
        {
            sum += A[i][j];
        }
    }
    
    return sum;
}


/*
 * Complete the 'matrixLand' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY A as parameter.
 */

int matrixLand(int A_rows, int A_columns, int** A) 
{
    if(A_columns == 1)
        return sum(A_rows, A_columns, A);
    
    
    for(int i = A_rows - 1; i >= 0; i--)
    {
        for(int j = 0; j < A_columns; j++)
        {
            long score = A[i][j] + max(
                0, 
                getElement(A_rows, A_columns, i, j - 1, maxScoreToLeft)
            );
            
            setElement(A_rows, A_columns, i, j, maxScoreToLeft, score);
        }
        
        for(int j = A_columns - 1; j >= 0; j--)
        {
            long score = A[i][j] + max(
                0, 
                getElement(A_rows, A_columns, i, j + 1, maxScoreToRight)
            );
            
            setElement(A_rows, A_columns, i, j, maxScoreToRight, score);
        }
        
        
        for(int j = 0; j < A_columns; j++)
        {
            long score = max(
                getElement(A_rows, A_columns, i, j, maxScoreToLeft) + getElement(A_rows, A_columns, i + 1, j, maxScore), 
                A[i][j] + getElement(A_rows, A_columns, i, j - 1, maxScoreToLeftDown)
            );
            
            setElement(A_rows, A_columns, i, j, maxScoreToLeftDown, score);
        }
        
        for(int j = A_columns - 1; j >= 0; j--)
        {
            long score = max(
                getElement(A_rows, A_columns, i, j, maxScoreToRight) + getElement(A_rows, A_columns, i + 1, j, maxScore), 
                A[i][j] + getElement(A_rows, A_columns, i, j + 1, maxScoreToRightDown)
            );
            
            setElement(A_rows, A_columns, i, j, maxScoreToRightDown, score);
        }
        
        
        for(int j = 0; j < A_columns; j++)
        {
            long path1 = A[i][j] + getElement(A_rows, A_columns, i + 1, j, maxScore);
            
            long path2 = getElement(A_rows, A_columns, i, j, maxScoreToRightDown) + getElement(A_rows, A_columns, i, j, maxScoreToLeft) - A[i][j];
            
            long path3 = getElement(A_rows, A_columns, i, j, maxScoreToLeftDown) + getElement(A_rows, A_columns, i, j, maxScoreToRight) - A[i][j];
            
            long score = maxOfThree(path1, path2, path3);
            setElement(A_rows, A_columns, i, j, maxScore, score);
        }
    }
    
    
    
    int res = getElement(A_rows, A_columns, 0, 0, maxScore);;
    
    for(int j = 0; j < A_columns; j++)
    {
        int s = getElement(A_rows, A_columns, 0, j, maxScore);
        res = max(res, s);
    }
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int m = parse_int(*(first_multiple_input + 1));

    int** A = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(A + i) = malloc(m * (sizeof(int)));

        char** A_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < m; j++) {
            int A_item = parse_int(*(A_item_temp + j));

            *(*(A + i) + j) = A_item;
        }
    }

    int result = matrixLand(n, m, A);

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
