

/*
 * Complete the 'removeDuplicates' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts INTEGER_SINGLY_LINKED_LIST llist as parameter.
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

SinglyLinkedListNode* removeDuplicates(SinglyLinkedListNode* llist)
{
    SinglyLinkedListNode* node = llist;
    while (node->next)
    {
        if(node->data == node->next->data)
        {
            SinglyLinkedListNode* toBeDeletedNode = node->next;
            node->next = toBeDeletedNode->next;
            toBeDeletedNode->next = NULL;
            free(toBeDeletedNode);
        }
        else
        {
            node = node->next;
        }
    }
    
    return llist;
}

