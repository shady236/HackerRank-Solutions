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
unsigned long long parse_long_long(char*);

/*
 * Complete the 'whatsNext' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void whatsNext(int arr_count, unsigned long long* arr)
{
    if(arr_count%2 && arr_count>1)
    {
        if(arr[arr_count-2] > 1)
        {
            arr[arr_count-1]--;
            arr[arr_count-2]--;
            
            if(arr[arr_count-1])
                printf("%u\n", arr_count+2);
            else
                printf("%u\n", arr_count+1);
            
            for(int i=0;i<arr_count-1; i++)
                printf("%llu ", arr[i]);
            printf("1 1");
            if(arr[arr_count-1])
                printf(" %llu", arr[arr_count-1]);
        }
        else
        {
            arr[arr_count-1]--;
            arr[arr_count-3]++;
            
            if(arr[arr_count-1])
                printf("%u\n", arr_count);
            else
                printf("%u\n", arr_count-1);
            
            for(int i=0;i<arr_count-1; i++)
                printf("%llu ", arr[i]);
            if(arr[arr_count-1])
                printf("%llu", arr[arr_count-1]);
        }
    }
    else if(arr_count==1)
    {
        if(arr[0]>1)
            printf("3\n");
        else
            printf("2\n");
        
        printf("1 1");
        if(arr[0] > 1)
            printf(" %llu", arr[0]-1);
    }
    else if(arr_count>2)
    {
        if(arr[arr_count-3] > 1)
        {
            arr[arr_count-2]--;
            arr[arr_count-3]--;
            
            if(arr[arr_count-2])
                printf("%u\n", arr_count+1);
            else
                printf("%u\n", arr_count);
            
            for(int i=0;i<arr_count-2; i++)
                printf("%llu ", arr[i]);
            printf("1 ");
            printf("%llu", arr[arr_count-1]+1);    
            if(arr[arr_count-2])
                printf(" %llu", arr[arr_count-2]);
        }
        else
        {
            arr[arr_count-2]--;
            arr[arr_count-4]++;
            arr[arr_count-3] += arr[arr_count-1];
            
            if(arr[arr_count-2])
                printf("%u\n", arr_count-1);
            else
                printf("%u\n", arr_count-2);
            
            for(int i=0;i<arr_count-2; i++)
                printf("%llu ", arr[i]);
            if(arr[arr_count-2])
                printf("%llu", arr[arr_count-2]);
        }
    }
    else
    {
        if(arr[0]>1)
            printf("3\n");
        else
            printf("2\n");
        
        printf("1 %llu", arr[1]+1);
        if(arr[0]>1)
            printf(" %llu", arr[0]-1);
    }
    printf("\n");
}

int main()
{
    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int arr_count = parse_int(ltrim(rtrim(readline())));

        char** arr_temp = split_string(rtrim(readline()));

        unsigned long long* arr = malloc(arr_count * sizeof(unsigned long long));

        for (int i = 0; i < arr_count; i++) {
            unsigned long long arr_item = parse_long_long(*(arr_temp + i));
            // printf("debug %llu\n", arr_item);
            // printf("debug %s\n", *(arr_temp + i));
            *(arr + i) = arr_item;
        }

        whatsNext(arr_count, arr);
    }

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


unsigned long long parse_long_long(char* str) {
    char* endptr;
    unsigned long long value = strtoull(str, &endptr, 0);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
