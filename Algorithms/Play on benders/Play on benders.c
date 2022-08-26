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

typedef struct Node_t
{
    int  childsCnt;
    int* childs;
}Node_t;


void initSgn(int pathsRows, int pathsColumns, int** paths, int sgnLen, int* sgn)
{
    for(int i=1; i<sgnLen; i++)
        sgn[i] = -1;
    sgn[0] = 0;
    
    // Array of nodes, node i for locationn i
    Node_t* Roots = malloc(sgnLen * sizeof(Node_t));
    for(int i=0; i<sgnLen; i++)
    {
        Roots[i].childsCnt = 0;
        Roots[i].childs    = malloc(sizeof(int));
    }
    
    // allocate paths between nodes
    for(int i=0; i<pathsRows; i++)
    {
        int from = paths[i][0];
        int to   = paths[i][1];
        
        Roots[from].childsCnt++;
        Roots[from].childs = realloc(Roots[from].childs, Roots[from].childsCnt * sizeof(int));
        Roots[from].childs[Roots[from].childsCnt-1] = to;
    }
    
    //sgn value of nodes has no childs (no next state) is 0
    for(int i=1; i<sgnLen; i++)
    {
        if(Roots[i].childsCnt == 0)
            sgn[i] = 0;
    }
    
    //other nodes sgn is min +ve not found in neighbors sgn
    char isAllSgnDone = 0;
    while(!isAllSgnDone)
    {
        isAllSgnDone = 1;
        for(int i=1; i<sgnLen; i++)
        {
            if(sgn[i] != -1)   continue;  //valid sgn
            
            int min = 0;
            char isMinValid = 0;
            while(!isMinValid)
            {
                isMinValid = 1;
                char isSgnCantBeFound = 0;
                for(int j=0; j<Roots[i].childsCnt; j++)
                {
                    if(sgn[Roots[i].childs[j]] == min)
                    {
                        isMinValid = 0;
                        min++;
                    }
                    else if(sgn[Roots[i].childs[j]] == -1)
                    {
                        isMinValid = 0;
                        isSgnCantBeFound = 1;
                        break;
                    }
                }
                if(isSgnCantBeFound)      break;
            }
            
            if(isMinValid)     sgn[i] = min;
            else               isAllSgnDone = 0;
        }
    }
}


/*
 * Complete the 'bendersPlay' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY paths
 *  3. INTEGER_ARRAY query
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* bendersPlay(int n, int pathsRows, int pathsColumns, int** paths, int initLocationCnt, int* initLocation)
{
    static char* p1 = "Bumi";
    static char* p2 = "Iroh";
    
    static int sgn[100001] = {-1};
    if(sgn[0] == -1)
        initSgn(pathsRows, pathsColumns, paths, n+1, sgn);
    
    int xor = 0;
    for(int i=0; i<initLocationCnt; i++)
        xor ^= sgn[initLocation[i]];
    
    if(xor)      return p1;
    return p2;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int m = parse_int(*(first_multiple_input + 1));

    int** paths = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        *(paths + i) = malloc(2 * (sizeof(int)));

        char** paths_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int paths_item = parse_int(*(paths_item_temp + j));

            *(*(paths + i) + j) = paths_item;
        }
    }

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int query_count = parse_int(ltrim(rtrim(readline())));

        char** query_temp = split_string(rtrim(readline()));

        int* query = malloc(query_count * sizeof(int));

        for (int i = 0; i < query_count; i++) {
            int query_item = parse_int(*(query_temp + i));

            *(query + i) = query_item;
        }

        char* result = bendersPlay(n, m, 2, paths, query_count, query);

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
