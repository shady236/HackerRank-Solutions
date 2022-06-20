#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define PARENT(i)       ((i)>>1)
#define LEFT(i)         ((i)<<1)
#define RIGHT(i)       (((i)<<1) + 1)

void heapAllocateBelow(int* heap, int heapSize, int idx)
{
    int left  = LEFT(idx);
    int right = RIGHT(idx);
    
    int smallest = idx;
    if(right < heapSize && heap[right] < heap[smallest])
        smallest = right;
        
    if(left < heapSize && heap[left] < heap[smallest])
        smallest = left;
    
    if(smallest != idx)
    {
        int tmp = heap[idx];
        heap[idx] = heap[smallest];
        heap[smallest] = tmp;
        heapAllocateBelow(heap, heapSize, smallest);
    }
}

void heapAllocateAbove(int* heap, int idx)
{
    int par = PARENT(idx);
    if(par >= 0 && heap[idx] < heap[par])
    {
        int tmp = heap[par];
        heap[par] = heap[idx];
        heap[idx] = tmp;
        heapAllocateAbove(heap, par);
    }
}

void insert(int* heap, int* heapSize, int data)
{
    heap[*heapSize] = data;
    (*heapSize)++;
    
    heapAllocateAbove(heap, (*heapSize) - 1);
}

void delete(int* heap, int* heapSize, int data)
{
    int dataIdx = 0;
    for(; dataIdx<*heapSize; dataIdx++)
        if(data == heap[dataIdx])
            break;
    
    (*heapSize)--;
    int tmp = heap[*heapSize];
    heap[*heapSize] = heap[dataIdx];
    heap[dataIdx]   = tmp;
    
    heapAllocateBelow(heap, *heapSize, dataIdx);
}

int main()
{
    int heap[100000] = {0};
    int heapSize = 0;
    
    int q, op, v;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                scanf("%d", &v);
                insert(heap, &heapSize, v);
            break;
            
            case 2:
                scanf("%d", &v);
                delete(heap, &heapSize, v);
            break;
            
            case 3:
                printf("%d\n", heap[0]);
            break;
        }
    }
    
    return 0;
}
