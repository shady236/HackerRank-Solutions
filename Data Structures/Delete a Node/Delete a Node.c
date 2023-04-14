

/*
 * Complete the 'deleteNode' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER position
 */

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */

SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* llist, int position) 
{
    
    if(position==0)
    {
        SinglyLinkedListNode* newHead = llist->next;
        llist->next = NULL;
        free(llist);
        return newHead;
    }
    
    SinglyLinkedListNode* prevNode = llist;
    
    for(int i=0; i<position-1; i++)
    {
        prevNode = prevNode->next;
    }
    
    
    SinglyLinkedListNode* requiredNode = prevNode->next;
    
    prevNode->next     = requiredNode->next;
    requiredNode->next = NULL;
    free(requiredNode);
    
    return llist;
}

