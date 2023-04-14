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


int sgn(int n)
{
    /*
     * for a tower of heiht n, it can be divided into y towers 
     * each of height x, where y * x = n
     * 
     * if <y>, number of towers, is even -> no effect on the
     * game, i.e. winner will remain winner. That's because 
     * the winner will do the same as his opponent does but
     * on another tower of the same height 
     * 
     * otherwise, if <y> is odd, this is actually what will
     * effect the game, count of available odd <y>'s is sgn
     */
    
    int cnt = 0;
    
    while(n % 2 == 0)
    {
        if((n / 2) % 2 == 1)
            cnt++;
        n >>= 1;
    }
    
    int nextPrime = 3;
    while(n > 1)
    {
        if(n % nextPrime == 0)
        {
            if((n / nextPrime) % 2 == 1)
                cnt++;
            n /= nextPrime;
        }
        else
        {
            nextPrime += 2;
        }
    }
    
    return cnt;
}


/*
 * Complete the 'towerBreakers' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int towerBreakers(int arr_count, int* arr) 
{
    int xor = 0;
    for(int i = 0; i < arr_count; i++)
        xor ^= sgn(arr[i]);
    
    if(xor)
        return 1;
    return 2;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int arr_count = parse_int(ltrim(rtrim(readline())));

        char** arr_temp = split_string(rtrim(readline()));

        int* arr = malloc(arr_count * sizeof(int));

        for (int i = 0; i < arr_count; i++) {
            int arr_item = parse_int(*(arr_temp + i));

            *(arr + i) = arr_item;
        }

        int result = towerBreakers(arr_count, arr);

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
