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


int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

/*
 * Complete the 'biggerIsGreater' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING w as parameter.
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

char* biggerIsGreater(char* w)
{
    // strlen("no answer") = 9
    int len = strlen(w);
    char* result = malloc(max(len + 1, 10) * sizeof(char));
    
    result[len] = 0;
    
    int i;
    for(i = len - 1; i > 0; i--)
    {
        if(w[i] <= w[i-1])
            continue;
        
        
        for(int j = 0; j < i - 1; j++)
            result[j] = w[j];
        
        
        int idxOfMin = i;
        for(int j = i + 1; j < len; j++)
        {
            if((w[j] > w[i-1]) && (w[j] <= w[idxOfMin]))
                idxOfMin = j;
        }
        
        result[i - 1] = w[idxOfMin];
        
        int resultIdx = i;
        for(int j = len - 1; j >= i; j--)
        {
            if(j == idxOfMin)       result[resultIdx] = w[i-1];
            else                    result[resultIdx] = w[j];
            resultIdx++;
        }
        
        break;
    }
    
    // if w[i] <= w[i-1] for i > 0
    if(i == 0)
        strcpy(result, "no answer");
    
    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int T = parse_int(ltrim(rtrim(readline())));

    for (int T_itr = 0; T_itr < T; T_itr++) {
        char* w = readline();

        char* result = biggerIsGreater(w);

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
