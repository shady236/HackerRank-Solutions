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
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

#define  CHARS_CNT      (4)

/*
 * Complete the 'steadyGene' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING gene as parameter.
 */

int steadyGene(char* gene)
{
    const char chars[] = {'A', 'C', 'G', 'T'};
    
    int freq['T' + 1] = {0};
    for(int i = 0; gene[i]; i++)
        freq[gene[i]]++;
    
    
    int avgFreq = 0;
    for(int i = 0; i < CHARS_CNT; i++)
        avgFreq += freq[chars[i]];
    avgFreq = avgFreq / CHARS_CNT;
    
    
    /*
     * calculate excess freq above average frequency
     */
    int excessFreq['T' + 1] = {0};
    
    for(int i = 0; i < CHARS_CNT; i++)
    {
        if(freq[chars[i]] >= avgFreq)
            excessFreq[chars[i]] = freq[chars[i]] - avgFreq;
        else 
            excessFreq[chars[i]] = 0;
    }
    
    
    /*
     * min lenght to be replaced is equal to min lenght
     * contains chars with freq >= excessFreq
     * 
     * so, first calculate min range starting imdex 0
     * that contains chars with freq >= excessFreq
     * 
     * then, find min range starting from each index > 0
     * that contains chars with freq >= excessFreq
     */
    int rangeFreq['T' + 1] = {0};
    
    char isRangeValid = 1;    // is freq >= excessFreq
    for(int i = 0; i < CHARS_CNT; i++)
        isRangeValid &= rangeFreq[chars[i]] >= excessFreq[chars[i]];
    
    int end = 0;        // end of range
    while(!isRangeValid)
    {
        if(freq[gene[end]])     rangeFreq[gene[end]]++;
        
        isRangeValid = 1;
        for(int i = 0; i < CHARS_CNT; i++)
            isRangeValid &= rangeFreq[chars[i]] >= excessFreq[chars[i]];
        
        end++;
    }
    
    int minLen = end;
    
    /* 
     * now, find min range starting from each index > 0
     * that contains chars with freq >= excessFreq
     */
    for(int strt = 1; gene[strt]; strt++)
    {
        if(freq[gene[strt - 1]])
            rangeFreq[gene[strt - 1]]--;
        
        isRangeValid = 1;
        for(int i = 0; i < CHARS_CNT; i++)
            isRangeValid &= rangeFreq[chars[i]] >= excessFreq[chars[i]];
        
        while(!isRangeValid && gene[end])
        {
            if(freq[gene[end]])
                rangeFreq[gene[end]]++;
            
            isRangeValid = 1;
            for(int i = 0; i < CHARS_CNT; i++)
                isRangeValid &= rangeFreq[chars[i]] >= excessFreq[chars[i]];
            
            end++;
        }
        
        int len = end - strt;
        if(isRangeValid && minLen > len)
            minLen = len;
    }
    
    return minLen;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char* gene = readline();

    int result = steadyGene(gene);

    fprintf(fptr, "%d\n", result);

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

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
