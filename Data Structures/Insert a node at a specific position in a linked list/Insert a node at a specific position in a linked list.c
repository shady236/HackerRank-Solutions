

/*
 * Complete the 'insertNodeAtPosition' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER data
 *  3. INTEGER position
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

SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position)
{
    SinglyLinkedListNode* newNode = malloc(sizeof(SinglyLinkedList));
    newNode->data = data;
    newNode->next = NULL;
    
    SinglyLinkedListNode* prevNode = llist;
    
    for(int i=0; i<position-1; i++)
    {
        prevNode = prevNode->next;
    }
    
    if(prevNode == NULL)        return newNode;
    
    newNode->next  = prevNode->next;
    prevNode->next = newNode;
    
    return llist;
}

