#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);


int min(int a, int b)
{
    if(a > b)
        return b;
    return a;
}


#define  MAX_SISE   (100)
#define  MAX_DIFF   (100)


/*
 * Complete the indianJob function below.
 */

/*
 * Please either make the string static or allocate on the heap. For example,
 * static char str[] = "hello world";
 * return str;
 *
 * OR
 *
 * char* str = "hello world";
 * return str;
 *
 */
char* indianJob(int g, int arr_count, int* arr) {
    /*
     * Write your code here.
     */
    
    static char* resStr[] = {"NO", "YES"};
    
    /*
     * problem csn be simplified to:
     *   - divide arr into two parts with minmum diffrence 
     *     between summtion pf these parts
     *   - if the two parts sum <= g --> answer is YES
     *   - else, answer is NO
     */
    
    
    /*
     * mimDiff[i][diff] stores minimim diffrence between
     * parts that can be get from subarray arr[i...] with 
     * an intial diffrence = diff which can be got from 
     * prefix subarray arr[...i-1]
     */
    int minDiff[MAX_SISE][MAX_DIFF + 1];
    
    /*
     * for last element, it will always be appended to the 
     * lower part, i.e. new diffrence will be 
     * absolute value of prev diffrence - last element 
     */
    for(int diff = 0; diff <= MAX_DIFF; diff++)
    {
        minDiff[arr_count - 1][diff] = (
            abs(diff - arr[arr_count - 1])
        );
    }
    
    
    /*
     * for other element, element can by appended to any of 
     * the two parts provided that the diffrence < MAX_DIFF
     */
    for(int i = arr_count - 2; i >= 0; i--)
    {
        for(int diff = 0; diff <= MAX_DIFF; diff++)
        {
            int nextDiff1 = diff + arr[i];
            int nextDiff2 = abs(diff - arr[i]);
            
            if(nextDiff1 > MAX_DIFF)
            {
                minDiff[i][diff] = minDiff[i + 1][nextDiff2];
            }
            else
            {
                minDiff[i][diff] = min(
                    minDiff[i + 1][nextDiff1],
                    minDiff[i + 1][nextDiff2]
                );
            }
        }
    }
    
    
    
    int sum = 0;
    for(int i = 0; i < arr_count; i++)
    {
        sum += arr[i];
    }
    
    int maxHalf = (sum>>1) + ((minDiff[0][0] + 1)>>1);
    return resStr[maxHalf <= g];
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* t_endptr;
    char* t_str = readline();
    int t = strtol(t_str, &t_endptr, 10);

    if (t_endptr == t_str || *t_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** ng = split_string(readline());

        char* n_endptr;
        char* n_str = ng[0];
        int n = strtol(n_str, &n_endptr, 10);

        if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

        char* g_endptr;
        char* g_str = ng[1];
        int g = strtol(g_str, &g_endptr, 10);

        if (g_endptr == g_str || *g_endptr != '\0') { exit(EXIT_FAILURE); }

        char** arr_temp = split_string(readline());

        int arr[n];

        for (int arr_itr = 0; arr_itr < n; arr_itr++) {
            char* arr_item_endptr;
            char* arr_item_str = arr_temp[arr_itr];
            int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);

            if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0') { exit(EXIT_FAILURE); }

            arr[arr_itr] = arr_item;
        }

        char* result = indianJob(g, n, arr);

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

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
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
