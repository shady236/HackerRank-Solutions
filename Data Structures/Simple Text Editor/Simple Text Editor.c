#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct 
{
    char opCode;
    union
    {
        int appendedCnt;
        char* deleted;
    };
}Opration_t;

int main()
{
    int q, opCode, k, deleteFrom;
    char str[1000001] = {0};
    char w[1000001] = {0};
    char* tmp;
    
    scanf("%d", &q);
    Opration_t op[1000000] = {0};
    int opCnt = 0;
    
    while (q--) 
    {
        scanf("%d", &opCode);
        switch (opCode)
        {
            case 1:
                scanf("%s", w);
                strcat(str, w);
                op[opCnt].opCode = 1;
                op[opCnt].appendedCnt = strlen(w);
                opCnt++;
            break;
            
            case 2:
                scanf("%d", &k);
                deleteFrom = strlen(str) - k;
                
                op[opCnt].opCode = 2;
                op[opCnt].deleted = malloc(k + 1);
                strcpy(op[opCnt].deleted, str + deleteFrom);
                opCnt++;
                
                str[deleteFrom] = 0;
                
            break;
            
            case 3:
                scanf("%d", &k);
                printf("%c\n", str[k - 1]);
            break;
            
            case 4:
                opCnt--;
                switch(op[opCnt].opCode)
                {
                    case 1:
                        deleteFrom = strlen(str) - op[opCnt].appendedCnt;
                        str[deleteFrom] = 0;
                    break;
                    
                    case 2:
                        strcat(str, op[opCnt].deleted);
                        free(op[opCnt].deleted);
                        op[opCnt].deleted = NULL;
                    break;
                }
            break;
        }
        
    }
    return 0;
}
