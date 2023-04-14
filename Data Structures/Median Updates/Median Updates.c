#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


typedef enum {
    RED, BLACK
}Color;


typedef struct Node
{
    int data;
    Color color;
    int subtreeSize;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef  Node*  OrderStatisticsTree;

#define  NIL        ((Node*) (&nullNode))




/*
 * @brief: Create new empty Red Black BST
 */
OrderStatisticsTree newOrderStatisticsTree(void);


/*
 * @brief: Insert new data into tree 
 */
void OrderStatisticsTreeInsert(OrderStatisticsTree* root, int data);


/*
 * @brief: Return pointer to required to node if it's found, or NIL
 */
Node* OrderStatisticsTreeSearch(OrderStatisticsTree root, int data);


/*
 * @brief: Return pointer to node with min data if it's found, or NIL
 */
Node* OrderStatisticsTreeMin(OrderStatisticsTree root);


/*
 * @brief: Delete a node from the tree
 */
void OrderStatisticsTreeDeleteNode(OrderStatisticsTree* root, Node* node);


/*
 * @brief: Delete a value from the tree
 */
int OrderStatisticsTreeDeleteVal(OrderStatisticsTree* root, int data);


/*
 * @brief: Print the tree data in order
 */
void OrderStatisticsTreeInOrderTraverse(OrderStatisticsTree root);

void printMedian(OrderStatisticsTree root);


Node  nullNode = {
    .color = BLACK,
    .subtreeSize = 0
};


/********** private functions ************/
static Node* newNode(int data);
static void  freeNode(Node* node);
static void  replaceSubtree(OrderStatisticsTree* root, Node* replacedRoot, Node* replaceWithRoot);
static void  leftRotate(OrderStatisticsTree* root, Node* node);
static void  rightRotate(OrderStatisticsTree* root, Node* node);
static void  insertFixup(OrderStatisticsTree* root, Node* node);
static void  deleteFixup(OrderStatisticsTree* root, Node* node);


/*
 * @brief: Create new empty OrderStatisticsTree
 */
OrderStatisticsTree newOrderStatisticsTree(void)
{
    return NIL;
}


/*
 * @brief: Allocate new node with passed data
 */
static Node* newNode(int data)
{
    Node* node = malloc(sizeof(Node));
    
    node->data = data;
    node->color = RED;
    node->subtreeSize = 1;
    
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
    node->subtreeSize = 0;
    free(node);
}


/*
 * @brief: Rotate subtree rooted at <node> to the left
 */
static void leftRotate(OrderStatisticsTree* root, Node* node)
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
    
    child->subtreeSize = node->subtreeSize;
    node->subtreeSize = node->left->subtreeSize + node->right->subtreeSize + 1;
}


/*
 * @brief: Rotate subtree rooted at <node> to the right
 */
static void rightRotate(OrderStatisticsTree* root, Node* node)
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
    
    child->subtreeSize = node->subtreeSize;
    node->subtreeSize = node->left->subtreeSize + node->right->subtreeSize + 1;
}


/*
 * @brief: Insert new data into tree 
 */
void OrderStatisticsTreeInsert(OrderStatisticsTree* root, int data)
{
    /* If tree is empty, root will be the new node */
    if(*root == NIL)
    {
        *root = newNode(data);
        (*root)->color = BLACK;
        return;
    }
    
    Node* parnt = NIL;
    Node* next  = *root;
    
    while (next != NIL)
    {
        parnt = next;
        parnt->subtreeSize++;
        
        if(data < parnt->data)
            next = parnt->left;
        else
            next = parnt->right;
    }
    
    
    if(data < parnt->data)
    {
        parnt->left = newNode(data);
        parnt->left->parent = parnt;
        insertFixup(root, parnt->left);
    }
    else 
    {
        parnt->right = newNode(data);
        parnt->right->parent = parnt;
        insertFixup(root, parnt->right);
    }
}


/*
 * @brief: Fix violation of inserting the node <node>
 */
static void insertFixup(OrderStatisticsTree* root, Node* node)
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
 * @brief: Return pointer to required to node if it's found, or NIL
 */
Node* OrderStatisticsTreeSearch(OrderStatisticsTree root, int data)
{
    Node* n = root;
    
    while (n != NIL)
    {
        if(data == n->data)
            break;
        else if(data < n->data)
            n = n->left;
        else
            n = n->right;
    }
    
    return n;
}


/*
 * @brief: Return pointer to node with min data if it's found, or NIL
 */
Node* OrderStatisticsTreeMin(OrderStatisticsTree root)
{
    if(root == NIL)
        return NIL;
    
    Node* n = root;
    while (n->left != NIL)
        n = n->left;
    
    return n;
}


/*
 * @brief: Replace subtree rooted at replacedRoot with subtree rooted at replaceWithRoot
 */
static void replaceSubtree(OrderStatisticsTree* root, Node* replacedRoot, Node* replaceWithRoot)
{
    if(*root == replacedRoot)
        *root = replaceWithRoot;
    else if(replacedRoot->parent->left == replacedRoot)
        replacedRoot->parent->left = replaceWithRoot;
    else
        replacedRoot->parent->right = replaceWithRoot;
    
    replaceWithRoot->parent = replacedRoot->parent;
}


/*
 * @brief: Delete a node from the tree
 */
