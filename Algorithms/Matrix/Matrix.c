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


typedef struct DisjointSet {
    int*  parent;
    int*  rank;
    char* isThereMachine;
} DisjointSet;


void create(DisjointSet* set, int n, int* machines, int machinesCnt) {
    set->parent         = malloc(n * sizeof(int));
    set->rank           = malloc(n * sizeof(int));
    set->isThereMachine = malloc(n * sizeof(char));
    
    for (int i = 0; i < n; i++) {
        set->parent[i]         = i;
        set->rank[i]           = 0;
        set->isThereMachine[i] = 0;
    }
    
    for (int i = 0; i < machinesCnt; i++) {
        set->isThereMachine[machines[i]] = 1;
    }
}


void clear(DisjointSet* set) {
    free(set->parent);
    free(set->rank);
    free(set->isThereMachine);
}


int find(DisjointSet* set, int i) {
    if (set->parent[i] != i) {
        set->parent[i] = find(set, set->parent[i]);
    }
    return set->parent[i];
}


void merge(DisjointSet* set, int i, int j) {
    int p1 = find(set, i);
    int p2 = find(set, j);
    
    if (p1 == p2) {
        return;
    }
    
    if (set->rank[p1] < set->rank[p2]) {
        set->parent[p1] = p2;
        set->isThereMachine[p2] |= set->isThereMachine[p1];
    }
    else {
        set->parent[p2] = p1;
        set->isThereMachine[p1] |= set->isThereMachine[p2];
        
        if (set->rank[p1] == set->rank[p2]) {
            set->rank[p1]++;
        }
    }
}


typedef struct Road {
    int u, v, t;
} Road;


int cmp(const void* r1, const void* r2) {
    Road* road1 = (Road*) r1;
    Road* road2 = (Road*) r2;
    
    int t1 = road1->t;
    int t2 = road2->t;
    
    return t2 - t1;
}


/*
 * Complete the 'minTime' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY roads
 *  2. INTEGER_ARRAY machines
 */

int minTime(int roads_rows, Road* roads, int machines_count, int* machines) {
    int n = roads_rows + 1;
    
    qsort(roads, roads_rows, sizeof(roads[0]), cmp);
    
    DisjointSet set;
    create(&set, n, machines, machines_count);
    
    int timeSum = 0;
    
    for (int i = 0; i < roads_rows; i++) {
        int u = roads[i].u;
        int v = roads[i].v;
        int t = roads[i].t;
        
        printf("%d %d %d\n", u, v, t);
        
        int uSet = find(&set, u);
        int vSet = find(&set, v);
        
        if (set.isThereMachine[uSet] && set.isThereMachine[vSet]) {
            timeSum += t;
        }
        else {
            merge(&set, uSet, vSet);
        }
    }
    
    return timeSum;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    Road* roads = malloc((n - 1) * sizeof(Road));

    for (int i = 0; i < n - 1; i++) {
        char** roads_item_temp = split_string(rtrim(readline()));

        roads[i].u = parse_int(*(roads_item_temp));
        roads[i].v = parse_int(*(roads_item_temp + 1));
        roads[i].t = parse_int(*(roads_item_temp + 2));
    }

    int* machines = malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        int machines_item = parse_int(ltrim(rtrim(readline())));

        *(machines + i) = machines_item;
    }

    int result = minTime(n - 1, roads, k, machines);

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
