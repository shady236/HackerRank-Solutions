

/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

*/

int max(int z, int y)
{
    if(z > y)   return z;
    return y;
}

int getHeight(struct node* root)
{
    if(root->right == NULL && root->left == NULL)
        return 0;
    if(root->right == NULL)
        return 1 + getHeight(root->left);
    if(root->left == NULL)
        return 1 + getHeight(root->right);
    
    return 1 + max(getHeight(root->right), getHeight(root->left));
}

