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
    int* parent;
    int* rank;
    int* size;
} DisjointSet;


void create(DisjointSet* set, int n) {
    set->parent = malloc(n * sizeof(int));
    set->rank   = malloc(n * sizeof(int));
    set->size   = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        set->parent[i] = i;
        set->rank[i]   = 0;
        set->size[i]   = 1;
    }
}


void clear(DisjointSet* set) {
    free(set->parent);
    free(set->rank);
    free(set->size);
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
        set->size[p2] += set->size[p1];
    }
    else {
        set->parent[p2] = p1;
        set->size[p1] += set->size[p2];
        
        if (set->rank[p1] == set->rank[p2]) {
            set->rank[p1]++;
        }
    }
}


int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}


int cmp(const void* n1, const void* n2) {
    int v1 = *((int*) n1);
    int v2 = *((int*) n2);
    return v2 - v1;
}


/*
 * Complete the 'valueOfFriendsship' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY friendships
 */

long valueOfFriendsship(int n, int friendships_rows, int friendships_columns, int** friendships) {
    DisjointSet friends;
    create(&friends, n);
    
    long sum = 0;
    long prevSum = 0;
    for (int i = 0; i < friendships_rows; i++) {
        int u = friendships[i][0] - 1;
        int v = friendships[i][1] - 1;
        merge(&friends, u, v);
    }
    
    int* sizes = malloc(n * sizeof(int));
    int  sizesCnt = 0;
    for (int i = 0; i < n; i++) {
        if (friends.parent[i] == i && friends.size[i] > 1) {
            sizes[sizesCnt++] = friends.size[i];
        }
    }
    
    qsort(sizes, sizesCnt, sizeof(int), cmp);
    
    for (int i = 0; i < sizesCnt; i++) {
        long comb = (sizes[i] * (sizes[i] - 1l) * (sizes[i] + 1l)) / 3;
        sum += comb;
        sum  += sizes[i] * (sizes[i] - 1l) * (friendships_rows - sizes[i] + 1);
        friendships_rows -= (sizes[i] - 1);
    }
    
    clear(&friends);
    free(sizes);
    return sum;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        int** friendships = malloc(m * sizeof(int*));

        for (int i = 0; i < m; i++) {
            *(friendships + i) = malloc(2 * (sizeof(int)));

            char** friendships_item_temp = split_string(rtrim(readline()));

            for (int j = 0; j < 2; j++) {
                int friendships_item = parse_int(*(friendships_item_temp + j));

                *(*(friendships + i) + j) = friendships_item;
            }
        }

        long result = valueOfFriendsship(n, m, 2, friendships);

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
