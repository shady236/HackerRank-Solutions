#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

#define  MAX_LEN    (10000)


void reverse(char* s, int len)
{
    for(int i = 0; i < (len>>1); i++)
    {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

/*
 * Complete the 'reverseShuffleMerge' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* reverseShuffleMerge(char* s)
{
    int len = strlen(s);
    
    /*
     * intially, s = merge(reverse(A), shuffle(A))
     * let s = reverse(s)
     * then, s = reverse(merge(reverse(A), shuffle(A)))
     *       s = merge(reverse(A), reverse(shuffle(A)))
     *       s = merge(A, shuffle(A))
     */
    reverse(s, len);
    
    
    /*
     * as s = merge(A, shuffle(A))
     * amd shuffle(A) has the same characters of A with 
     * diffrent order
     * 
     * so, if s has character <ch> repeated n times, A must 
     * contain character <ch> repeated n/2 times 
     */
    int totalFreq[26] = {0};
    for(int i = 0; s[i]; i++)
        totalFreq[s[i] - 'a']++;
    
    
    int goalFreq[26];
    for(int ch = 0; ch < 26; ch++)
        goalFreq[ch] = totalFreq[ch]>>1;
    
    /*
     * take first ocurrences for each charcter 
     */
    int isCharInRes[MAX_LEN] = {0};
    for(int i = 0; s[i]; i++)
    {
        if(goalFreq[s[i] - 'a'])
        {
            isCharInRes[i] = 1;
            goalFreq[s[i] - 'a']--;
        }
    }
    
    
    /*
     * try to shuffle A to get smallest A
     * 
     * let character <ch1> followed by charcter <ch2> 
     * where <ch2> is smaller than <ch1>, then:
     *   - search for another ocurrence of <ch1> after <ch2>
     *   - if it exists, then include this charcter instead 
     *     of the used one
     */
    int resCurrCharIdx = 0;
    
    while(resCurrCharIdx < len)
    {
        /*
         * go to first char included in result, i.e. <ch1>
         */
        while(resCurrCharIdx < len && isCharInRes[resCurrCharIdx] == 0)
            resCurrCharIdx++;
        
        /*
         * if there's no charcters, A can't be shuffeled more
         */
        if(resCurrCharIdx >= len)
            break;
        
        /*
         * get next first char included in result, i.e. <ch2>
         */
        int resNextCharIdx = resCurrCharIdx + 1;
        while(resNextCharIdx < len && isCharInRes[resNextCharIdx] == 0)
            resNextCharIdx++;
        
        
        /*
         * if there's no charcters, A can't be shuffeled more
         */
        if(resNextCharIdx >= len)
            break;
        
        
        char ch1 = s[resCurrCharIdx];
        char ch2 = s[resNextCharIdx];
        
        /*
         * if <ch2> >= <ch1>, they are in the smallest order,
         * don't shuffle it, but go to <ch2>
         */
        if(ch2 >= ch1)
        {
            resCurrCharIdx = resNextCharIdx;
            continue;
        }
        
        
        /*
         * here, <ch2> must be higher than <ch1>, so search 
         * for another ocurrence of <ch1> after <ch2>
         */ 
        int i;
        for(i = resNextCharIdx + 1; i < len; i++)
        {
            /*
             * if char is already included in resut, it
             * can't be included again, skip it
             * 
             * if char isn't <ch1>, skip it
             */
            if(isCharInRes[i] || s[i] != ch1)
                continue;
            
            /*
             * if <ch1> is found at i (after <ch2>), include
             * it in result instead of the one before <ch2>
             */
            isCharInRes[resCurrCharIdx] = 0;
            isCharInRes[i] = 1;
            
            /*
             * return to start of the result to start 
             * checking for available shuffles from there
             */
            resCurrCharIdx = 0;
            break;
        }
        
        /*
         * if seaech fails, i.e. <ch1> isn't found after 
         * <ch2>, go to <ch2>
         */
        if(i >= len)
            resCurrCharIdx = resNextCharIdx;
    }
    
    
    /* construct the result */
    char* res = malloc(((len>>1) + 1) * sizeof(char));
    int resIdx = 0;
    for(int i = 0; s[i]; i++)
    {
        if(isCharInRes[i])
        {
            res[resIdx] = s[i];
            resIdx++;
        }
    }
    res[len>>1] = 0;     // NULL
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = reverseShuffleMerge(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}
