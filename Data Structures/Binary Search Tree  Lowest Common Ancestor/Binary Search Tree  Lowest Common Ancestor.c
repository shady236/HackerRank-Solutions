

/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

*/

char search(struct node* root, int v1, int v2)
{
    if(root == NULL)        return 0;
    
    char res = 0;
    if(root->data == v1)             res = 1;
    else if(root->data == v2)        res = 2;
    
    res |= search(root->left , v1, v2);
    res |= search(root->right, v1, v2);
    
    return res;
}

struct node *lca( struct node *root, int v1, int v2 )
{
    struct node* res = root;
    
    char l, r;
    do
    {
        l = search(res->left , v1, v2);
        r = search(res->right, v1, v2);
        
        if(l == 3)           res = res->left;
        else if(r == 3)      res = res->right;
    }while(l == 3 || r == 3);
    
    return res;
}

