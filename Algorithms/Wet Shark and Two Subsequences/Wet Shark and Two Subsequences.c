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


#define  MAX_ARR_SIZE       (100)
#define  MOD                (1000000007ULL)


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

void sort(int* arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        int minIdx = i;
        for(int j = i + 1; j < size; j++)
        {
            if(arr[j] < arr[minIdx])
                minIdx = j;
        }
        
        int tmp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = tmp;
    }
}

typedef struct 
{
    int val;
    int freq;
}ValFreqPair_t;

/*
 * Complete the 'twoSubsequences' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY x
 *  2. INTEGER r
 *  3. INTEGER s
 */

int twoSubsequences(int x_count, int* x, int r, int s) 
{
    if((r + s) % 2 == 1)
        return 0;
    if(r <= s)
        return 0;
    
    int aSum = (r + s)>>1;
    int bSum = (r - s)>>1;
    
    sort(x, x_count);
    
    for(int i = x_count - 1; i >= 0; i--)
    {
        if(aSum < x[i])
            x_count--;
        else 
            break;
    }
    
    if(x_count == 0)
        return 0;
    
    ValFreqPair_t  valuesFreq[100];
    valuesFreq[0].val  = x[0];
    valuesFreq[0].freq = 1;
    int valuesCnt = 1;
    
    for(int i = 1; i < x_count; i++)
    {
        if(x[i] == x[i - 1])
            valuesFreq[valuesCnt - 1].freq++;
        else 
        {
            valuesFreq[valuesCnt].val  = x[i];
            valuesFreq[valuesCnt].freq = 1;
            valuesCnt++;
        }
    }
    
    
    /*
     * possibleWays[l][st][sm] stores how many ways we can 
     * get a subsequence of length <l> with sum <sm> from  
     * array <x> starting from the value valuesFreq[st].val
     */
    static int possibleWays[102][102][2002] = {0};
    
    /*
     * for a subsequence of length 0, sum should be 0, 
     * there's only one way to get empty subsequence
     */
    for(int st = 0; st <= valuesCnt; st++)
        possibleWays[0][st][0] = 1;
    
    /*
     * compute other possibleWays for 
     *   - 0 <  len  < x_count
     *   - 0 <= strt < valuesCnt
     *   - 0 <  sum  < aSum
     */
    for(int len = 1; len <= x_count; len++)
    {
        for(int strt = valuesCnt - 1; strt >= 0; strt--)
        {
            for(int sum = 1; sum <= aSum; sum++)
            {
                /*
                 * value valuesFreq[strt].val has freq of 
                 * valuesFreq[strt].freq.
                 * 
                 * we can take upto valuesFreq[strt].freq 
                 * of the value valuesFreq[strt].val to 
                 * get required <sum> 
                 * 
                 * possible ways would be summtion of:
                 *   - taking 0 of valuesFreq[strt].val 
                 *     and take the remainder of both 
                 *     <len> and <sum> from <strt + 1> 
                 *   - taking 1 of valuesFreq[strt].val 
                 *     and take the remainder of both 
                 *     <len> and <sum> from <strt + 1>
                 *   - ...
                 *   - and so on, the end is either:
                 *        1) reaching valuesFreq[strt].freq
                 *        2) remainder len < 0
                 *        3) remainder sum < 0
                 */
                unsigned long long cnt = 0;
                for(int i = 0; i <= valuesFreq[strt].freq; i++)
                {
                    int remLen = len - i;
                    int remSum = sum - i * valuesFreq[strt].val;
                    
                    if(remSum < 0 || remLen < 0)
                        break;
                    
                    cnt += (
                        ncr(valuesFreq[strt].freq, i) * 
                        possibleWays[remLen][strt + 1][remSum]
                    ) % MOD;
                    
                    cnt %= MOD;
                }
                
                possibleWays[len][strt][sum] = cnt;
            }
        }
    }
    
    
    unsigned long long res = 0;
    for(int len = 0; len <= x_count; len++)
    {
        res += (
            possibleWays[len][0][aSum] * 
            (unsigned long long)possibleWays[len][0][bSum]
        ) % MOD;
        
        res %= MOD;
    }
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int m = parse_int(*(first_multiple_input + 0));

    int r = parse_int(*(first_multiple_input + 1));

    int s = parse_int(*(first_multiple_input + 2));

    char** x_temp = split_string(rtrim(readline()));

    int* x = malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        int x_item = parse_int(*(x_temp + i));

        *(x + i) = x_item;
    }

    int result = twoSubsequences(m, x, r, s);

    fprintf(fptr, "%d\n", result);

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
