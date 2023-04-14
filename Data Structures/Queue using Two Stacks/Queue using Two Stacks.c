#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define QUEUE_SIZE 100001

int queue[QUEUE_SIZE];
int queueSize = 0;

void enqueue(int x)
{
    queue[queueSize] = x;
    queueSize++;
}

void dequeue()
{
    if(queueSize <= 0)  return;
        
    for(int i=0; i<queueSize-1; i++)
        queue[i] = queue[i+1];
    
    queueSize--;
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int q;
    scanf("%d", &q);
    
    while(q--)
    {
        int type;
        int x;
        scanf("%d", &type);
        
        switch (type)
        {
            case 1:
                scanf("%d", &x);
                enqueue(x);
            break;
            
            case 2:
                dequeue();
            break;
            
            case 3:
                printf("%d\n", queue[0]);
            break;
        }
        
    }
    
        
    return 0;
}
