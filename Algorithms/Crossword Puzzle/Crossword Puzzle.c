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


#define  CROSSWORD_LEN   (10)
#define  MAZ_WORD_LEN    CROSSWORD_LEN

#define  BLOCKED         ('+')
#define  EMPTY           ('-')

#define  RIGHT      ('R')
#define  LEFT       ('L')
#define  UP         ('U')
#define  DOWN       ('D')


char tryToFillWord(char** crossword, char* word, char dir, int i, int j)
{
    int wordIdx = 0;
    
    switch (dir) 
    {
        case RIGHT:
            for(; j < CROSSWORD_LEN && word[wordIdx]; j++)
            {
                char cantFit = (
                    (crossword[i][j] != EMPTY) && 
                    (crossword[i][j] != word[wordIdx])
                );
                
                if(cantFit)     return 0;
                
                crossword[i][j] = word[wordIdx];
                wordIdx++;
            }
        break;
        
        case LEFT:
            for(; j >= 0 && word[wordIdx]; j--)
            {
                char cantFit = (
                    (crossword[i][j] != EMPTY) && 
                    (crossword[i][j] != word[wordIdx])
                );
                
                if(cantFit)     return 0;
                
                crossword[i][j] = word[wordIdx];
                wordIdx++;
            }
        break;
        
        case DOWN:
            for(; i < CROSSWORD_LEN && word[wordIdx]; i++)
            {
                char cantFit = (
                    (crossword[i][j] != EMPTY) && 
                    (crossword[i][j] != word[wordIdx])
                );
                
                if(cantFit)     return 0;
                
                crossword[i][j] = word[wordIdx];
                wordIdx++;
            }
        break;
                
        case UP:
            for(; i >= 0 && word[wordIdx]; i--)
            {
                char cantFit = (
                    (crossword[i][j] != EMPTY) && 
                    (crossword[i][j] != word[wordIdx])
                );
                
                if(cantFit)     return 0;
                
                crossword[i][j] = word[wordIdx];
                wordIdx++;
            }
        break;
    }
    
    return (word[wordIdx] == 0);
}



void deinitCrossword(char** crossword, char (*initCrossword)[CROSSWORD_LEN])
{
    for(int i = 0; i < CROSSWORD_LEN; i++)
        for(int j = 0; j < CROSSWORD_LEN; j++)
            crossword[i][j] = initCrossword[i][j];
}


char solvePuzzle(char** crossword, char** words, int wordsSize)
{
    // if all words are filled, solution is done
    if(wordsSize == 0)      return 1;
    
    static char dir[4] = {RIGHT, LEFT, UP, DOWN};
    
    // copy intial crossword
    char initCrossword[CROSSWORD_LEN][CROSSWORD_LEN];
    for(int i = 0; i < CROSSWORD_LEN; i++)
        for(int j = 0; j < CROSSWORD_LEN; j++)
            initCrossword[i][j] = crossword[i][j];
    
    
    for(int i = 0; i < CROSSWORD_LEN; i++)
    {
        for(int j = 0; j < CROSSWORD_LEN; j++)
        {
            if(crossword[i][j] == BLOCKED)
                continue;
            
            for(int d = 0; d < 4; d++)
            {
                // try to fill word from this square
                char isWordFilled = tryToFillWord(crossword, words[0], dir[d], i, j);
                
                if(!isWordFilled)
                {
                    // unfill word
                    deinitCrossword(crossword, initCrossword);
                    continue;
                }
                
                char isOtherWordsFilled = solvePuzzle(crossword, words + 1, wordsSize - 1);
                
                if(isOtherWordsFilled)      return 1;

                deinitCrossword(crossword, initCrossword);
            }
        }
    }
    
    return 0;
}


/*
 * Complete the 'crosswordPuzzle' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY crossword
 *  2. STRING words
 */

/*
 * To return the string array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * char** return_string_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static char* a[5] = {"static", "allocation", "of", "string", "array"};
 *
 *     return a;
 * }
 *
 * char** return_string_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     char** a = malloc(5 * sizeof(char*));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = malloc(20 * sizeof(char));
 *     }
 *
 *     *(a + 0) = "dynamic";
 *     *(a + 1) = "allocation";
 *     *(a + 2) = "of";
 *     *(a + 3) = "string";
 *     *(a + 4) = "array";
 *
 *     return a;
 * }
 *
 */


#define  SEPRATOR   (';')

char** crosswordPuzzle(int crossword_count, char** crossword, char* words, int* result_count) 
{
    *result_count = crossword_count;
    
    char* parsedWords[100];
    parsedWords[0] = malloc(11 * sizeof(char));
    
    int wordsCnt = 0;
    int charsCnt = 0;
    for(int i = 0; words[i]; i++)
    {
        switch (words[i]) 
        {
            case SEPRATOR:
                parsedWords[wordsCnt][charsCnt] = 0;
                wordsCnt++;
                parsedWords[wordsCnt] = malloc(11 * sizeof(char));
                charsCnt = 0;
            break;
            
            default:
                parsedWords[wordsCnt][charsCnt] = words[i];
                charsCnt++;
            break;
        }
    }
    
    wordsCnt++;     // last word has no ; after it
    
    solvePuzzle(crossword, parsedWords, wordsCnt);
    
    return crossword;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** crossword = malloc(10 * sizeof(char*));

    for (int i = 0; i < 10; i++) {
        char* crossword_item = readline();

        *(crossword + i) = crossword_item;
    }

    char* words = readline();

    int result_count;
    char** result = crosswordPuzzle(10, crossword, words, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

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
