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

/*
 * Complete the 'aOrB' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. STRING a
 *  3. STRING b
 *  4. STRING c
 */

#define  GET_BIT(x, bit)        (((x)>>(bit)) & 1)
#define  CLR_BIT(x, bit)        (x &= ~(1U<<(bit)))
#define  SET_BIT(x, bit)        (x |=  (1U<<(bit)))

void aOrB(int k, char* a, char* b, char* c)
{
    int len;
    for(len = 0; a[len]; len++)
        if(a[len] <= '9')        a[len] -= '0';
        else                     a[len] -= 'A' - 10;
    
    for(int i=0; i<len; i++)
        if(b[i] <= '9')        b[i] -= '0';
        else                   b[i] -= 'A' - 10;
    
    for(int i=0; c[i]; i++)
        if(c[i] <= '9')        c[i] -= '0';
        else                   c[i] -= 'A' - 10;
    
    for(int i=0; k>=0 && i<len; i++)
    {
        for(int j=0; j<4; j++)
        {
            char aBit = GET_BIT(a[i], j);
            char bBit = GET_BIT(b[i], j);
            char cBit = GET_BIT(c[i], j);
            
            if(cBit)
            {
                if(!aBit && !bBit)
                {
                    k--;
                    SET_BIT(b[i], j);
                }
            }
            else 
            {
                if(aBit)
                {
                    k--;
                    CLR_BIT(a[i], j);
                }
                if(bBit)
                {
                    k--;
                    CLR_BIT(b[i], j);
                }
            }
        }
    }
    
    if(k < 0)
    {
        printf("-1\n");
        return;
    }
    
    
    
    for(int i=0; k>0 && i<len; i++)
    {
        for(int j=3; k>0 && j>=0; j--)
        {
            char aBit = GET_BIT(a[i], j);
            char bBit = GET_BIT(b[i], j);
            
            if(aBit && bBit)
            {
                k--;
                CLR_BIT(a[i], j);
            }
            else if(aBit && k>=2)
            {
                k -= 2;
                CLR_BIT(a[i], j);
                SET_BIT(b[i], j);
            }
        }
    }
    
    
    for(int i=0; i<len; i++)
        if(a[i] <= 9)        a[i] += '0';
        else                 a[i] += 'A' - 10;
    
    for(int i=0; i<len; i++)
        if(b[i] <= 9)        b[i] += '0';
        else                 b[i] += 'A' - 10;
    
    
    char isLeadingZerosEnded = 0;
    for(int i=0; i<len; i++)
    {
        if(a[i] > '0')
        {
            printf("%c", a[i]);
            isLeadingZerosEnded = 1;
        }
        else if(isLeadingZerosEnded || i == len - 1)
            printf("0");
    }
    printf("\n");
    
    isLeadingZerosEnded = 0;
    for(int i=0; i<len; i++)
    {
        if(b[i] > '0')
        {
            printf("%c", b[i]);
            isLeadingZerosEnded = 1;
        }
        else if(isLeadingZerosEnded || i == len - 1)
            printf("0");
    }
    printf("\n");
}

int main()
{
    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int k = parse_int(ltrim(rtrim(readline())));

        char* a = readline();

        char* b = readline();

        char* c = readline();

        aOrB(k, a, b, c);
    }

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
