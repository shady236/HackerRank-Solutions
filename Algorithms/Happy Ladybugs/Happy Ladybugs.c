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

/*
 * Complete the 'happyLadybugs' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING b as parameter.
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
char* happyLadybugs(char* b)
{
    char* result = malloc(4 * sizeof(char));
    
    char isUnderscoreFound = 0;
    int  freq[26] = {0};
    
    for(int i = 0; b[i]; i++)
    {
        if(b[i] == '_')
            isUnderscoreFound = 1;
        else 
            freq[b[i] - 'A']++;
    }
    
    char isCharUnique[26] = {0};
    for(int i = 0; i < 26; i++)
    {
        if(freq[i] == 1)
            isCharUnique[i] = 1;
    }
    
    char isAnyCharUnique = 0;
    for(int i = 0; i < 26; i++)
    {
        if(isCharUnique[i])
        {
            isAnyCharUnique = 1;
            break;
        }
    }
    
    if(isAnyCharUnique)
    {
        strcpy(result, "NO");
    }
    else if(!isUnderscoreFound)
    {
        char isSwapRequired = 0;
        for(int i = 1; b[i]; i++)
        {
            if(b[i] != b[i - 1] && b[i] != b[i + 1])
            {
                isSwapRequired = 1;
                break;
            }
        }
        
        isSwapRequired |= (b[0] != b[1]);
        
        if(isSwapRequired)
            strcpy(result, "NO");
        else
            strcpy(result, "YES");
    }
    else
    {
        strcpy(result, "YES");
    }
    
    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int g = parse_int(ltrim(rtrim(readline())));

    for (int g_itr = 0; g_itr < g; g_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char* b = readline();

        char* result = happyLadybugs(b);

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
