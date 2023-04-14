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


void allocateChilds(int** nodeChilds, int* nodeChildsCnt, int t_nodes, int t_edges, int* t_from, int* t_to, int prnt)
{
    for(int i = 0; i < t_edges; i++)
    {
        int n1 = t_from[i] - 1;
        int n2 = t_to[i] - 1;
        
        if(n1 != prnt && n2 != prnt)
            continue;
        
        int child = n1;
        if(prnt == n1)
            child = n2;
        
        char addChild = 1;
        for(int j = 0; j < nodeChildsCnt[child]; j++)
        {
            if(nodeChilds[child][j] == prnt)
            {
                addChild = 0;
                break;
            }
        }
        
        if(addChild == 0)
            continue;
        
        nodeChildsCnt[prnt]++;
        if(nodeChilds[prnt] == NULL)
            nodeChilds[prnt] = malloc(sizeof(int));
        else 
            nodeChilds[prnt] = realloc(nodeChilds[prnt], nodeChildsCnt[prnt] * sizeof(int));
        nodeChilds[prnt][nodeChildsCnt[prnt] - 1] = child;
        
        allocateChilds(nodeChilds, nodeChildsCnt, t_nodes, t_edges, t_from, t_to, child);
    }
}


void updateChildsCnt(int** nodeChilds, int* nodeChildsCnt, int node)
{
    int cnt = 0;
    
    for(int i = 0; i < nodeChildsCnt[node]; i++)
    {
        int child = nodeChilds[node][i];
        
        updateChildsCnt(nodeChilds, nodeChildsCnt, child);
        
        cnt += nodeChildsCnt[child];
    }
    
    nodeChildsCnt[node] += cnt;
}


// Complete the evenForest function below.
int evenForest(int t_nodes, int t_edges, int t_from_count, int* t_from, int t_to_count, int* t_to) 
{
    /* allocate tree */
    int** nodeChilds    = malloc(t_nodes * sizeof(int*));
    int*  nodeChildsCnt = malloc(t_nodes * sizeof(int));
    
    for(int i = 0; i < t_nodes; i++)
    {
        nodeChildsCnt[i] = 0;
        nodeChilds[i]    = NULL;
    }
    
    allocateChilds(nodeChilds, nodeChildsCnt, t_nodes, t_edges, t_from, t_to, 0);
    
    /*
     * update nodes child count to be all nodes below a node
     */
    updateChildsCnt(nodeChilds, nodeChildsCnt, 0);
    
    /*
     * number of edges can be removed to obtain even tree = 
     * number of subtrees of even nodes = 
     * number of nodes having odd childs below it because 
     * the tree rooted at this node will have even nodes
     */
    int cnt = 0;
    for(int i = 1; i < t_nodes; i++)
    {
        if(nodeChildsCnt[i] % 2 == 1)
            cnt++;
    }
    
    return cnt;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** t_nodes_edges = split_string(rtrim(readline()));

    char* t_nodes_endptr;
    char* t_nodes_str = t_nodes_edges[0];
    int t_nodes = strtol(t_nodes_str, &t_nodes_endptr, 10);

    if (t_nodes_endptr == t_nodes_str || *t_nodes_endptr != '\0') { exit(EXIT_FAILURE); }

    char* t_edges_endptr;
    char* t_edges_str = t_nodes_edges[1];
    int t_edges = strtol(t_edges_str, &t_edges_endptr, 10);

    if (t_edges_endptr == t_edges_str || *t_edges_endptr != '\0') { exit(EXIT_FAILURE); }

    int t_from[t_edges];
    int t_to[t_edges];

    for (int t_i = 0; t_i < t_edges; t_i++) {
        char** t_from_to = split_string(rtrim(readline()));

        char* t_from_temp_endptr;
        char* t_from_temp_str = t_from_to[0];
        int t_from_temp = strtol(t_from_temp_str, &t_from_temp_endptr, 10);

        if (t_from_temp_endptr == t_from_temp_str || *t_from_temp_endptr != '\0') { exit(EXIT_FAILURE); }

        char* t_to_temp_endptr;
        char* t_to_temp_str = t_from_to[1];
        int t_to_temp = strtol(t_to_temp_str, &t_to_temp_endptr, 10);

        if (t_to_temp_endptr == t_to_temp_str || *t_to_temp_endptr != '\0') { exit(EXIT_FAILURE); }

        t_from[t_i] = t_from_temp;
        t_to[t_i] = t_to_temp;
    }

    int res = evenForest(t_nodes, t_edges, t_edges, t_from, t_edges, t_to);

    fprintf(fptr, "%d\n", res);

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
