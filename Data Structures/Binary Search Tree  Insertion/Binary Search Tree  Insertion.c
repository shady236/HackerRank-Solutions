

/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

*/
struct node* insert( struct node* root, int data )
{
    if(root == NULL)
    {
        root = malloc(sizeof(struct node));
        root->data  = data;
        root->left  = NULL;
        root->right = NULL;
        return root;
    }
    
    if(root->data < data)
        root->right = insert(root->right, data);
    else 
        root->left = insert(root->left, data);
    
    return root;
}

