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
    int data;
    struct Node_t* left;
    struct Node_t* right;
}Node_t;

#define  MAX_NODES_CNT      (1024)


Node_t* constructTree(int indexes_rows, int indexes_columns, int** indexes)
{
    Node_t* root = malloc(indexes_rows * sizeof(Node_t));
    
    for(int i = 0; i < indexes_rows; i++)
    {
        root[i].data = i + 1;
        
        if(indexes[i][0] != -1)
            root[i].left = &root[indexes[i][0] - 1];
        else 
            root[i].left = NULL;
        
        if(indexes[i][1] != -1)
            root[i].right = &root[indexes[i][1] - 1];
        else 
            root[i].right = NULL;
    }
    
    return root;
}


int getMaxDepth(Node_t* root)
{
    if(root == NULL)
        return 0;
    
    int d1 = 1 + getMaxDepth(root->left);
    int d2 = 1 + getMaxDepth(root->right);
    
    if(d1 > d2)
        return d1;
    return d2;
}


int* inOrder(Node_t* root, int* resSize)
{
    if(root == NULL)
    {
        *resSize = 0;
        return NULL;
    }
    
    int leftSize;
    int* left = inOrder(root->left, &leftSize);
    
    int rightSize;
    int* right = inOrder(root->right, &rightSize);
    
    
    int* res = malloc(MAX_NODES_CNT * sizeof(int));
    *resSize = 0;
    
    for(int i = 0; i < leftSize; i++)
    {
        res[*resSize] = left[i];
        (*resSize)++;
    }
    
    res[*resSize] = root->data;
    (*resSize)++;
    
    for(int i = 0; i < rightSize; i++)
    {
        res[*resSize] = right[i];
        (*resSize)++;
    }
    
    free(left);
    free(right);
    
    return res;
}


void swap(Node_t* root)
{
    Node_t* tmp = root->left;
    root->left = root->right;
    root->right = tmp;
}


void swapAllDepth(Node_t* root, int depth)
{
    if(root == NULL)
        return;
    
    if(depth == 1)
        swap(root);
    
    swapAllDepth(root->left, depth - 1);
    swapAllDepth(root->right, depth - 1);
}


/*
 * Complete the 'swapNodes' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY indexes
 *  2. INTEGER_ARRAY queries
 */

/*
 * To return the 2d integer array from the function, you should:
 *     - Store the number of rows of the array to be returned in the result_rows variable
 *     - Store the number of columns of the array to be returned in the result_columns variable
 *     - Allocate the array dynamically
 *
 * For example,
 * int** return_2d_integer_array(int* result_rows, int* result_columns) {
 *     *result_rows = 2;
 *     *result_columns = 3;
 *
 *     int** a = malloc(2 * sizeof(int*));
 *
 *     for (int i = 0; i < 2; i++) {
 *         *(a + i) = malloc(3 * sizeof(int));
 *
 *         for (int j = 0; j < 3; j++) {
 *             *(*(a + i) + j) = 3 * i + j + 1;
 *         }
 *     }
 *
 *     return a;
 * }
 *
 */
int** swapNodes(int indexes_rows, int indexes_columns, int** indexes, int queries_count, int* queries, int* result_rows, int* result_columns) 
{
    Node_t* tree = constructTree(indexes_rows, indexes_columns, indexes);
    
    int maxDepth = getMaxDepth(tree);
    
    int** res = malloc(queries_count * sizeof(int*));
    *result_rows = queries_count;
    *result_columns = indexes_rows;
    
    for(int i = 0; i < queries_count; i++)
    {
        int k = queries[i];
        for(int d = k; d <= maxDepth; d += k)
            swapAllDepth(tree, d);
        
        int resSize;
        res[i] = inOrder(tree, &resSize);
        if(resSize != queries_count)
            printf("%d\n", resSize);
    }
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int** indexes = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(indexes + i) = malloc(2 * (sizeof(int)));

        char** indexes_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int indexes_item = parse_int(*(indexes_item_temp + j));

            *(*(indexes + i) + j) = indexes_item;
        }
    }

    int queries_count = parse_int(ltrim(rtrim(readline())));

    int* queries = malloc(queries_count * sizeof(int));

    for (int i = 0; i < queries_count; i++) {
        int queries_item = parse_int(ltrim(rtrim(readline())));

        *(queries + i) = queries_item;
    }

    int result_rows;
    int result_columns;
    int** result = swapNodes(n, 2, indexes, queries_count, queries, &result_rows, &result_columns);

    for (int i = 0; i < result_rows; i++) {
        for (int j = 0; j < result_columns; j++) {
            fprintf(fptr, "%d", *(*(result + i) + j));

            if (j != result_columns - 1) {
                fprintf(fptr, " ");
            }
        }

        if (i != result_rows - 1) {
            fprintf(fptr, "\n");
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
