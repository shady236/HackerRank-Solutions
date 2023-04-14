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


char sgn[15][15];

void sgnInit(void)
{
    sgn[0][0] = 0;
    sgn[0][1] = 0;
    sgn[1][0] = 0;
    sgn[1][1] = 0;
    sgn[2][0] = 1;
    sgn[0][2] = 1;
    
    for(int diagonal=3; diagonal<15; diagonal++)
    {
        for(int i=0; i<=diagonal; i++)
        {
            char x = diagonal - i;
            char y = i;
            
            char nextPosSgn[4] = {100, 100, 100, 100};
            
            if(x >= 2 && y >= 1)
                nextPosSgn[0] = sgn[x - 2][y - 1];
            
            if(x >= 2 && y < 14)
                nextPosSgn[1] = sgn[x - 2][y + 1];
            
            if(x >= 1 && y >= 2)
                nextPosSgn[2] = sgn[x - 1][y - 2];
            
            if(x < 14 && y >= 2)
                nextPosSgn[3] = sgn[x + 1][y - 2];
            
            char min = 0;
            while(true)
            {
                int i;
                for(i=0; i<4; i++)
                {
                    if(min == nextPosSgn[i])
                    {
                        min++;
                        break;
                    }
                }
                if(i == 4)  break;
            }
            sgn[x][y] = min;
        }
    }
    
    
    for(int diagonal=1; diagonal<15; diagonal++)
    {
        for(int i=0; i < 15-diagonal; i++)
        {
            char x = diagonal + i;
            char y = 14 - i;
            
            char nextPosSgn[4] = {100, 100, 100, 100};
            
            if(x >= 2 && y >= 1)
                nextPosSgn[0] = sgn[x - 2][y - 1];
            
            if(x >= 2 && y < 14)
                nextPosSgn[1] = sgn[x - 2][y + 1];
            
            if(x >= 1 && y >= 2)
                nextPosSgn[2] = sgn[x - 1][y - 2];
            
            if(x < 14 && y >= 2)
                nextPosSgn[3] = sgn[x + 1][y - 2];
            
            char min = 0;
            while(true)
            {
                int i;
                for(i=0; i<4; i++)
                {
                    if(min == nextPosSgn[i])
                    {
                        min++;
                        break;
                    }
                }
                if(i == 4)  break;
            }
            sgn[x][y] = min;
        }
    }
    

    
    for(int i=0; i<15; i++)
    {
        for(int j=0; j<15; j++)
            printf("%d ", sgn[i][j]);
        printf("\n");
    }
}

/*
 * Complete the 'chessboardGame' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER x
 *  2. INTEGER y
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
char* chessboardGame(int x, int y)
{
    static char first[] = "First";
    static char secnd[] = "Second";
    
    if(sgn[x-1][y-1])       return first;
    return secnd;
    
    // x = (x+1)>>1;
    // y = (y+1)>>1;
    
    // if(x % 2 == 0)       return first;
    // if(y % 2 == 0)       return first;
    // return secnd;
}

int main()
{
    sgnInit();
    
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int x = parse_int(*(first_multiple_input + 0));

        int y = parse_int(*(first_multiple_input + 1));

        char* result = chessboardGame(x, y);

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
