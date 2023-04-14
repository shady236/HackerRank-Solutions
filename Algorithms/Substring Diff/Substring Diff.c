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


int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}


/*
 * Complete the 'substringDiff' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. STRING s1
 *  3. STRING s2
 */

int substringDiff(int k, char* s1, char* s2) 
{
    /*
     * suffixDiff[i][j] stores number of mismatches between 
     * substring s1[i...] & s1[j...]
     */
    short int suffixDiff[1501][1501] = {0};
    
    int len = strlen(s1);
    for(int i = len - 1; i >= 0; i--)
    {
        for(int j = len - 1; j >= 0; j--)
        {
            if(s1[i] == s2[j])
                suffixDiff[i][j] = suffixDiff[i + 1][j + 1];
            else 
                suffixDiff[i][j] = suffixDiff[i + 1][j + 1] + 1;
        }
    }
    
    
    /*
     * maxLengtha[i][j] stores max lenght for substrings 
     * s1[i...] & s1[j...] that has mismatches <= k
     */
    short int maxLengths[1500][1500] = {0};
    for(int i = len - 1; i >= 0; i--)
    {
        for(int j = len - 1; j >= 0; j--)
        {
            /*
             * for two substrings starting at indeces i, j:
             *    - min length is 0 
             *    - max length is len - max(i, j)
             */
            int minL = 0;
            int maxL = len - max(i, j);
            
            int midL, mismatches;
            while(minL <= maxL)
            {
                midL = (minL + maxL)>>1;
                
                mismatches = (
                    suffixDiff[i][j] - 
                    suffixDiff[i + midL][j + midL]
                );
                
                if(mismatches > k)
                {
                    maxL = midL - 1;
                }
                else if(mismatches < k || (midL + 1 <= maxL && suffixDiff[i + midL][j + midL] == suffixDiff[i + midL + 1][j + midL + 1]))
                {
                    minL = midL + 1;
                }
                else 
                {
                    break;
                }
            }
            
            if(mismatches <= k)
                maxLengths[i][j] = midL;
        }
    }
    
    
    /* find max length at all */
    int maxLen = 0;
    for(int i = len - 1; i >= 0; i--)
    {
        for(int j = len - 1; j >= 0; j--)
        {
            if(maxLen < maxLengths[i][j])
                maxLen = maxLengths[i][j];
        }
    }
    
    return maxLen;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int k = parse_int(*(first_multiple_input + 0));

        char* s1 = *(first_multiple_input + 1);

        char* s2 = *(first_multiple_input + 2);

        int result = substringDiff(k, s1, s2);

        fprintf(fptr, "%d\n", result);
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
