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

int parse_int(char*);

typedef struct Node_t
{
    char data;
    struct Node_t* (childs[10]);
}Node_t;

/*
 * Complete the 'noPrefix' function below.
 *
 * The function accepts STRING_ARRAY words as parameter.
 */

void noPrefix(int words_count, char** words)
{
    Node_t* root = malloc(sizeof(Node_t));
    root->data = 0;
    for(int i=0; i<10; i++)
        root->childs[i] = NULL;
    
    for(int i=0; i<words_count; i++)
    {
        Node_t* node = root;
        char isLastNodeAlreadyFound = 0;
        int j;
        for(j=0; words[i][j]; j++)
        {
            if(node->childs[words[i][j] - 'a'] == NULL)
            {
                
                Node_t* n = malloc(sizeof(Node_t));
                n->data = 0;
                for(int i=0; i<10; i++)
                    n->childs[i] = NULL;
                node->childs[words[i][j] - 'a'] = n;
                
                isLastNodeAlreadyFound = 0;
            }
            else 
            {
                isLastNodeAlreadyFound = 1;
            }
            node = node->childs[words[i][j] - 'a'];
            if(node->data)
            {
                printf("BAD SET\n");
                printf("%s\n", words[i]);
                return;
            }
        }
        if(isLastNodeAlreadyFound)
        {
            printf("BAD SET\n");
            printf("%s\n", words[i]);
            return;
        }
        else 
        {
            node->data = 1;
        }
    }
    printf("GOOD SET\n");
}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    char** words = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* words_item = readline();

        *(words + i) = words_item;
    }

    noPrefix(n, words);

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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
