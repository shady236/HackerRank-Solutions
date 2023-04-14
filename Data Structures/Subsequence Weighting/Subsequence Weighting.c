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



long max(long a, long b)
{
    if(a > b)
        return a;
    return b;
}


long maxOfThree(long a, long b, long c)
{
    return max(a, max(b, c));
}



typedef enum {
    RED, BLACK
}Color;


typedef struct Node
{
    long key;
    Color color;
    long maxWeight;
    long subtreeMaxWeight;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef  Node*  RedBlackBST;
#define  NIL        ((Node*) (&nullNode))




/*
 * @brief: Create new empty Red Black BST
 */
RedBlackBST newRedBlackBST(void);


/*
 * @brief: Insert new key into tree 
 */
void RedBlackBSTInsert(RedBlackBST* root, long key, long weight);



Node  nullNode = {
    .color = BLACK,
    .subtreeMaxWeight = 0,
    .maxWeight = 0
};


/********** private functions ************/
static Node* newNode(long key, long weight);
static void  freeNode(Node* node);
static void  leftRotate(RedBlackBST* root, Node* node);
static void  rightRotate(RedBlackBST* root, Node* node);
static void  insertFixup(RedBlackBST* root, Node* node);


/*
 * @brief: Create new empty RedBlackBST
 */
RedBlackBST newRedBlackBST(void)
{
    return NIL;
}


/*
 * @brief: Allocate new node with passed key
 */
static Node* newNode(long key, long weight)
{
    Node* node = malloc(sizeof(Node));
    
    node->key = key;
    node->color = RED;
    node->subtreeMaxWeight = weight;
    node->maxWeight = weight;
    
    node->left = NIL;
    node->right = NIL;
    node->parent = NIL;
    
    return node;
}


/*
 * @brief: Free the space allocated for the node from memory
 */
static void freeNode(Node* node)
{
    node->left = NIL;
    node->right = NIL;
    node->parent = NIL;
    node->subtreeMaxWeight = 0;
    node->maxWeight = 0;
    free(node);
}


/*
 * @brief: Rotate subtree rooted at <node> to the left
 */
static void leftRotate(RedBlackBST* root, Node* node)
{
    Node* child = node->right;
    
    node->right = child->left;
    node->right->parent = node;
    
    child->parent = node->parent;
    if(node == (*root))
        *root = child;
    else if(node == node->parent->left)
        node->parent->left = child;
    else 
        node->parent->right = child;
    
    child->left = node;
    node->parent = child;
    
    child->subtreeMaxWeight = node->subtreeMaxWeight;
    node->subtreeMaxWeight = maxOfThree(
        node->left->subtreeMaxWeight, 
        node->right->subtreeMaxWeight, 
        node->maxWeight
    );
}


/*
 * @brief: Rotate subtree rooted at <node> to the right
 */
static void rightRotate(RedBlackBST* root, Node* node)
{
    Node* child = node->left;
    
    node->left = child->right;
    node->left->parent = node;
    
    child->parent = node->parent;
    if(node == (*root))
        *root = child;
    else if(node == node->parent->left)
        node->parent->left = child;
    else 
        node->parent->right = child;
    
    child->right = node;
    node->parent = child;
    
    child->subtreeMaxWeight = node->subtreeMaxWeight;
    node->subtreeMaxWeight = maxOfThree(
        node->left->subtreeMaxWeight, 
        node->right->subtreeMaxWeight, 
        node->maxWeight
    );
}


/*
 * @brief: Insert new key into tree 
 */
void RedBlackBSTInsert(RedBlackBST* root, long key, long weight)
{
    /* If tree is empty, root will be the new node */
    if(*root == NIL)
    {
        *root = newNode(key, weight);
        (*root)->color = BLACK;
        return;
    }
    
    Node* parnt = NIL;
    Node* next  = *root;
    
    while (next != NIL)
    {
        parnt = next;
        parnt->subtreeMaxWeight++;
        
        if(key < parnt->key)
            next = parnt->left;
        else
            next = parnt->right;
    }
    
    
    Node* new = newNode(key, weight);
    
    if(key < parnt->key)
    {
        parnt->left = new;
        new->parent  = parnt;
    }
    else 
    {
        parnt->right = new;
        new->parent = parnt;
    }
    
    
    /* modify weight */
    long prevMaxWeight = 0;
    Node* n = *root;
    
    while (n != NIL) 
    {
        if(n->key < new->key)
        {
            prevMaxWeight = maxOfThree(
                prevMaxWeight, 
                n->left->subtreeMaxWeight,
                n->maxWeight
            );
            n = n->right;
        }
        else 
        {
            n = n->left;
        }
    }
    
    new->maxWeight = prevMaxWeight + weight;
    
    
    /* go from inserted node up to root to update subtreeMaxWeight for each node */
    n = new;
    
    while (n != NIL) 
    {
        n->subtreeMaxWeight = maxOfThree(
            n->left->subtreeMaxWeight, 
            n->right->subtreeMaxWeight, 
            n->maxWeight
        );
        
        n = n->parent;
    }
    
    /* fix violations of red black tree propirties */
    insertFixup(root, new);
}


/*
 * @brief: Fix violation of inserting the node <node>
 */
static void insertFixup(RedBlackBST* root, Node* node)
{
    while (node->parent->color == RED)
    {
        Node* prnt = node->parent;
        Node* grndPrnt = prnt->parent;
        
        if(prnt == grndPrnt->left)
        {
            Node* uncle = grndPrnt->right;
            
            if(uncle->color == RED)
            {
                uncle->color = BLACK;
                prnt->color = BLACK;
                grndPrnt->color = RED;
                
                node = grndPrnt;
            }
            else 
            {
                if(node == prnt->right)
                {
                    leftRotate(root, prnt);
                    
                    /* After rotation, child node will be parrent of its previous parent */
                    Node* tmp = node;
                    node = prnt;
                    prnt = tmp;
                }
                
                prnt->color = BLACK;
                grndPrnt->color = RED;
                rightRotate(root, grndPrnt);
            }
        }
        else
        {
            Node* uncle = grndPrnt->left;
            
            if(uncle->color == RED)
            {
                uncle->color = BLACK;
                prnt->color = BLACK;
                grndPrnt->color = RED;
                
                node = grndPrnt;
            }
            else 
            {
                if(node == prnt->left)
                {
                    rightRotate(root, prnt);
                    
                    /* After rotation, child node will be parrent of its previous parent */
                    Node* tmp = node;
                    node = prnt;
                    prnt = tmp;
                }
                
                prnt->color = BLACK;
                grndPrnt->color = RED;
                leftRotate(root, grndPrnt);
            }
        }
    }
    
    
    (*root)->color = BLACK;
}











/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY a
 *  2. INTEGER_ARRAY w
 */

long solve(int a_count, int* a, int w_count, int* w) 
{
    RedBlackBST tree = newRedBlackBST();
    
    for(int i = 0; i < a_count; i++)
    {
        RedBlackBSTInsert(&tree, a[i], w[i]);
    }
    
    return tree->subtreeMaxWeight;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** a_temp = split_string(rtrim(readline()));

        int* a = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int a_item = parse_int(*(a_temp + i));

            *(a + i) = a_item;
        }

        char** w_temp = split_string(rtrim(readline()));

        int* w = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int w_item = parse_int(*(w_temp + i));

            *(w + i) = w_item;
        }

        long result = solve(n, a, n, w);

        fprintf(fptr, "%ld\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t key_length = 0;

    char* key = malloc(alloc_length);

    while (true) {
        char* cursor = key + key_length;
        char* line = fgets(cursor, alloc_length - key_length, stdin);

        if (!line) {
            break;
        }

        key_length += strlen(cursor);

        if (key_length < alloc_length - 1 || key[key_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        key = realloc(key, alloc_length);

        if (!key) {
            key = '\0';

            break;
        }
    }

    if (key[key_length - 1] == '\n') {
        key[key_length - 1] = '\0';

        key = realloc(key, key_length);

        if (!key) {
            key = '\0';
        }
    } else {
        key = realloc(key, key_length + 1);

        if (!key) {
            key = '\0';
        } else {
            key[key_length] = '\0';
        }
    }

    return key;
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
