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
 * Complete the 'morganAndString' function below.
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
char* morganAndString(char* a, char* b)
{
    int aLen = strlen(a);
    int bLen = strlen(b);

    static char resultStr[200001];
    for(int i = 0; i < 200001; i++)
        resultStr[i] = 0;
    
    int resultIdx = 0;
    int aIdx = 0;
    int bIdx = 0;
    
    while(aIdx < aLen  &&  bIdx < bLen)
    {
        if(a[aIdx] > b[bIdx])
        {
            resultStr[resultIdx] = b[bIdx];
            bIdx++;
            resultIdx++;
        }
        else if(a[aIdx] < b[bIdx])
        {
            resultStr[resultIdx] = a[aIdx];
            aIdx++;
            resultIdx++;
        }
        else
        {
            resultStr[resultIdx] = a[aIdx];
            resultIdx++;
            int  copiedCnt = 1;
            char continueCpyFlag = 1;
            
            int diffIdx = -1;
            int l=1;
            while((aIdx + l < aLen)  &&  (bIdx + l < bLen))
            {
                if(a[aIdx + l] != b[bIdx + l])
                {
                    diffIdx = l;
                    break; 
                }
                else if(continueCpyFlag && a[aIdx + l] <= a[aIdx + l - 1])
                {
                    resultStr[resultIdx] = a[aIdx + l];
                    resultIdx++;
                    copiedCnt++;
                }
                else
                {
                    continueCpyFlag = 0;
                }
                l++;
            }
            
            if(diffIdx != -1)
            {
                if(a[aIdx + diffIdx] > b[bIdx + diffIdx])
                    bIdx += copiedCnt;
                else 
                    aIdx += copiedCnt;
            }
            else
            {
                if(aLen - aIdx > bLen - bIdx)
                    aIdx += copiedCnt;
                else
                    bIdx += copiedCnt;
            }
        }
    }
    
    /* copy from not completed string */
    if(aIdx < aLen)
        strcat(resultStr, a + aIdx);
    else if(bIdx < bLen)
        strcat(resultStr, b + bIdx);
    
    return resultStr;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char* a = readline();

        char* b = readline();

        char* result = morganAndString(a, b);

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
