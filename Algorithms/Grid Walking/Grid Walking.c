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

#define  MOD      (1000000007)

unsigned long long movesCnt[102][102][301];

void initMovesCnt(void)
{
    for (int m = 0; m <= 300; m++) 
    {
        for (int d = 1; d <= 100; d++) 
        {
            for (int x = 1; x <= d; x++) 
            {
                if(m == 0)
                    movesCnt[d][x][m] = 1;
                else 
                    movesCnt[d][x][m] = (
                        movesCnt[d][x - 1][m - 1] + 
                        movesCnt[d][x + 1][m - 1]
                    ) % MOD;
            }
        }
    }
}


int min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}


int fast_pow(long long base, long long n) 
{
    if(n == 0)
       return 1;
    if(n == 1)
        return base;
    
    long long half = fast_pow(base, n>>1);
    if(n % 2 == 0)
        return (half * half) % MOD;
    else
        return (((half * half) % MOD) * base) % MOD;
}


int MMI(int n)
{
    static int lockupTable[151] = {-1};
    
    if(lockupTable[0] == -1)
    {
        for(int i = 0; i <= 150; i++)
            lockupTable[i] = fast_pow(i, MOD - 2);
    }
    
    return lockupTable[n];
}


unsigned long long ncr(int n, int r)
{
    r = min(r, n - r);
    unsigned long long res = 1;
    
    for(int i = 1; i <= r; i++)
    {
        res *= n;
        res %= MOD;
        res *= MMI(i);
        res %= MOD;
        n--;
    }
    
    return res;
}


unsigned long long gridWalkingDp(int m, int* x, int* d, int size, int idx, unsigned long long dp[11][301]) 
{
    if(idx == size - 1)
        return movesCnt[d[idx]][x[idx]][m];
    
    if(m == 0)
        return 1;
    
    if(dp[idx][m] != -1)
        return dp[idx][m];
    
    unsigned long long res = 0;
    
    for(int i = 0; i <= m; i++)
    {
        unsigned long long add = ncr(m, i) % MOD;
        add *= movesCnt[d[idx]][x[idx]][i];
        add %= MOD;
        add *= gridWalkingDp(m - i, x, d, size, idx + 1, dp);
        add %= MOD;
        
        res += add;
        res %= MOD;
    }
    
    dp[idx][m] = res;
    return res;
}


/*
 * Complete the 'gridWalking' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER m
 *  2. INTEGER_ARRAY x
 *  3. INTEGER_ARRAY d
 */

int gridWalking(int m, int x_count, int* x, int d_count, int* d) 
{
    unsigned long long dp[10][301];
    for(int i = 0; i < x_count; i++) 
    {
        for(int j = 0; j <= m; j++) 
            dp[i][j] = -1;
    }
    
    return gridWalkingDp(m, x, d, x_count, 0, dp);
}

int main()
{
    initMovesCnt();
    
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        char** x_temp = split_string(rtrim(readline()));

        int* x = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int x_item = parse_int(*(x_temp + i));

            *(x + i) = x_item;
        }

        char** D_temp = split_string(rtrim(readline()));

        int* D = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int D_item = parse_int(*(D_temp + i));

            *(D + i) = D_item;
        }

        int result = gridWalking(m, n, x, n, D);

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
