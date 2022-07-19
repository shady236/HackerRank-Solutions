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
 * Complete the 'queensAttack' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 *  3. INTEGER r_q
 *  4. INTEGER c_q
 *  5. 2D_INTEGER_ARRAY obstacles
 */

int min(int a, int b)
{
    if(a > b)       return b;
    return a;
}

int queensAttack(int n, int k, int r_q, int c_q, int obstacles_rows, int obstacles_columns, int** obstacles)
{
    /* get location of nearst obstacles in all 8 directions */
    int upObstacleRow    = n + 1;
    int downObstacleRow  = 0;
    int rightObstacleCol = n + 1;
    int leftObstacleCol  = 0;
    
    int upRightObstacleRow   = n + 1;
    int downLeftObstacleRow  = 0;
    int upLeftObstacleRow    = n + 1;
    int downRightObstacleRow = 0;
    
    for(int i = 0; i < obstacles_rows; i++)
    {
        int obRow = obstacles[i][0];    //obstacle row
        int obCol = obstacles[i][1];    //obstacle column
        
        // if obstacle in the same column
        if(obCol == c_q)
        {
            // if ostacle is above & is the nearest
            if(obRow > r_q && obRow < upObstacleRow)
                upObstacleRow = obRow;
            // else if ostacle is below & is the nearest
            else if(obRow < r_q  &&  obRow > downObstacleRow)
                downObstacleRow = obRow;
        }
        
        // if obstacle in the same row
        if(obRow == r_q)
        {
            // if ostacle is at right & is the nearest
            if(obCol > c_q && obCol < rightObstacleCol)
                rightObstacleCol = obCol;
            // else if ostacle is at left & is the nearest
            else if(obCol < c_q  &&  obCol > leftObstacleCol)
                leftObstacleCol = obCol;
        }
        
        
        // if obstacle in the same primary diagonal
        if(obRow + obCol == r_q + c_q)
        {
            // if ostacle is above & is the nearest
            if(obRow > r_q && obRow < upLeftObstacleRow)
                upLeftObstacleRow = obRow;
            // else if ostacle is below & is the nearest
            else if(obRow < r_q  &&  obRow > downRightObstacleRow)
                downRightObstacleRow = obRow;
        }
        
        // if obstacle in the same secondary diagonal
        if(obRow - r_q == obCol - c_q)
        {
            // if ostacle is above & is the nearest
            if(obRow > r_q && obRow < upRightObstacleRow)
                upRightObstacleRow = obRow;
            // else if ostacle is below & is the nearest
            else if(obRow < r_q  &&  obRow > downLeftObstacleRow)
                downLeftObstacleRow = obRow;
        }
    }
    
    
    int upCnt     = upObstacleRow - r_q - 1;
    int downCnt   = r_q - downObstacleRow - 1;
    int rightCnt  = rightObstacleCol - c_q - 1;
    int leftCnt   = c_q - leftObstacleCol - 1;
    
    int upLeftCnt;
    if(upLeftObstacleRow == n + 1)  // no obstacle
        upLeftCnt = min(n - r_q, c_q - 1);
    else 
        upLeftCnt = upLeftObstacleRow - r_q - 1;
    
    int downRightCnt;
    if(downRightObstacleRow == 0)  // no obstacle
        downRightCnt = min(r_q - 1, n - c_q);
    else 
        downRightCnt = r_q - downRightObstacleRow - 1;
    
    int downLeftCnt;
    if(downLeftObstacleRow == 0)  // no obstacle
        downLeftCnt = min(r_q - 1, c_q - 1);
    else 
        downLeftCnt = r_q - downLeftObstacleRow - 1;
    
    int upRightCnt;
    if(upRightObstacleRow == n + 1)  // no obstacle
        upRightCnt = min(n - r_q, n - c_q);
    else 
        upRightCnt = upRightObstacleRow - r_q - 1;
    
    
    return (
        upCnt + downCnt + rightCnt + leftCnt + 
        upRightCnt + downLeftCnt + upLeftCnt + downRightCnt
    );
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char** second_multiple_input = split_string(rtrim(readline()));

    int r_q = parse_int(*(second_multiple_input + 0));

    int c_q = parse_int(*(second_multiple_input + 1));

    int** obstacles = malloc(k * sizeof(int*));

    for (int i = 0; i < k; i++) {
        *(obstacles + i) = malloc(2 * (sizeof(int)));

        char** obstacles_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int obstacles_item = parse_int(*(obstacles_item_temp + j));

            *(*(obstacles + i) + j) = obstacles_item;
        }
    }

    int result = queensAttack(n, k, r_q, c_q, k, 2, obstacles);

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
