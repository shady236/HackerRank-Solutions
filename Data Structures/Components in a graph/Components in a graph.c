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


int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}


int min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}


int visit(char* isVisited, int node, int** connections, int* connectionsCnt)
{
    isVisited[node] = 1;
    
    int cnt = 1;
    for(int i = 0; i < connectionsCnt[node]; i++)
    {
        int next = connections[node][i];
        
        if(!isVisited[next])
            cnt += visit(isVisited, next, connections, connectionsCnt);
    }
    
    return cnt;
}


int* getComponentsSize(int** connections, int* connectionsCnt, int nodesCnt, int* componentsCnt)
{
    char* isVisited = malloc(nodesCnt * sizeof(int));
    int*  componentSize = malloc(nodesCnt * sizeof(int));
    *componentsCnt = 0;
    
    for(int n = 0; n < nodesCnt; n++)
        isVisited[n] = 0;  // all nodes not visited intially
    
    for(int n = 0; n < nodesCnt; n++)
    {
        if(!isVisited[n])
        {
            componentSize[*componentsCnt] = visit(isVisited, n, connections, connectionsCnt);
            (*componentsCnt)++;
        }
    }
    
    free(isVisited);
    
    return componentSize;
}



/*
 * Complete the 'componentsInGraph' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_INTEGER_ARRAY gb as parameter.
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
int* componentsInGraph(int gb_rows, int gb_columns, int** gb, int* result_count) 
{
    int* nodeConnections[30000] = {NULL};
    int  nodeConnectionsCnt[30000] = {0};
    
    int nodesCnt = 0;
    
    for(int i = 0; i < gb_rows; i++)
    {
        int n1 = gb[i][0] - 1;
        int n2 = gb[i][1] - 1;
        
        nodesCnt = max(nodesCnt, n2 + 1);
        
        nodeConnectionsCnt[n1]++;
        if(nodeConnections[n1] == NULL)
            nodeConnections[n1] = malloc(sizeof(int));
        else 
            nodeConnections[n1] = realloc(nodeConnections[n1], nodeConnectionsCnt[n1] * sizeof(int));
        nodeConnections[n1][nodeConnectionsCnt[n1] - 1] = n2;
        
        
        nodeConnectionsCnt[n2]++;
        if(nodeConnections[n2] == NULL)
            nodeConnections[n2] = malloc(sizeof(int));
        else 
            nodeConnections[n2] = realloc(nodeConnections[n2], nodeConnectionsCnt[n2] * sizeof(int));
        nodeConnections[n2][nodeConnectionsCnt[n2] - 1] = n1;
    }
    

    int componentsCnt;
    int* componentsSizes = getComponentsSize(nodeConnections, nodeConnectionsCnt, nodesCnt, &componentsCnt);
    
    
    int* res = malloc(2 * sizeof(int));
    *result_count = 2;
    
    res[0] = nodesCnt;      // min
    res[1] = 2;             // max
    
    for(int i = 0; i < componentsCnt; i++)
    {
        if(componentsSizes[i] >= 2)
        {
            res[0] = min(res[0], componentsSizes[i]);
            res[1] = max(res[1], componentsSizes[i]);
        }
    }
    
    
    for(int i = 0; i < nodesCnt; i++)
        free(nodeConnections[i]);
    free(componentsSizes);
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int** gb = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(gb + i) = malloc(2 * (sizeof(int)));

        char** gb_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int gb_item = parse_int(*(gb_item_temp + j));

            *(*(gb + i) + j) = gb_item;
        }
    }

    int result_count;
    int* result = componentsInGraph(n, 2, gb, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, " ");
        }
    }

    fprintf(fptr, "\n");

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
