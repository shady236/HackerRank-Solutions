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
    int x, y;
}Square_t;

void inqueue(Square_t* queue, int* queueSize, Square_t* val)
{
    queue[*queueSize].x = val->x; 
    queue[*queueSize].y = val->y;
    (*queueSize)++;
}

Square_t dequeue(Square_t* queue, int* queueSize)
{
    Square_t ret = queue[0];
    (*queueSize)--;
    for(int i=0; i<(*queueSize); i++)
    {
        queue[i] = queue[i+1];
    }
    return ret;
}

int min(int a, int b)
{
    if(a > b)       return b;
    return a;
}

/*
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */

int minimumMoves(int grid_count, char** grid, int startX, int startY, int goalX, int goalY)
{
    int minMoves[100][100] = {0};
    for(int i=0; i<grid_count; i++)
        for(int j=0; j<grid_count; j++)
            minMoves[i][j] = 0xFFFFF;
    minMoves[startX][startY] = 0;
    
    Square_t* lastVisitedSqr = malloc(grid_count * grid_count * sizeof(Square_t));
    lastVisitedSqr[0].x = startX;
    lastVisitedSqr[0].y = startY;
    int lastVisitedCnt = 1;
    
    Square_t* toBeVisitedSqr = malloc(grid_count * grid_count * sizeof(Square_t));
    int toBeVisitedCnt = 0;
    
    while(0xFFFFF == minMoves[goalX][goalY])
    {
        toBeVisitedCnt = 0;
        
        for(int sq=0; sq<lastVisitedCnt; sq++)
        {
            int x = lastVisitedSqr[sq].x; 
            int y = lastVisitedSqr[sq].y;
            
            int i = x , j = y;
            for(; i >= 0 && grid[i][j] != 'X'; i--)
            {
                if(minMoves[i][j] > minMoves[x][y] + 1)
                {
                    minMoves[i][j] = minMoves[x][y] + 1;
                    toBeVisitedSqr[toBeVisitedCnt].x = i;
                    toBeVisitedSqr[toBeVisitedCnt].y = j;
                    toBeVisitedCnt++;
                }
            }
            
            i = x; 
            j = y;
            for(; i < grid_count && grid[i][j] != 'X'; i++)
            {
                if(minMoves[i][j] > minMoves[x][y] + 1)
                {
                    minMoves[i][j] = minMoves[x][y] + 1;
                    toBeVisitedSqr[toBeVisitedCnt].x = i;
                    toBeVisitedSqr[toBeVisitedCnt].y = j;
                    toBeVisitedCnt++;
                }
            }
            
            i = x; 
            j = y;
            for(; j >= 0 && grid[i][j] != 'X'; j--)
            {
                if(minMoves[i][j] > minMoves[x][y] + 1)
                {
                    minMoves[i][j] = minMoves[x][y] + 1;
                    toBeVisitedSqr[toBeVisitedCnt].x = i;
                    toBeVisitedSqr[toBeVisitedCnt].y = j;
                    toBeVisitedCnt++;
                }
            }
            
            i = x; 
            j = y;
            for(; j < grid_count && grid[i][j] != 'X'; j++)
            {
                if(minMoves[i][j] > minMoves[x][y] + 1)
                {
                    minMoves[i][j] = minMoves[x][y] + 1;
                    toBeVisitedSqr[toBeVisitedCnt].x = i;
                    toBeVisitedSqr[toBeVisitedCnt].y = j;
                    toBeVisitedCnt++;
                }
            }
        }
        
        Square_t* tmp  = toBeVisitedSqr;
        toBeVisitedSqr = lastVisitedSqr;
        lastVisitedSqr = tmp;
        
        lastVisitedCnt = toBeVisitedCnt;
    }
    
    return minMoves[goalX][goalY];
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** grid = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* grid_item = readline();

        *(grid + i) = grid_item;
    }

    char** first_multiple_input = split_string(rtrim(readline()));

    int startX = parse_int(*(first_multiple_input + 0));

    int startY = parse_int(*(first_multiple_input + 1));

    int goalX = parse_int(*(first_multiple_input + 2));

    int goalY = parse_int(*(first_multiple_input + 3));

    int result = minimumMoves(n, grid, startX, startY, goalX, goalY);

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
