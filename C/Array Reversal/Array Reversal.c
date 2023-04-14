#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{
    int num, *arr, i;
    scanf("%d", &num);
    arr = (int*) malloc(num * sizeof(int));
    for(i = 0; i < num; i++) {
        scanf("%d", arr + i);
    }


    /* Write the logic to reverse the array. */
    for(i = 0; i < (num>>1); i++)
        swap(arr + i, arr + num - 1 - i);
    

    for(i = 0; i < num; i++)
        printf("%d ", *(arr + i));
    return 0;
}
