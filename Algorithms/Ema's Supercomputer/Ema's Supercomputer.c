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

#define  MAX_GRID_SIZ  15

typedef struct 
{
    int area;
    int grid[MAX_GRID_SIZ][MAX_GRID_SIZ];
}Plus_t;

/*
 * Complete the 'twoPluses' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY grid as parameter.
 */

int twoPluses(int grid_count, char** grid)
{
    Plus_t  totalPlus[1240] = {0};
    int     totalPlusCount  =  0 ;
    
    for(int i = 0; i < grid_count; i++)
    {
        for(int j = 0; grid[0][j]; j++)
        {
            for(int shift = 0; ; shift++)
            {
                int strtI = i - shift;
                int endI  = i + shift;
                
                int strtJ = j - shift;
                int endJ  = j + shift;
                
                if(strtI <  0)               break;
                if(endI  >= grid_count)      break;
                if(strtJ <  0)               break;
                if(grid[i][endJ]  != 'G')    break;
                if(grid[i][strtJ] != 'G')    break;
                if(grid[strtI][j] != 'G')    break;
                if(grid[endI][j]  != 'G')    break;
                
                for(int iCntr = strtI; iCntr <= endI; iCntr++)
                    totalPlus[totalPlusCount].grid[iCntr][j] = 1;
                
                for(int jCntr = strtJ; jCntr <= endJ; jCntr++)
                    totalPlus[totalPlusCount].grid[i][jCntr] = 1;
                totalPlusCount++;
            }
        }
    }
    
    for(int p = 0; p < totalPlusCount; p++)
    {
        totalPlus[p].area = 0;
        for(int i = 0; i < grid_count; i++)
        {
            for(int j = 0; grid[0][j]; j++)
            {
                totalPlus[p].area += totalPlus[p].grid[i][j];
                printf("%d ", totalPlus[p].grid[i][j]);
            }
            printf("\n");
        }
        printf("%d\n", totalPlus[p].area);
    }
    
    int maxProduct = 0;
    for(int p1 = 0; p1 < totalPlusCount; p1++)
    {
        for(int p2 = p1 + 1; p2 < totalPlusCount; p2++)
        {
            //chaeck if no overlap
            char isThereOverlap = 0;
            for(int i = 0; i < grid_count && !isThereOverlap; i++)
            {
                for(int j = 0; grid[0][j] && !isThereOverlap; j++)
                {
                    isThereOverlap = (
                        totalPlus[p1].grid[i][j] && 
                        totalPlus[p2].grid[i][j]
                    );
                }
            }
            
            if(!isThereOverlap)
            {
                int curProduct = totalPlus[p1].area * totalPlus[p2].area;
                if(maxProduct < curProduct)
                    maxProduct = curProduct;
            }
        }
    }
    
    
    return maxProduct;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int m = parse_int(*(first_multiple_input + 1));

    char** grid = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* grid_item = readline();

        *(grid + i) = grid_item;
    }

    int result = twoPluses(n, grid);

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
