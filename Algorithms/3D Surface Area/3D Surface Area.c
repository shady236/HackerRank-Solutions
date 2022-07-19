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
 * Complete the 'surfaceArea' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY A as parameter.
 */

int surfaceArea(int A_rows, int A_columns, int** A)
{
    int area = A_rows * A_columns * 2;    // top & down 
    
    /* corners */ 
    if(A_rows > 1  &&  A_columns > 1)
    {
        area += 2 * (
            A[0][0] +
            A[A_rows - 1][0] + 
            A[0][A_columns - 1] +
            A[A_rows - 1][A_columns - 1]
        );
        
        if(A[0][0] > A[0][1])
            area += A[0][0] - A[0][1];
        
        if(A[0][0] > A[1][0])
            area += A[0][0] - A[1][0];


        if(A[A_rows - 1][0] > A[A_rows - 1][1])
            area += A[A_rows - 1][0] - A[A_rows - 1][1];

        if(A[A_rows - 1][0] > A[A_rows - 2][0])
            area += A[A_rows - 1][0] - A[A_rows - 2][0];


        if(A[0][A_columns - 1] > A[0][A_columns - 2])
            area += A[0][ A_columns - 1] - A[0][A_columns - 2];

        if(A[0][A_columns - 1] > A[1][A_columns - 1])
            area += A[0][A_columns - 1] - A[1][A_columns - 1];


        if(A[A_rows - 1][A_columns - 1] > A[A_rows - 1][A_columns - 2])
            area += A[A_rows - 1][A_columns - 1] - A[A_rows - 1][A_columns - 2];
            
        if(A[A_rows - 1][A_columns - 1] > A[A_rows - 2][A_columns - 1])
            area += A[A_rows - 1][A_columns - 1] - A[A_rows - 2][A_columns - 1];
    }
    else if(A_columns > 1)
    {
        area += 3 * (A[0][0] + A[0][A_columns - 1]);

        if(A[0][0] > A[0][1])
            area += A[0][0] - A[0][1];

        if(A[0][A_columns - 1] > A[0][A_columns - 2])
            area += A[0][A_columns - 1] - A[0][A_columns - 2];
    }
    else if(A_rows > 1)
    {
        area += 3 * (A[0][0] + A[A_rows - 1][0]);
        
        if(A[0][0] > A[1][0])
            area += A[0][0] - A[1][0];

        if(A[A_rows - 1][0] > A[A_rows - 2][0])
            area += A[A_rows - 1][0] - A[A_rows - 2][0];
    } 
    else 
    {
        area += 4 * A[0][0];
    } 

    
    /* Edges */
    for(int i = 1; i < A_rows - 1; i++) 
    {
        area += A[i][0] + A[i][A_columns - 1];
    
        if(A[i][0] > A[i - 1][0])
            area += A[i][0] - A[i - 1][0];
        
        if(A[i][0] > A[i + 1][0])
            area += A[i][0] - A[i + 1][0];
    
    
        if(A_columns > 1)
        {
            if(A[i][0] > A[i][1])
                area += A[i][0] - A[i][1];
        
            if(A[i][A_columns - 1] > A[i - 1][A_columns - 1])
                area += A[i][A_columns - 1] - A[i - 1][A_columns - 1];
            
            
            if(A[i][A_columns - 1] > A[i + 1][A_columns - 1])
                area += A[i][A_columns - 1] - A[i + 1][A_columns - 1];
            
            if(A[i][A_columns - 1] > A[i][A_columns - 2])
                area += A[i][A_columns - 1] - A[i][A_columns - 2];
        }
    }

    for(int i = 1; i < A_columns - 1; i++) 
    {
        area += A[0][i] + A[A_rows - 1][i];
    
    
        if(A[0][i] > A[0][i - 1])
            area += A[0][i] - A[0][i - 1];
        
        if(A[0][i] > A[0][i + 1])
            area += A[0][i] - A[0][i + 1];
    
        if(A_rows > 1)
        {
            if(A[0][i] > A[1][i])
                area += A[0][i] - A[1][i];
        
            
            if(A[A_rows - 1][i] > A[A_rows - 1][i - 1])
                area += A[A_rows - 1][i] - A[A_rows - 1][i - 1];
            
            if(A[A_rows - 1][i] > A[A_rows - 1][i + 1])
                area += A[A_rows - 1][i] - A[A_rows - 1][i + 1];
            
            if(A[A_rows - 1][i] > A[A_rows - 2][i])
                area += A[A_rows - 1][i] - A[A_rows - 2][i];
        }
    } 


    /* Middle */
    for(int i = 1; i < A_rows - 1; i++) 
    {
        for(int j = 1; j < A_columns - 1; j++) 
        {
            if(A[i][j] > A[i][j + 1])
                area += A[i][j] - A[i][j + 1];
                
            if(A[i][j] > A[i][j - 1])
                area += A[i][j] - A[i][j - 1];
                
            if(A[i][j] > A[i + 1][j])
                area += A[i][j] - A[i + 1][j];
                
            if(A[i][j] > A[i - 1][j])
                area += A[i][j] - A[i - 1][j];
        } 
    } 

    return area;
}



int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int H = parse_int(*(first_multiple_input + 0));

    int W = parse_int(*(first_multiple_input + 1));

    int** A = malloc(H * sizeof(int*));

    for (int i = 0; i < H; i++) {
        *(A + i) = malloc(W * (sizeof(int)));

        char** A_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < W; j++) {
            int A_item = parse_int(*(A_item_temp + j));

            *(*(A + i) + j) = A_item;
        }
    }

    int result = surfaceArea(H, W, A);

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
