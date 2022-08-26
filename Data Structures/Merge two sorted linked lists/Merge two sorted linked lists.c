

// Complete the mergeLists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2)
{
    SinglyLinkedListNode* resultHead ;
    SinglyLinkedListNode* srcNode;
    SinglyLinkedListNode* dstNode;
    if((head1->data) <= (head2->data))
    {
        resultHead = head1;
        srcNode    = head2;
        dstNode    = head1;
    }
    else
    {
        resultHead = head2;
        srcNode    = head1;
        dstNode    = head2;
    }
    
    
    SinglyLinkedListNode* srcNextNode;
    while(srcNode && dstNode->next)
    {
        srcNextNode = srcNode->next;
        
        if((srcNode->data) < (dstNode->next->data))
        {
            srcNode->next = dstNode->next;
            dstNode->next = srcNode;
            srcNode = srcNextNode;
            dstNode = dstNode->next;
        }
        else
        {
            dstNode = dstNode->next;
        }
    }
    
    if(srcNode)     dstNode->next = srcNode;
    
    return resultHead;
}

