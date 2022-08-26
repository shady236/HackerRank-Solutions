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
    if(a < b)
        return a;
    return b;
}

#define  MAX_N      (51)
#define  MAX_M      (51)
#define  MAX_K      (1000)

int minOperations(char** board, int boardSize, int disRow, int disCol, int k, int dp[MAX_N][MAX_M][MAX_K + 1])
{
    if(dp[disRow][disCol][k] != -1)
        return dp[disRow][disCol][k];
    
    if(disRow + disCol > k)
        return -1;
    
    if(disRow == 0 && disCol == 0)
        return 0;
    
    int p1 = -1;
    if(disRow > 0)
    {
        p1 = (
            minOperations(board, boardSize, disRow - 1, disCol, k - 1, dp) 
        );
        
        if(p1 != -1)
            p1 += (board[disRow - 1][disCol] != 'D');
    }
    
    int p2 = -1;
    if(disCol > 0)
    {
        p2 = (
            minOperations(board, boardSize, disRow, disCol - 1, k - 1, dp) 
        );
        
        if(p2 != - 1)
            p2 += (board[disRow][disCol - 1] != 'R');
    }
    
    int p3 = -1;
    if(disRow + 1 < boardSize)
    {
        p3 = (
            minOperations(board, boardSize, disRow + 1, disCol, k - 1, dp)
        );
        
        if(p3 != -1)
            p3 += (board[disRow + 1][disCol] != 'U');
    }
    
    int p4 = -1;
    if(board[disRow][disCol + 1])
    {
        p4 = (
            minOperations(board, boardSize, disRow, disCol + 1, k - 1, dp) 
        );
        
        if(p4 != -1)
            p4 += (board[disRow][disCol + 1] != 'L');
    }
    
    int res = 100000000;
    if(p1 != -1)
        res = min(res, p1);
    if(p2 != -1)
        res = min(res, p2);
    if(p3 != -1)
        res = min(res, p3);
    if(p4 != -1)
        res = min(res, p4);
    
    
    dp[disRow][disCol][k] = res;
    return res;
}


/*
 * Complete the 'coinOnTheTable' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER m
 *  2. INTEGER k
 *  3. STRING_ARRAY board
 */

int coinOnTheTable(int m, int k, int board_count, char** board) 
{
    int dp[MAX_N][MAX_M][MAX_K + 1];
    
    for(int i = 0; i < board_count; i++)
    {
        for(int j = 0; board[0][j]; j++)
        {
            for(int l = 0; l <= k; l++)
            {
                dp[i][j][l] = -1;
            }
        }
    }
    
    for(int i = 0; i < board_count; i++)
    {
        for(int j = 0; board[0][j]; j++)
        {
            if(board[i][j] == '*')
                return minOperations(board, board_count, i, j, k, dp);
        }
    }
    
    return -1;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int m = parse_int(*(first_multiple_input + 1));

    int k = parse_int(*(first_multiple_input + 2));

    char** board = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* board_item = readline();

        *(board + i) = board_item;
    }

    int result = coinOnTheTable(m, k, n, board);

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
