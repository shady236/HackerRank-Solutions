#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define  MAX_STR_LEN    1000

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    
    char str[MAX_STR_LEN + 1];
    scanf("%s", str);
    
    int freq[10] = {0};
    for(int i = 0; str[i]; i++)
    {
        if(str[i]>='0' && str[i]<='9')
            freq[str[i]-'0']++;
    }

    for(int i = 0; i < 10; i++)
        printf("%d ", freq[i]);
    
    return 0;
}
