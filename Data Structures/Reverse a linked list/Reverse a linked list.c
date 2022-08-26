

/*
 * Complete the 'reverse' function below.
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

SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist)
{
    SinglyLinkedListNode* newHead = llist;
    if(llist->next)
    {
        newHead = reverse(llist->next);
        llist->next->next = llist;
        llist->next = NULL;
    }
    return newHead;
}

