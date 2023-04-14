#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

long long elementVal(long long idx)
{
    switch (idx % 4)
    {
        case 0:
            return idx;
        break;
        
        case 1:
            return 1;
        break;
        
        case 2:
            return idx + 1;
        break;
        
        case 3:
            return 0;
        break;
    }
    return 0;
}

// Complete the xorSequence function below.
long long xorSequence(long long l, long long r)
{
    long long result = 0;
    
    while((l % 4 != 0)  &&  (l <= r))
    {
        result ^= elementVal(l);
        l++;
    }
    
    
    while((r % 4 != 3)  &&  (r >= l))
    {
        result ^= elementVal(r);
        r--;
    }
    
    long long cyclesCount = (r - l + 1)>>2;
    if(r > l && cyclesCount % 2 == 1)    result ^= 2;
    
    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* q_endptr;
    char* q_str = readline();
    int q = strtol(q_str, &q_endptr, 10);

    if (q_endptr == q_str || *q_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** lr = split_string(readline());

        char* l_endptr;
        char* l_str = lr[0];
        long long l = strtoll(l_str, &l_endptr, 0);

        if (l_endptr == l_str || *l_endptr != '\0') { exit(EXIT_FAILURE); }

        char* r_endptr;
        char* r_str = lr[1];
        long long r = strtoll(r_str, &r_endptr, 0);

        if (r_endptr == r_str || *r_endptr != '\0') { exit(EXIT_FAILURE); }

        long long result = xorSequence(l, r);

        fprintf(fptr, "%lld\n", result);
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
