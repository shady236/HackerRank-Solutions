/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
	struct Node {
		int data;
		Node* left;
		Node* right;
	}
*/
    
    bool isBST(Node* root, int maxData, int minData)
    {
        if(root == NULL)
            return true;
        
        if(root->data < minData || root->data > maxData)
            return false;
        
        return (
            isBST(root->left, root->data - 1, minData) && 
            isBST(root->right, maxData, root->data + 1) 
        );
    }
    
	bool checkBST(Node* root)
    {
        return isBST(root, 10000, 0);
	}