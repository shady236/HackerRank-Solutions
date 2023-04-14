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
    int  data;
    int  sum;
    int  childsCnt;
    int* childsNum;
}Node_t;

#define  MAX_NODES_CNT     (100000)


int min(int a, int b)
{
    if(a > b)
        return b;
    return a;
}


void addChilds(Node_t* tree, int parnt, int parntOfParnt, int nodesCnt, int** nodeEdges, int* nodeEdgesCnt)
{
    if(parnt == 0)
    {
        tree[parnt].childsNum = malloc(nodeEdgesCnt[parnt] * sizeof(int));
    }
    else if(nodeEdgesCnt[parnt] > 1)
    {
        tree[parnt].childsNum = malloc((nodeEdgesCnt[parnt] - 1) * sizeof(int));
    }
    
    
    for(int i = 0; i < nodeEdgesCnt[parnt]; i++)
    {
        int to = nodeEdges[parnt][i];
        
        if(to == parntOfParnt)
            continue;
        
        tree[parnt].childsNum[tree[parnt].childsCnt] = to;
        tree[parnt].childsCnt++;
        
        addChilds(tree, to, parnt, nodesCnt, nodeEdges, nodeEdgesCnt);
    }
}


void initSum(Node_t* tree, int node)
{
    for(int i = 0; i < tree[node].childsCnt; i++)
        initSum(tree, tree[node].childsNum[i]);
    
    int sum = tree[node].data;
    for(int i = 0; i < tree[node].childsCnt; i++)
        sum += tree[tree[node].childsNum[i]].sum;
    
    tree[node].sum = sum;
}



Node_t* constructTree(int data_count, int* data, int edges_rows, int** edges)
{
    int** nodeEdges = malloc(data_count * sizeof(int*));
    int*  nodeEdgesCnt = malloc(data_count * sizeof(int));
    
    for(int i = 0; i < data_count; i++)
    {
        nodeEdges[i] = NULL;
        nodeEdgesCnt[i] = 0;
    }
    
    for(int i = 0; i < edges_rows; i++)
    {
        int n1 = edges[i][0] - 1;
        int n2 = edges[i][1] - 1;
        
        nodeEdgesCnt[n1]++;
        if(nodeEdges[n1] == NULL)
            nodeEdges[n1] = malloc(nodeEdgesCnt[n1] * sizeof(int));
        else 
            nodeEdges[n1] = realloc(nodeEdges[n1], nodeEdgesCnt[n1] * sizeof(int));
        nodeEdges[n1][nodeEdgesCnt[n1] - 1] = n2;
        
        nodeEdgesCnt[n2]++;
        if(nodeEdges[n2] == NULL)
            nodeEdges[n2] = malloc(nodeEdgesCnt[n2] * sizeof(int));
        else 
            nodeEdges[n2] = realloc(nodeEdges[n2], nodeEdgesCnt[n2] * sizeof(int));
        nodeEdges[n2][nodeEdgesCnt[n2] - 1] = n1;
    }
    
    
    Node_t* nodes = malloc(data_count * sizeof(Node_t));
    for(int i = 0; i < data_count; i++)
    {
        nodes[i].childsCnt = 0;
        nodes[i].childsNum = NULL;
        nodes[i].data = data[i];
        nodes[i].sum = 0;
    }
    
    addChilds(nodes, 0, -1, data_count, nodeEdges, nodeEdgesCnt);
    initSum(nodes, 0);
    
    
    for(int i = 0; i < data_count; i++)
        free(nodeEdges[i]);
    free(nodeEdges);
    free(nodeEdgesCnt);
    
    return nodes;
}




int minDiff(Node_t* tree, int parnt, int totalSum)
{
    int res = totalSum;
    
    for(int i = 0; i < tree[parnt].childsCnt; i++)
    {
        res = min(
            res, 
            abs(
                totalSum - 
                (tree[tree[parnt].childsNum[i]].sum<<1)
            )
        );
        
        res = min(
            res,
            minDiff(tree, tree[parnt].childsNum[i], totalSum)
        );
    }
    
    
    return res;
}


/*
 * Complete the 'cutTheTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. 2D_INTEGER_ARRAY edges
 */

int cutTheTree(int data_count, int* data, int edges_rows, int edges_columns, int** edges) 
{
    Node_t* tree = constructTree(data_count, data, edges_rows, edges);
    
    return minDiff(tree, 0, tree[0].sum);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** data_temp = split_string(rtrim(readline()));

    int* data = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int data_item = parse_int(*(data_temp + i));

        *(data + i) = data_item;
    }

    int** edges = malloc((n - 1) * sizeof(int*));

    for (int i = 0; i < n - 1; i++) {
        *(edges + i) = malloc(2 * (sizeof(int)));

        char** edges_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int edges_item = parse_int(*(edges_item_temp + j));

            *(*(edges + i) + j) = edges_item;
        }
    }

    int result = cutTheTree(n, data, n - 1, 2, edges);

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
