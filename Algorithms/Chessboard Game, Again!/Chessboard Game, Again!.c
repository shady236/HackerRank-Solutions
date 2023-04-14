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
}

/*
 * Complete the 'chessboardGame' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts 2D_INTEGER_ARRAY coins as parameter.
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
char* chessboardGame(int coins_rows, int coins_columns, int** coins)
{
    static char first[] = "First";
    static char secnd[] = "Second";
    
    int res = 0;
    for(int i=0; i<coins_rows; i++)
        res ^= sgn[coins[i][0] - 1][coins[i][1] - 1];
    
    if(res)   return first;
    return secnd;
}

int main()
{
    sgnInit();
    
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int k = parse_int(ltrim(rtrim(readline())));

        int** coins = malloc(k * sizeof(int*));

        for (int i = 0; i < k; i++) {
            *(coins + i) = malloc(2 * (sizeof(int)));

            char** coins_item_temp = split_string(rtrim(readline()));

            for (int j = 0; j < 2; j++) {
                int coins_item = parse_int(*(coins_item_temp + j));

                *(*(coins + i) + j) = coins_item;
            }
        }

        char* result = chessboardGame(k, 2, coins);

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
