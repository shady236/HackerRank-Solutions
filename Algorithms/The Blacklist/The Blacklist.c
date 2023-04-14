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

#define  MAX_N       (20)
#define  MAX_K       (10)
#define  MAX_K_MASK  (((1) << (MAX_K)) - 1)

#define  SET_BIT(x, n)      (x |=  ((1) << (n)))
#define  CLR_BIT(x, n)      (x &= ~((1) << (n)))
#define  GET_BIT(x, n)      (((x) >> (n)) & (1))

int min(int a, int b) {
    if (a > b) {
        return b;
    }
    return a;
}

/*
 * Complete the 'blacklist' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY amounts as parameter.
 */

int blacklist(int amounts_rows, int amounts_columns, int** amounts) {
    int k = amounts_rows;
    int n = amounts_columns;
    int kMaskMax = (1 << k) - 1;
    
    static int minCost[MAX_N + 1][MAX_K][MAX_K_MASK + 1];
    
    for (int kItr = 0; kItr < k; kItr++) {
        for (int used = 0; used <= kMaskMax; used++) {
            if (GET_BIT(used, kItr) == 0) {
                minCost[0][kItr][used] = INT32_MAX;
            }
            else {
                minCost[0][kItr][used] = 0;
            }
        }
    }
    
    
    for (int i = 1; i <= n; i++) {
        for (int kItr = 0; kItr < k; kItr++) {
            for (int used = 0; used <= kMaskMax; used++) {
                if (GET_BIT(used, kItr) == 0) {
                    minCost[i][kItr][used] = INT32_MAX;
                    continue;
                }
                
                minCost[i][kItr][used] = minCost[i - 1][kItr][used] + amounts[kItr][i - 1];
                
                int usedWithountK = used;
                CLR_BIT(usedWithountK, kItr);
                
                for (int kComp = 0; kComp < k; kComp++) {
                    if (GET_BIT(usedWithountK, kComp) == 0) {
                        continue;
                    }
                    
                    minCost[i][kItr][used] = min(
                        minCost[i][kItr][used], 
                        minCost[i - 1][kComp][usedWithountK] + amounts[kItr][i - 1]
                    );
                }
            }
        }
    }
    
    
    int res = INT32_MAX;
    
    for (int kItr = 0; kItr < k; kItr++) {
        for (int used = 0; used <= kMaskMax; used++) {
            res = min(res, minCost[n][kItr][used]);
        }
    }
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    int** amounts = malloc(k * sizeof(int*));

    for (int i = 0; i < k; i++) {
        *(amounts + i) = malloc(n * (sizeof(int)));

        char** amounts_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < n; j++) {
            int amounts_item = parse_int(*(amounts_item_temp + j));

            *(*(amounts + i) + j) = amounts_item;
        }
    }

    int result = blacklist(k, n, amounts);

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
