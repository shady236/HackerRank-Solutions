

/*
 * Complete the 'reverse' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts INTEGER_DOUBLY_LINKED_LIST llist as parameter.
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

DoublyLinkedListNode* reverse(DoublyLinkedListNode* llist) {
    DoublyLinkedListNode* node = llist;
    DoublyLinkedListNode* nextNode = llist; 
    DoublyLinkedListNode* prevNode;
    while(nextNode) 
    {
        node = nextNode;
        nextNode = node->next;
        prevNode = node->prev;
        node->next = prevNode;
        node->prev = nextNode;
    } 
    return node;

}

