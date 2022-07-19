

/*
 * Complete the 'sortedInsert' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_DOUBLY_LINKED_LIST llist
 *  2. INTEGER data
 */

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */

DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data)
{
    DoublyLinkedListNode* newNode = malloc(sizeof(DoublyLinkedListNode));
    newNode->data = data;
    
    if(data < llist->data)
    {
        newNode->prev = NULL;
        llist->prev = newNode;
        newNode->next =llist;
        return newNode;
    }
    
    DoublyLinkedListNode* prevNode = llist;
    while (prevNode->next  &&  prevNode->next->data < data)
    {
        prevNode = prevNode->next;
    }
    newNode->prev = prevNode;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    if(newNode->next)
        newNode->next->prev = newNode;
    return llist;
}

