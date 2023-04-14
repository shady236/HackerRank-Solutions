

/*
 * Complete the 'getNode' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER positionFromTail
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

int getNode(SinglyLinkedListNode* llist, int positionFromTail)
{
    int listLen = 0;
    SinglyLinkedListNode* node = llist;
    while (node)
    {
        listLen++;
        node = node->next;
    }
    int positionFromHead = listLen - positionFromTail - 1;
    node = llist;
    for(int i=0; i<positionFromHead; i++)
    {
        node = node->next;
    }
    return node->data;
}

