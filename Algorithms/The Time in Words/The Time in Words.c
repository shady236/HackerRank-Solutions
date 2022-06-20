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
 * Complete the 'timeInWords' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER h
 *  2. INTEGER m
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


char* timeInWords(int h, int m) 
{
    static const char numbers[][13] = {
        "", 
        "one", 
        "two", 
        "three", 
        "four", 
        "five", 
        "six", 
        "seven", 
        "eight", 
        "nine", 
        "ten", 
        "eleven", 
        "twelve", 
        "thirteen", 
        "fourteen", 
        "fifteen", 
        "sixteen", 
        "seventeen", 
        "eighteen", 
        "nineteen", 
        "twenty", 
        "twenty one", 
        "twenty two", 
        "twenty three", 
        "twenty four", 
        "twenty five", 
        "twenty six", 
        "twenty seven", 
        "twenty eight", 
        "twenty nine"
    };
    
    static char str[100] = "";
    
    switch (m)
    {
        case 0:
            strcat(str, numbers[h]);
            strcat(str, " o' clock");
        break;
        
        case 1:
            strcat(str, "one minute past ");
            strcat(str, numbers[h]);
        break;
        
        case 2 ... 14:
            strcat(str, numbers[m]);
            strcat(str, " minutes past ");
            strcat(str, numbers[h]);
        break;
        
        case 15:
            strcat(str, "quarter past ");
            strcat(str, numbers[h]);
        break;
        
        case 16 ... 29:
            strcat(str, numbers[m]);
            strcat(str, " minutes past ");
            strcat(str, numbers[h]);
        break;
        
        case 30:
            strcat(str, "half past ");
            strcat(str, numbers[h]);
        break;
        
        case 31 ... 44:
            strcat(str, numbers[60 - m]);
            strcat(str, " minutes to ");
            strcat(str, numbers[h + 1]);
        break;
        
        case 45:
            strcat(str, "quarter to ");
            strcat(str, numbers[h + 1]);
        break;
        
        case 46 ... 58:
            strcat(str, numbers[60 - m]);
            strcat(str, " minutes to ");
            strcat(str, numbers[h + 1]);
        break;
        
        case 59:
            strcat(str, "one minute to ");
            strcat(str, numbers[h + 1]);
        break;
    }
    
    return str;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int h = parse_int(ltrim(rtrim(readline())));

    int m = parse_int(ltrim(rtrim(readline())));

    char* result = timeInWords(h, m);

    fprintf(fptr, "%s\n", result);

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
