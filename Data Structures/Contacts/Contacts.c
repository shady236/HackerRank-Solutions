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
    char data;
    int prefixChildsCnt;
    struct ChildNode_t
    {
        struct Node_t* childNode;
        struct ChildNode_t* next;
    }*childsList;
}Node_t;

typedef struct ChildNode_t  ChildNode_t;


void print(Node_t* root)
{
    if(root == NULL)
        return;
    
    printf("%c\n", root->data);
    
    ChildNode_t* child = root->childsList;
    while (child) 
    {
        if(child->childNode->data == 0)
            printf("End\n");
        else 
            print(child->childNode);
        
        child = child->next;
    }
}



void add(Node_t* root, char* str)
{
    root->prefixChildsCnt++;
    
    if(str[0] == 0) // if end of string is reached
    {
        /* 
         * create an empty child indication for end of
         * contact is here.
         */
        ChildNode_t* contactEnd = malloc(sizeof(ChildNode_t));
        contactEnd->childNode = malloc(sizeof(Node_t));
        contactEnd->childNode->data = 0;
        contactEnd->childNode->childsList = NULL;
        contactEnd->childNode->prefixChildsCnt = 1;
        
        // Add child to start of list
        contactEnd->next = root->childsList;
        root->childsList = contactEnd;
        
        return;
    }
    
    
    /*
     * search for a child has data = str[0]
     */
    ChildNode_t* child = root->childsList;
    while (child) 
    {
        if(child->childNode->data == str[0])
            break;
        
        child = child->next;
    }
    
    /*
     * if no child has data = str[0], create one
     */
    if(child == NULL)
    {
        child = malloc(sizeof(ChildNode_t));
        child->childNode = malloc(sizeof(Node_t));
        child->childNode->data = str[0];
        child->childNode->childsList = NULL;
        child->childNode->prefixChildsCnt = 0;
        
        // Add child to start of list
        child->next = root->childsList;
        root->childsList = child;
    }
    
    // go to this child, with the nest char
    add(child->childNode, str + 1);
}


int search(Node_t* root, char* str)
{
    if(root == NULL)
        return 0;
    
    if(str[0] == 0)
        return root->prefixChildsCnt;
    
    /*
     * search for a child has data = str[0]
     */
    ChildNode_t* child = root->childsList;
    while (child) 
    {
        if(child->childNode->data == str[0])
            return search(child->childNode, str + 1);
        
        child = child->next;
    }
    
    return 0;
}

/*
 * Complete the 'contacts' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_STRING_ARRAY queries as parameter.
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
int* contacts(int queries_rows, int queries_columns, char*** queries, int* result_count)
{
    int* res = malloc(queries_rows * sizeof(int));
    *result_count = 0;
    
    Node_t* root = malloc(sizeof(Node_t));
    root->data = 0;
    root->childsList = NULL;
    root->prefixChildsCnt = 0;
    
    for(int i = 0; i < queries_rows; i++)
    {
        switch (queries[i][0][0])
        {
            case 'a':
                add(root, queries[i][1]);
            break;
            
            case 'f':
                res[*result_count] = search(root, queries[i][1]);
                (*result_count)++;
            break;
        }
    }
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int queries_rows = parse_int(ltrim(rtrim(readline())));

    char*** queries = malloc(queries_rows * sizeof(char**));

    for (int i = 0; i < queries_rows; i++) {
        *(queries + i) = malloc(2 * (sizeof(char*)));

        char** queries_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            char* queries_item = *(queries_item_temp + j);

            *(*(queries + i) + j) = queries_item;
        }
    }

    int result_count;
    int* result = contacts(queries_rows, 2, queries, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
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
