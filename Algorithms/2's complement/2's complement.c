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
long parse_long(char*);

/*
 * Complete the 'twosCompliment' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER a
 *  2. LONG_INTEGER b
 */

#define  GET_BIT(x, bit)        (((x)>>(bit)) & 1)

unsigned long long ncr(int n, int r)
{
    unsigned long long res = 1;
    for(int i=1; i<=r; i++)
    {
        res *= n;
        res /= i;
        n--;
    }
    return res;
}

unsigned long long twosCompliment(long a, long b)
{
    unsigned long long count = 0;
    if(a >= 0)
    {
        char prevOnes = 0;
        for(char i=31; i>=0; i--)
        {
            if(GET_BIT(b, i) == 1)
            {
                count += (i + 1) * (1 + prevOnes);
                for(int j=2; j<=i; j++)
                    count += (prevOnes + j) * ncr(i, j);
                prevOnes++;
            }
        }
        
        if(a)
        {
            a--;
            prevOnes = 0;
            for(char i=31; i>=0; i--)
            {
                if(GET_BIT(a, i) == 1)
                {
                    count -= (i + 1) * (1 + prevOnes);
                    for(int j=2; j<=i; j++)
                        count -= (prevOnes + j) * ncr(i, j);
                    prevOnes++;
                }
            }
        }
    }
    else if(b >= 0)
    {
        char prevOnes = 0;
        for(char i=31; i>=0; i--)
        {
            if(GET_BIT(b, i) == 1)
            {
                count += (i + 1) * (1 + prevOnes);
                for(int j=2; j<=i; j++)
                    count += (prevOnes + j) * ncr(i, j);
                prevOnes++;
            }
        }
        
        
        a = ~a;
        count += 32;
        prevOnes = 0;
        for(char i=31; i>=0; i--)
        {
            if(GET_BIT(a, i) == 1)
            {
                unsigned long long cnt = (i + 1) * (1 + prevOnes);
                for(int j=2; j<=i; j++)
                    cnt += (prevOnes + j) * ncr(i, j);
                count += 32ULL * (1ULL<<i) - cnt;
                prevOnes++;
            }
        }
    }
    else
    {
        a = ~a;
        count += 32;
        char prevOnes = 0;
        for(char i=31; i>=0; i--)
        {
            if(GET_BIT(a, i) == 1)
            {
                unsigned long long cnt = (i + 1) * (1 + prevOnes);
                for(int j=2; j<=i; j++)
                    cnt += (prevOnes + j) * ncr(i, j);
                count += 32ULL * (1ULL<<i) - cnt;
                prevOnes++;
            }
        }
        
        if(b < -1)
        {
            b++;
            b = ~b;
            count -= 32;
            prevOnes = 0;
            for(char i=31; i>=0; i--)
            {
                if(GET_BIT(b, i) == 1)
                {
                    unsigned long long cnt = (i + 1) * (1 + prevOnes);
                    for(int j=2; j<=i; j++)
                        cnt += (prevOnes + j) * ncr(i, j);
                    count -= 32ULL * (1ULL<<i) - cnt;
                    prevOnes++;
                }
            }
        }
    }
    
    return count;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        long a = parse_long(*(first_multiple_input + 0));

        long b = parse_long(*(first_multiple_input + 1));

        unsigned long long result = twosCompliment(a, b);

        fprintf(fptr, "%llu\n", result);
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

long parse_long(char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
