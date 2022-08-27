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
 * Complete the 'journeyToMoon' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY astronaut
 */

long journeyToMoon(int n, int astronaut_rows, int astronaut_columns, int** astronaut) 
{
    int* astronautConnections[100000] = {NULL};
    int  astronautConnectionsCnt[100000] = {0};
    
    for(int i = 0; i < astronaut_rows; i++)
    {
        int a1 = astronaut[i][0];
        int a2 = astronaut[i][1];
        
        
        astronautConnectionsCnt[a1]++;
        if(astronautConnections[a1] == NULL)
            astronautConnections[a1] = malloc(sizeof(int));
        else 
            astronautConnections[a1] = realloc(astronautConnections[a1], astronautConnectionsCnt[a1] * sizeof(int));
        astronautConnections[a1][astronautConnectionsCnt[a1] - 1] = a2;
        
        
        astronautConnectionsCnt[a2]++;
        if(astronautConnections[a2] == NULL)
            astronautConnections[a2] = malloc(sizeof(int));
        else 
            astronautConnections[a2] = realloc(astronautConnections[a2], astronautConnectionsCnt[a2] * sizeof(int));
        astronautConnections[a2][astronautConnectionsCnt[a2] - 1] = a1;
    }
    

    int nationalitiesCnt;
    int* nationalitiesFreq = getComponentsSize(astronautConnections, astronautConnectionsCnt, n, & nationalitiesCnt);
    
    long res = 0;
    for(int i = 0; i < nationalitiesCnt; i++)
    {
        res += (
            nationalitiesFreq[i] * 
            (n - nationalitiesFreq[i])
        );
    }
    res = res>>1;
    
    
    for(int i = 0; i < n; i++)
        free(astronautConnections[i]);
    free(nationalitiesFreq);
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int p = parse_int(*(first_multiple_input + 1));

    int** astronaut = malloc(p * sizeof(int*));

    for (int i = 0; i < p; i++) {
        *(astronaut + i) = malloc(2 * (sizeof(int)));

        char** astronaut_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int astronaut_item = parse_int(*(astronaut_item_temp + j));

            *(*(astronaut + i) + j) = astronaut_item;
        }
    }

    long result = journeyToMoon(n, p, 2, astronaut);

    fprintf(fptr, "%ld\n", result);

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
