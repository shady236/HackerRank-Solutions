#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

/*
 * Complete the solve function below.
 */
int solve(int t_count, int* t) {
    /*
     * Return the ID
     */
    
    /*
     * diffArr[0] stores number of students that will
     * comolete thier drawing starting with student at 0.
     * 
     * for i > 0 diffArr[i] stores diffrence betwen: 
     *  - number of students that will comolete thier 
     *    drawing starting with student at i. 
     *  - number of students that will comolete thier 
     *    drawing starting with student at i - 1.
     */
    int diffArr[100001] = {0};
    
    
    for(int i = 0; i < t_count; i++)
    {
        /* 
         * if student needs time >= number of students 
         * then student needs time > allowed time
         * Because each student takes 1 minute only to 
         * review its solution, so he catn't complete 
         * his drawing
         */
        if(t[i] >= t_count)
            continue;
        
        if(t[i] == 0)
        {
            diffArr[0]++;
            diffArr[t_count]--;
            continue;
        }
        
        int rangeEnd  = (t_count + i - t[i]) % t_count;
        int rangeStrt = (i + 1) % t_count;
        
        if(rangeEnd >= rangeStrt)
        {
            diffArr[rangeStrt]++;
            diffArr[rangeEnd + 1]--;
        }
        else 
        {
            diffArr[rangeStrt]++;
            diffArr[t_count]--;
            
            diffArr[0]++;
            diffArr[rangeEnd + 1]--;
        }
    }
    
    /* 
     * construct arr of number of students that will 
     * comolete thier drawing starting with any student.
     */
    // int arr[100000] = {0};
    // arr[0] = diffArr[0];
    // for(int i = 1; i < t_count; i++)
    // {
    //     arr[i] = arr[i - 1] + diffArr[i];
    // }
    
    
    int maxIdx = 0;
    int maxCompleted = diffArr[0];
    int currCopleted = diffArr[0];
    for(int i = 1; i < t_count; i++)
    {
        currCopleted += diffArr[i];
        if(currCopleted > maxCompleted)
        {
            maxCompleted = currCopleted;
            maxIdx = i;
        }
    }
    
    return maxIdx + 1;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* t_count_endptr;
    char* t_count_str = readline();
    int t_count = strtol(t_count_str, &t_count_endptr, 10);

    if (t_count_endptr == t_count_str || *t_count_endptr != '\0') { exit(EXIT_FAILURE); }

    char** t_temp = split_string(readline());

    int t[t_count];

    for (int t_itr = 0; t_itr < t_count; t_itr++) {
        char* t_item_endptr;
        char* t_item_str = t_temp[t_itr];
        int t_item = strtol(t_item_str, &t_item_endptr, 10);

        // if (t_item_endptr == t_item_str || *t_item_endptr != '\0') { exit(EXIT_FAILURE); }

        t[t_itr] = t_item;
    }

    int id = solve(t_count, t);

    fprintf(fptr, "%d\n", id);

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
