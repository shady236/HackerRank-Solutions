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

#define  MAX_LEN    (100000)
#define  maxComp(l)    ((((long)l) * ((l) - 1ULL)) >> 1)

int minComp(int len)
{
    static int minCmp[MAX_LEN + 1] = {-1};
    
    if(minCmp[0] == -1)
    {
        minCmp[0] = 0;
        minCmp[1] = 0;
        
        for(int l = 2; l <= MAX_LEN; l++)
        {
            int half1 = l>>1;
            int half2 = l - 1 - half1;
            
            minCmp[l] = minCmp[half1] + minCmp[half2] + l - 1;
        }
    }
    
    return minCmp[len];
}


void getLenaArr(int len, int cmp, int strt, int end, int* arr)
{
    if(len == 0)
        return;
    if(len == 1)
    {
        arr[0] = strt;
        return;
    }
    
    cmp -= len - 1;
    
    for(int i = strt; i <= end; i++)
    {
        int lessSize = i - strt;
        int moreSize = end - i;
        
        long lessCmpMin = minComp(lessSize);
        long lessCmpMax = maxComp(lessSize);
        long moreCmpMin = minComp(moreSize);
        long moreCmpMax = maxComp(moreSize);
        
        long cmpMin  = lessCmpMin + moreCmpMin;
        long cmpMax  = lessCmpMax + moreCmpMax;
        
        if(cmp >= cmpMin && cmp <= cmpMax)
        {
            arr[0] = i;
            
            long lessCmp = (lessCmpMin + lessCmpMax) >> 1; 
            long moreCmp;
            do
            {
                lessCmp = (lessCmpMin + lessCmpMax) >> 1;
                moreCmp = cmp - lessCmp;
                
                if(moreCmp >= moreCmpMin || moreCmp >= moreCmpMax)
                    break;
                else if(moreCmp < moreCmpMin)
                    lessCmpMax = lessCmp;
                else 
                    lessCmpMin = lessCmp;
            }while(1);
            
            
            getLenaArr(lessSize, lessCmp, strt, i - 1, arr + 1);
            getLenaArr(moreSize, moreCmp, i + 1, end, arr + lessSize + 1);
            break;
        }
    }
}


void lenaArr(int l, int c)
{
    if(c < minComp(l) || c > maxComp(l))
    {
        printf("-1\n");
        return;
    }
    
    int* arr = malloc(l * sizeof(int));
    getLenaArr(l, c, 1, l, arr);
    
    for(int i = 0; i < l; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    free(arr);
}



int main()
{
    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int l = parse_int(*(first_multiple_input + 0));

        int c = parse_int(*(first_multiple_input + 1));

        // Write your code here
        lenaArr(l, c);
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
