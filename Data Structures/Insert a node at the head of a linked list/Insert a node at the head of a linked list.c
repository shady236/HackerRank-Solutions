

// Complete the insertNodeAtHead function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtHead(SinglyLinkedListNode* llist, int data) 
{
    SinglyLinkedListNode* newNode = malloc(sizeof(SinglyLinkedList));
    newNode->data = data;
    newNode->next = llist;
    return newNode;
}

