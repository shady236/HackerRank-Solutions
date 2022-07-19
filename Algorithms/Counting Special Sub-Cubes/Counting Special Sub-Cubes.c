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

int arrMax(int* arr, int arrSize)
{
    int max = arr[0];
    
    for(int i = 0; i < arrSize; i++)
        if(arr[i] > max)
            max = arr[i];
    
    return max;
}

/*
 * Complete the 'specialSubCubes' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY cube as parameter.
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
int* specialSubCubes(int cube_count, int* cube, int* result_count)
{
    int* res = malloc(cube_count * sizeof(int));
    *result_count = cube_count;
    
    int*** (cubesMax[50]);
    cubesMax[0] = malloc(cube_count * sizeof(int**));
    for(int x = 0; x < cube_count; x++)
    {
        cubesMax[0][x] = malloc(cube_count * sizeof(int*));
        for(int y = 0; y < cube_count; y++)
        {
            cubesMax[0][x][y] = malloc(cube_count * sizeof(int));
            for(int z = 0; z < cube_count; z++)
                cubesMax[0][x][y][z] = cube[x * cube_count * cube_count + y * cube_count + z];
        }
    }
    
    int mergedCubes[8];
    
    for(int i = 1; i < cube_count; i++)
    {
        int cubesCnt = cube_count - i;
        
        cubesMax[i] = malloc(cubesCnt * sizeof(int**));
        
        for(int x = 0; x < cubesCnt; x++)
        {
            cubesMax[i][x] = malloc(cubesCnt * sizeof(int*));
            for(int y = 0; y < cubesCnt; y++)
            {
                cubesMax[i][x][y] = malloc(cubesCnt * sizeof(int));
                for(int z = 0; z < cubesCnt; z++)
                {
                    for(int xItr = 0; xItr < 2; xItr++)
                        for(int yItr = 0; yItr < 2; yItr++)
                            for(int zItr = 0; zItr < 2; zItr++)
                                mergedCubes[xItr * 4 + yItr * 2 + zItr] = cubesMax[i - 1][x + xItr][y + yItr][z + zItr];
                    
                    cubesMax[i][x][y][z] = arrMax(mergedCubes, 8);
                }
            }
        }
    }
    
    
    
    for(int i = 0; i < cube_count; i++)
    {
        res[i] = 0;
        int cubesCnt = cube_count - i;
        
        for(int x = 0; x < cubesCnt; x++)
        {
            for(int y = 0; y < cubesCnt; y++)
            {
                for(int z = 0; z < cubesCnt; z++)
                {
                    if(cubesMax[i][x][y][z] == i + 1)
                        res[i]++;
                }
            }
        }
    }
    
    
    for(int i = cube_count - 1; i >= 0; i--)
    {
        int cubesCnt = cube_count - i;
        
        for(int x = 0; x < cubesCnt; x++)
        {
            for(int y = 0; y < cubesCnt; y++)
            {
                free(cubesMax[i][x][y]);
            }
            free(cubesMax[i][x]);
        }
        free(cubesMax[i]);
    }
    
    
    
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** cube_temp = split_string(rtrim(readline()));

        int* cube = malloc((n * n * n) * sizeof(int));

        for (int i = 0; i < n * n * n; i++) {
            int cube_item = parse_int(*(cube_temp + i));

            *(cube + i) = cube_item;
        }

        int result_count;
        int* result = specialSubCubes(n, cube, &result_count);

        for (int i = 0; i < result_count; i++) {
            fprintf(fptr, "%d", *(result + i));

            if (i != result_count - 1) {
                fprintf(fptr, " ");
            }
        }

        fprintf(fptr, "\n");
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
