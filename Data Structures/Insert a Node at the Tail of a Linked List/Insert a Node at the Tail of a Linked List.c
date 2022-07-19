

// Complete the insertNodeAtTail function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtTail(SinglyLinkedListNode* head, int data) 
{
    SinglyLinkedListNode* newNode = malloc(sizeof(SinglyLinkedList));
    newNode->data = data;
    newNode->next = NULL;
    
    if(head == NULL)        return newNode;
    
    SinglyLinkedListNode* lastNode = head;
    while(lastNode->next)
    {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
    return head;
}

