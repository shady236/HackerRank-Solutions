

// Complete the printLinkedList function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
void printLinkedList(SinglyLinkedListNode* head) 
{
    SinglyLinkedListNode* node = head;
    
    while(node)
    {
        printf("%d\n", node->data);
        node = node->next;
    }

}

