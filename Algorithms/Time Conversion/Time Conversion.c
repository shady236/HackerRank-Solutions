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

// convert ASCII char to int 
#define  charToInt(c)        ((c) - '0')

// convert a string of 2 chars to int
#define  strToInt(str)  ((charToInt(str[0]) * 10) + charToInt(str[1]))


// convert one digit int to ASCII char
#define  digitToASCII(d)        ((d) + '0')

// convert 2 digit int to a string
void intToStr(char n, char* str)
{
    str[1] = digitToASCII(n % 10);
    str[0] = digitToASCII((n / 10) % 10);
}

/*
 * Complete the 'timeConversion' function below.
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
char* timeConversion(char* s)
{
    char* time24Format = malloc(9 * sizeof(char));
    time24Format[8] = 0;        // NULL terminator 
    
    // copy minutes, seconds and : symbols 
    for (int i = 2; i < 8; i++)
    {
        time24Format[i] = s[i]; 
    }
    
    // first 2 chars represnts hour
    char hour12Format = strToInt(s);
    char hour24Format = 0;
    
    switch (s[8])
    {
        // case AM
        case 'A':
        case 'a':
            /*
             * 12 AM correponds to 00 in 24 format
             * else, hh AM correponds to hh in 24 format
             */
            if(hour12Format == 12)     hour24Format = 0;
            else            hour24Format = hour12Format;
        break;
        
        // case PM
        case 'P':
        case 'p':
            /*
             * 12 PM correponds to 12 in 24 format
             * else, hh PM correponds to hh + 12 in 24 format
             */
            if(hour12Format == 12)     hour24Format = 12;
            else        hour24Format = hour12Format + 12;
        break;
    }
    
    // copy hours to result string
    intToStr(hour24Format, time24Format);
    
    return time24Format;
}


int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = timeConversion(s);

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