void OrderStatisticsTreeDeleteNode(OrderStatisticsTree* root, Node* node)
{
    Node* changedNode = node;
    Color changedNodeColor = changedNode->color;
    Node* violationNode;
    
    if(node->left == NIL)
    {
        violationNode = node->right;
        replaceSubtree(root, node, node->right);
    }
    else if(node->right == NIL)
    {
        violationNode = node->left;
        replaceSubtree(root, node, node->left);
    }
    else 
    {
        changedNode = OrderStatisticsTreeMin(node->right);
        changedNodeColor = changedNode->color;
        violationNode = changedNode->right;
        
        if(changedNode == node->right)
        {
            violationNode->parent = changedNode;        // to make sure if violationNode was NIL
        }
        else
        {
            replaceSubtree(root, changedNode, changedNode->right);
            changedNode->right = node->right;
            changedNode->right->parent = changedNode;
        }
        
        replaceSubtree(root, node, changedNode);
        changedNode->left = node->left;
        changedNode->left->parent = changedNode;
        changedNode->color = node->color;
    }
    
    freeNode(node);
    
    Node* n = violationNode->parent;
    while (n != NIL)
    {
        n->subtreeSize = n->left->subtreeSize + n->right->subtreeSize + 1;
        n= n->parent;
    }
    
    if(changedNodeColor == BLACK)
        deleteFixup(root, violationNode);
}


/*
 * @brief: Fix violation of deleting some node which occured at node <node>
 */
static void  deleteFixup(OrderStatisticsTree* root, Node* node)
{
    while (node->color == BLACK && node != (*root))
    {
        Node* prnt = node->parent;
        
        if(node == prnt->left)
        {
            Node* bro = prnt->right;
            
            if(bro->color == RED)
            {
                bro->color = BLACK;
                prnt->color = RED;
                leftRotate(root, prnt);
                prnt = node->parent;
                bro = prnt->right;
            }
            
            if(bro->left->color == BLACK && bro->right->color == BLACK)
            {
                bro->color = RED;
                node = prnt;
            }
            else 
            {
                if(bro->right->color == BLACK)
                {
                    bro->color = RED;
                    bro->left->color = BLACK;
                    rightRotate(root, bro);
                    bro = prnt->right;
                }
                
                bro->color = prnt->color;
                prnt->color = BLACK;
                bro->right->color = BLACK;
                leftRotate(root, prnt);
                node = *root;
            }
        }
        else
        {
            Node* bro = prnt->left;
            
            if(bro->color == RED)
            {
                bro->color = BLACK;
                prnt->color = RED;
                rightRotate(root, prnt);
                prnt = node->parent;
                bro = prnt->left;
            }
            
            if(bro->left->color == BLACK && bro->right->color == BLACK)
            {
                bro->color = RED;
                node = prnt;
            }
            else 
            {
                if(bro->left->color == BLACK)
                {
                    bro->color = RED;
                    bro->right->color = BLACK;
                    leftRotate(root, bro);
                    bro = prnt->left;
                }
                
                bro->color = prnt->color;
                prnt->color = BLACK;
                bro->left->color = BLACK;
                rightRotate(root, prnt);
                node = *root;
            }
        }
    }
    
    node->color = BLACK;
}


/*
 * @brief: Delete a value from the tree
 */
int OrderStatisticsTreeDeleteVal(OrderStatisticsTree* root, int data)
{
    Node* node = OrderStatisticsTreeSearch(*root, data);
    
    if(node != NIL)
    {
        OrderStatisticsTreeDeleteNode(root, node);
        return 1;
    }
    
    printf("Wrong!\n");
    return 0; 
}


/*
 * @brief: get value with rank <rank>
 */
int getRank(OrderStatisticsTree root, int rank)
{
    int r = root->left->subtreeSize + 1;
    if(r == rank)
        return root->data;
    else if(r > rank)
        return getRank(root->left, rank);
    return getRank(root->right, rank - r);
}



void printMedian(OrderStatisticsTree root) 
{
    if(root == NIL)
    {
        printf("Wrong!\n");
        return;
    }
    
    int nodesCnt = root->subtreeSize;
    long median1, median2;
    double median;
    
    switch (nodesCnt % 2) 
    {
        case 0:
           median1 = getRank(root, nodesCnt>>1);
           median2 = getRank(root, (nodesCnt>>1) + 1);
    
           median = median1 / 2.0 + median2 / 2.0;
        break;
    
        case 1:
           median = getRank(root, (nodesCnt>>1) + 1);
        break;
    }
    
    if(median == (long) median)
        printf("%ld\n", (long) median);
    else 
        printf("%.1f\n", median);
}


/*
 * @brief: Print the tree data in order
 */
void OrderStatisticsTreeInOrderTraverse(OrderStatisticsTree root)
{
    if(root == NIL)
        return;
    
    OrderStatisticsTreeInOrderTraverse(root->left);
    printf("%d ", root->data);
    OrderStatisticsTreeInOrderTraverse(root->right);
}


















OrderStatisticsTree tree;

void proccessQuery(char op, int data)
{
    int status = 1;
    
    switch (op) 
    {
        case 'r':
            status = OrderStatisticsTreeDeleteVal(&tree, data);
        break;
    
        case 'a':
            OrderStatisticsTreeInsert(&tree, data);
        break;
    }
    
    if(status)
        printMedian(tree);
}


int main()
{
    tree = newOrderStatisticsTree();
    
	int i, N;
	scanf("%d", &N);
	char op;
	int data;
    
	for(i = 0; i < N; i++)
    {
		scanf(" %c %d", &op, &data);
        proccessQuery(op, data);
	}
}
