

/* 
The structure of the node is

typedef struct node {

	int freq;
    char data;
    node * left;
    node * right;
    
} node;

*/


void decode_huff(node * root, string s) {
    char result[260] = {0};;
    char resultSize = 0;
    node* n = root;
    for(int i=0; s[i]; )
    {
        n = root;
        while(n->right && n->left)
        {
            switch(s[i])
            {
                case '0':
                n = n->left;
                i++;
                break;
                
                case '1':
                n = n->right;
                i++;
                break;
            }
        }
        result[resultSize] = n->data;
        resultSize++;
    }
    
    cout<<result;    
}

