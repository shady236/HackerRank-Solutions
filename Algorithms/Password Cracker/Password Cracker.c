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
char** split_string(char*);

int parse_int(char*);


char isStringEqual(char* s1, char* s2)
{
    return (strcmp(s1, s2) == 0);
}

char isStringStartsWith(char* str, char* ptrn)
{
    for(int i = 0; ptrn[i]; i++)
    {
        if(str[i] != ptrn[i])
            return 0;
    }
    
    return 1;
}


/*
 * function try to form the loginAttept from the given password
 * 
 * if there's a way to do that, it stores the indeces of 
 * passwords that form the loginAttempt in res array in reverse order
 * (the first password is at res[0], the last password is at res[res_size - 1])
 * and return true (1) as cracking is possible
 * 
 * otherwise, it returns false (0) as cracking is not possible
 */

char recursivePasswordCracker(int passwords_count, char **passwords, int *passwordLen, char *loginAttempt, int loginAttemptLen, int *res, int *resultSize, char *cantBeCracked)
{
    if (cantBeCracked[loginAttemptLen])
        return 0;
    
    for (int i = 0; i < passwords_count; i++)
    {
        // if the password is too long, it can't form the loginAttempt
        if (passwordLen[i] > loginAttemptLen)
            continue;
        
        // if loginAttempt starts with the password, this password can form the loginAttempt
        if (isStringStartsWith(loginAttempt, passwords[i]))
        {
            // check if remaining string of loginAttempt can be formed by the passwords
            char isRemValid = 1;
            if (passwordLen[i] < loginAttemptLen)   // if there's a remaining string of loginAttempt
            {
                isRemValid = recursivePasswordCracker(passwords_count, passwords, passwordLen, loginAttempt + passwordLen[i], loginAttemptLen - passwordLen[i], res, resultSize, cantBeCracked);
            }
            
            if (isRemValid)
            {
                /* 
                 * loginAttempt can be formed by the password at index i
                 * password index (i) should be added to the result array
                 */
                res[*resultSize] = i;
                (*resultSize)++;
                return 1;
            }
        }
    }
    
    /*
     * if program reaches here, loginAttempt can't be formed by the passwords
     * so, we mark the loginAttempt as "cantBeCracked" to avoid checking it again
     * and return false (0)
     */
    cantBeCracked[loginAttemptLen] = 1;
    return 0;
}


/*
 * Complete the 'passwordCracker' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING_ARRAY passwords
 *  2. STRING loginAttempt
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
char *passwordCracker(int passwords_count, char **passwords, char *loginAttempt)
{
    static char wrong[] = "WRONG PASSWORD";

    // dp to storte if the remaining of loginAttempt can't be cracked
    char cantBeCracked[2001];
    for (int i = 0; i < 2001; i++)
        cantBeCracked[i] = 0;

    // length of all passwords to avoid multiple calculations
    int passwordLen[10];
    for (int i = 0; i < passwords_count; i++)
        passwordLen[i] = strlen(passwords[i]);

    // resIdx will store reverse indeces of passwords that can form the loginAttempt
    int resIdx[2001];
    int resIdxSize = 0;
    char isValid = recursivePasswordCracker(passwords_count, passwords, passwordLen, loginAttempt, strlen(loginAttempt), resIdx, &resIdxSize, cantBeCracked);
    
    
    if (!isValid)
        return wrong;
    
    
    // res will store the actual passwords that can form the loginAttempt
    char *res = malloc(5000 * sizeof(char));
    // construct the result from end to start
    for (int i = resIdxSize - 1; i > 0; i--)
    {
        strcat(res, passwords[resIdx[i]]);
        strcat(res, " ");
    }
    strcat(res, passwords[resIdx[0]]);

    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** passwords_temp = split_string(rtrim(readline()));

        char** passwords = malloc(n * sizeof(char*));

        for (int i = 0; i < n; i++) {
            char* passwords_item = *(passwords_temp + i);

            *(passwords + i) = passwords_item;
        }

        char* loginAttempt = readline();

        char* result = passwordCracker(n, passwords, loginAttempt);

        fprintf(fptr, "%s\n", result);
    }

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

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
