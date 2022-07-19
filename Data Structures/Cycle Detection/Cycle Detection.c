

// Complete the has_cycle function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
bool has_cycle(SinglyLinkedListNode* head)
{
    SinglyLinkedListNode* (nodes[1001]);
    for(int i=0; head; i++)
    {
        nodes[i] = head;
        for(int j=0; j<i; j++)
            if(head == nodes[j])    return 1;
        head = head->next;
    }
    return 0;
}

