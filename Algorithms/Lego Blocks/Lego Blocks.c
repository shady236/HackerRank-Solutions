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

#define  MOD        (1000000007ULL)


int power(int a, int p)
{
    if(p == 0)
        return 1;
    
    int pHalf = p>>1;
    
    unsigned long long res = power(a, pHalf);
    res *= res;
    res %= MOD;
    
    // if power is odd, multiply by a
    if(p % 2 == 1)
        res *= a;
    res %= MOD;
    
    return res;
}


/*
 * caculate count of all poaaible layouts for a wall of 
 * width w, regardless of what is the below row, 
 * i.e. regardless of good or bad latouts
 */
int rowConfgCnt(int w)
{
    static int dp[1001] = {0, 1, 2, 4, 8};
    
    if(dp[w] == 0)
    {
        for(int i = 5; i < 1001; i++)
        {
            dp[i] = ((unsigned long long)
                dp[i - 1] + 
                dp[i - 2] + 
                dp[i - 3] + 
                dp[i - 4]
            ) % MOD;
        }
    }
    
    return dp[w];
}


/*
 * calxulate count of all (good + bad) possible layouts for
 * a wall of heigth n and width m
 */
void initTotalDp(int n, int m, int* dp)
{
    for(int w = 1; w <= m; w++)
        dp[w] = power(rowConfgCnt(w), n);
}


int goodWallConfgCnt(int n, int m, int* totDp)
{
    /* 
     * goodDp[w] stores good walls layout count of width w 
     * and height n
     */
    int goodDp[1001] = {0};
    
    for(int w = 1; w <= m; w++)
    {
        unsigned long long goodCnt = totDp[w];
        
        /* 
         * eleminate number of bad walls 
         * 
         * vertical line across all rows divides the wall
         * into two right and left wall 
         * 
         * for a vertiacal line at distance v:
         *   - right wall will be of width w - v
         *   - left  wall will be of width v
         * 
         * so, for right wall:
         *   - total wall layouts count is totDp[w - v]
         *   - good wall layouts count is goodDp[w - v]
         * 
         * for left wall:
         *   - total wall layouts count is totDp[v]
         *   - good wall layouts count is goodDp[v]
         * 
         * 
         * multiple vertical lines are possible to generate
         * bad layouts. so, for vertical line at v, right 
         * and left walls can be bad or good.
         * 
         * But to count each bad layout only one time, 
         * we have to conider left wall of good layouts only
         * and right wall of good and bad layouts, so bad 
         * layouts for vertcal lije at v is: 
         *            totDp[w - v] * goodDp[v]  
         * 
         * this way includes vertical lines to the right
         * and excludes vertical lines to the left, so that
         * vertical lines combinations are included only 
         * once at the most right vertical line
         */
        for(int v = 1; v < w; v++)
        {
            goodCnt += MOD * MOD;   // to avoid -ve values
            
            // eleminate bad layouts
            goodCnt -= ((unsigned long long)
                totDp[w - v] * 
                goodDp[v]
            );
            
            goodCnt %= MOD;
        }
        
        goodDp[w] = goodCnt;
    }
    
    return goodDp[m];
}


/*
 * Complete the 'legoBlocks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 */

int legoBlocks(int n, int m) 
{
    /* 
     * totDp[w] stores all walls layout count (good + bad)
     * of width w and height n
     */
    int totDp[1001] = {0};
    
    initTotalDp(n, m, totDp);
    
    return goodWallConfgCnt(n, m, totDp);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        int result = legoBlocks(n, m);

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
