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

int parse_int(char*);

#define  MAX_LEN   1000
#define  isCapital(x)       (((x) >= 'A') && ((x) <= 'Z'))
#define  isSmall(x)         (((x) >= 'a') && ((x) <= 'z'))
#define  small(x)           ((x) - 'A' + 'a')
#define  capital(x)         ((x) - 'a' + 'A')


char canConvert(char* a, char* b)
{
    int aLen = strlen(a);
    int bLen = strlen(b);
    
    /*
     * dp[i][j] stores if suffex subtring a[i...] can be 
     * modified to match suffex substring b[j...]
     */
    char dp[MAX_LEN + 1][MAX_LEN + 1] = {0};
    dp[aLen][bLen] = 1;
    
    /*
     * for empty substring b[bLen...], substring a[i...] 
     * can match it if and only if a[i...] contains only 
     * lowercase characters
     */
    for(int aIdx = aLen - 1; aIdx >= 0 && isSmall(a[aIdx]); aIdx--)
    {
        dp[aIdx][bLen] = 1;
    }
    
    /* fill remaining array */
    for(int bIdx = bLen - 1; bIdx >= 0; bIdx--)
    {
        for(int aIdx = aLen - 1; aIdx >= 0; aIdx--)
        {
            if(a[aIdx] == b[bIdx])
            {
                dp[aIdx][bIdx] = dp[aIdx + 1][bIdx + 1];
            }
            else if(isCapital(a[aIdx]))
            {
                dp[aIdx][bIdx] = 0;
            }
            else if(capital(a[aIdx]) == b[bIdx])
            {
                dp[aIdx][bIdx] = (
                    dp[aIdx + 1][bIdx + 1] ||
                    dp[aIdx + 1][bIdx]
                );
            }
            else 
            {
                dp[aIdx][bIdx] = dp[aIdx + 1][bIdx];
            }
        }
    }
    
    return dp[0][0];
}


/*
 * Complete the 'abbreviation' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING a
 *  2. STRING b
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
char* abbreviation(char* a, char* b) 
{
    static char* res[2] = {"NO", "YES"};
        
    return res[canConvert(a, b)];
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char* a = readline();

        char* b = readline();

        char* result = abbreviation(a, b);

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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
