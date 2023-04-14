

// Complete the findMergeNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2)
{
    SinglyLinkedListNode* list1Node = head1;
    SinglyLinkedListNode* list2Node = head2;
    
    while(list1Node)
    {
        list2Node = head2;
        while(list2Node)
        {
            if(list2Node == list1Node)
            {
                return list1Node->data;
            }
            list2Node = list2Node->next;
        }
        list1Node = list1Node->next;
    }
    
    return -1;
}

