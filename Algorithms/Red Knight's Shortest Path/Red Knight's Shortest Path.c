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
 * Complete the 'printShortestPath' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER i_start
 *  3. INTEGER j_start
 *  4. INTEGER i_end
 *  5. INTEGER j_end
 */

void printShortestPath(int n, int i_start, int j_start, int i_end, int j_end)
{
    // Print the distance along with the sequence of moves.
    
    int verticalDiff   = abs(i_start - i_end);
    int horizontalDiff = abs(j_start - j_end);
    int verticalMovesCount = verticalDiff>>1;
    
    if(verticalDiff % 2 == 1  ||  (verticalMovesCount % 2 + horizontalDiff) %2 == 1)
    {
        printf("Impossible\n");
        return;
    }
    
    char moves[6][3] = {"UL", "UR", "R", "LR", "LL", "L"};
    int movesFreq[6] = {0};
    
    int movesCount = 0;
    if(horizontalDiff > verticalMovesCount)
        movesCount = (horizontalDiff>>1) + verticalMovesCount - (verticalMovesCount>>1) ;
    else
        movesCount = verticalMovesCount;

    printf("%d\n", movesCount);
    
    while (i_start != i_end)
    {
        if(i_start > i_end && j_start <= j_end && (j_start+1) < n)
        {
            i_start -= 2;
            j_start++;
            movesFreq[1]++;
        }
        else if(i_start > i_end && j_start >= j_end && (j_start-1) > 0)
        {
            i_start -= 2;
            j_start--;
            movesFreq[0]++;
        }
        else if(i_start < i_end && j_start <= j_end && (j_start+1) < n)
        {
            i_start += 2;
            j_start++;
            movesFreq[3]++;
        }
        else if(i_start < i_end && j_start >= j_end && (j_start-1) > 0)
        {
            i_start += 2;
            j_start--;
            movesFreq[4]++;
        }
    }
    
    
    if(j_start > j_end)
        movesFreq[5] = (j_start - j_end)>>1; 
    else
        movesFreq[2] = (j_end - j_start)>>1; 
    
    
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < movesFreq[i]; j++)
            printf("%s ", moves[i]);

}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    char** first_multiple_input = split_string(rtrim(readline()));

    int i_start = parse_int(*(first_multiple_input + 0));

    int j_start = parse_int(*(first_multiple_input + 1));

    int i_end = parse_int(*(first_multiple_input + 2));

    int j_end = parse_int(*(first_multiple_input + 3));

    printShortestPath(n, i_start, j_start, i_end, j_end);

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
