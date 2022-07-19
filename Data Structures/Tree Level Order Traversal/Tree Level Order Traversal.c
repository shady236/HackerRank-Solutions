

/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

*/

char printLvl(struct node* root, int lvl)
{
    char isAnyPrinted = 0;
    if(lvl == 0)
    {
        printf("%d ", root->data);
        return 1;
    }
    
    if(root->left)    
        isAnyPrinted |= printLvl(root->left , lvl-1);
    if(root->right)
        isAnyPrinted |= printLvl(root->right, lvl-1);
    
    return isAnyPrinted;
}

void levelOrder( struct node *root)
{
    int lvl = 0;
    while(printLvl(root, lvl))
        lvl++;
}

