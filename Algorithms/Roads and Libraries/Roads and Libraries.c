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


void visit(char* isVisited, int nodesCnt, int node, int** connections, int* connectionsCnt)
{
    isVisited[node] = 1;
    
    for(int i = 0; i < connectionsCnt[node]; i++)
    {
        int next = connections[node][i];
        
        if(!isVisited[next])
            visit(isVisited, nodesCnt, next, connections, connectionsCnt);
    }
}


int networksCnt(int** connections, int* connectionsCnt, int nodesCnt)
{
    // networkID[i] stores network ID of ith node
    char* isVisited = malloc(nodesCnt * sizeof(int));
    
    for(int n = 0; n < nodesCnt; n++)
        isVisited[n] = 0;  // all nodes not visited intially
    
    int netCnt = 0;
    for(int n = 0; n < nodesCnt; n++)
    {
        if(!isVisited[n])
        {
            visit(isVisited, nodesCnt, n, connections, connectionsCnt);
            netCnt++;
        }
    }
    
    free(isVisited);
    
    return netCnt;
}

/*
 * Complete the 'roadsAndLibraries' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER c_lib
 *  3. INTEGER c_road
 *  4. 2D_INTEGER_ARRAY cities
 */

long roadsAndLibraries(int n, long c_lib, long c_road, int cities_rows, int cities_columns, int** cities)
{
    if(c_lib <= c_road)
        return n * c_lib;
    
    int* cityRoads[100000] = {NULL};
    int  cityRoadsCnt[100000] = {0};
    
    for(int i = 0; i < cities_rows; i++)
    {
        int city1 = cities[i][0] - 1;
        int city2 = cities[i][1] - 1;
        
        
        cityRoadsCnt[city1]++;
        if(cityRoads[city1] == NULL)
            cityRoads[city1] = malloc(sizeof(int));
        else 
            cityRoads[city1] = realloc(cityRoads[city1], cityRoadsCnt[city1] * sizeof(int));
        cityRoads[city1][cityRoadsCnt[city1] - 1] = city2;
        
        
        cityRoadsCnt[city2]++;
        if(cityRoads[city2] == NULL)
            cityRoads[city2] = malloc(sizeof(int));
        else 
            cityRoads[city2] = realloc(cityRoads[city2], cityRoadsCnt[city2] * sizeof(int));
        cityRoads[city2][cityRoadsCnt[city2] - 1] = city1;
    }
    
    long netCnt = networksCnt(cityRoads, cityRoadsCnt, n);
    
    
    for(int i = 0; i < n; i++)
    {
        free(cityRoads[i]);
    }
    
    return (netCnt * c_lib + (n - netCnt) * c_road);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        int c_lib = parse_int(*(first_multiple_input + 2));

        int c_road = parse_int(*(first_multiple_input + 3));

        int** cities = malloc(m * sizeof(int*));

        for (int i = 0; i < m; i++) {
            *(cities + i) = malloc(2 * (sizeof(int)));

            char** cities_item_temp = split_string(rtrim(readline()));

            for (int j = 0; j < 2; j++) {
                int cities_item = parse_int(*(cities_item_temp + j));

                *(*(cities + i) + j) = cities_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, m, 2, cities);

        fprintf(fptr, "%ld\n", result);
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
