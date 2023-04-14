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


#define  MIN_NUM    (3500)
#define  MAX_NUM    (4500)
#define  MAX_XOR    (1<<13)
#define  MOD        (1000000007)


char isPrimeFun(int n)
{
    if(n <= 1)
        return 0;
    if(n == 2)
        return 1;
    if(n % 2 == 0)
        return 0;
    
    for(int i = 3; i * i <= n; i += 2)
    {
        if(n % i == 0)
            return 0;
    }
    
    return 1;
}


char isPrime[MAX_XOR + 1];
void primesInit(void)
{
    for(int i = 0; i <= MAX_XOR; i++)
        isPrime[i] = isPrimeFun(i);
}

/*
 * Complete the 'primeXor' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

int primeXor(int a_count, int* a) 
{
    int freq[MAX_NUM + 1] = {0};
    for(int i = 0; i < a_count; i++)
        freq[a[i]]++;
    
    int xorFreq[MAX_XOR + 1] = {0};
    int prevXorFreq[MAX_XOR + 1] = {0};
    
    for(int i = MIN_NUM; i <= MAX_NUM; i++)
    {
        long evenCnt = (freq[i]>>1);
        if(evenCnt)
        {
            for(int j = 0; j <= MAX_XOR; j++)
            {
                xorFreq[j] = (xorFreq[j] * (1ULL + evenCnt)) % MOD;
            }
            
            xorFreq[0] = (xorFreq[0] + evenCnt) % MOD;
        }
        
        long oddCnt = (freq[i] + 1) >> 1;
        if(oddCnt)
        {
            for(int j = 0; j < MAX_XOR; j++)
            {
                xorFreq[j ^ i] = (xorFreq[j ^ i] + prevXorFreq[j] * oddCnt) % MOD;
            }
            
            xorFreq[i] = (xorFreq[i] + oddCnt) % MOD;
        }
        
        
        for(int j = 0; j <= MAX_XOR; j++)
            prevXorFreq[j] = xorFreq[j];
    }
    
    
    long primeCnt = 0;
    
    for(int j = 0; j <= MAX_XOR; j++)
    {
        if(isPrime[j])
            primeCnt = (primeCnt + xorFreq[j]) % MOD;
    }
    
    return primeCnt;
}

int main()
{
    primesInit();
    
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** a_temp = split_string(rtrim(readline()));

        int* a = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int a_item = parse_int(*(a_temp + i));

            *(a + i) = a_item;
        }

        int result = primeXor(n, a);

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
