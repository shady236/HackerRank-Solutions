/* Node is defined as :
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; */


node* newNode(int val)
{
    node* n = (node*) malloc(sizeof(node));
    
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    n->ht = 0;
    
    return n;
}


int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}


void updateHeight(node* root)
{
    if (root == NULL)
        return;
    
    if(root->left == NULL && root->right == NULL)   // no childs
        root->ht = 0;
    else if(root->left == NULL)     // right child only
        root->ht = 1 + root->right->ht;
    else if(root->right == NULL)    // left child only
        root->ht = 1 + root->left->ht;
    else        // both childs
        root->ht = 1 + max(root->left->ht, root->right->ht);
}


node* leftRotation(node* root)
{
    node* newRoot = root->right;
    
    root->right = newRoot->left;
    newRoot->left = root;
    
    updateHeight(root);
    updateHeight(newRoot);
    
    return newRoot;
}


node* rightRotation(node* root)
{
    node* newRoot = root->left;
    
    root->left = newRoot->right;
    newRoot->right = root;
    
    updateHeight(root);
    updateHeight(newRoot);
    
    return newRoot;
}


int balanceFactor(node* root)
{
    if(root == NULL)
        return 0;
   
    if(root->ht == 0)  // no childs
        return 0;
    
    if(root->left == NULL)    // right child only
        return -1 * root->ht;
    
    if(root->right == NULL)    // left child only
        return root->ht;
    
    // both childs
    return root->left->ht - root->right->ht;
}


node* insert(node* root ,int val)
{
    /* insert as ordinary BST recursivly */
    if(root == NULL)
        return newNode(val);
    
    if (val < root->val)
        root->left  = insert(root->left, val);
    else 
        root->right = insert(root->right, val);
    
    updateHeight(root);
    
     
    int balance = balanceFactor(root);
    
    // Left Left Case
    if (balance > 1 && val < root->left->val)
        return rightRotation(root);
    
    // Right Right Case
    if (balance < -1 && val > root->right->val)
        return leftRotation(root);
 
    // Left Right Case
    if (balance > 1 && val > root->left->val)
    {
        root->left =  leftRotation(root->left);
        return rightRotation(root);
    }
 
    // Right Left Case
    if (balance < -1 && val < root->right->val)
    {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    // already balanced case
    return root;
}