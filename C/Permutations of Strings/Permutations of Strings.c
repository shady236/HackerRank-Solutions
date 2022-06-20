#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/
    
    for(int i = n-1; i > 0; i--)
    {
        if(strcmp(s[i], s[i-1]) > 0)
        {
            int idxOfMin = i - 1;
            for(int j = i; j < n; j++)
            {
                if((strcmp(s[i - 1], s[j]) < 0) && ((strcmp(s[idxOfMin], s[j]) >= 0) || idxOfMin == i - 1))
                    idxOfMin = j;
            }
            if(idxOfMin >= i)
            {
                char temp[12];
                strcpy(temp, s[i - 1]);
                strcpy(s[i - 1], s[idxOfMin]);
                strcpy(s[idxOfMin], temp);
                
                for(int j = i; j < ((n + i)>>1); j++)
                {
                    strcpy(temp, s[j]);
                    strcpy(s[j], s[n - 1 + i - j]);
                    strcpy(s[n - 1 + i - j], temp);
                }
                return 1;
            }
        }
    }
    
    return 0;
}

