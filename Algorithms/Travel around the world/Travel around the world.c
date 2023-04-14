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
unsigned long long parse_long(char*);


typedef struct 
{
    uint64_t endCity;  // far Rechable City
    uint64_t remFuel;  // remainder Fuel at end city
    uint64_t maxFuel;  // max fuel during journey
    char isTraveled;
}CityInfo_t;


uint64_t max(uint64_t a, uint64_t b)
{
    if(a > b)
        return a;
    return b;
}


uint64_t min(uint64_t a, uint64_t b)
{
    if(a < b)
        return a;
    return b;
}


/*
 * Complete the 'travelAroundTheWorld' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY a
 *  2. INTEGER_ARRAY b
 *  3. LONG_INTEGER c
 */

int travelAroundTheWorld(int a_count, int* a,  int b_count, int* b, unsigned long long c) 
{
    CityInfo_t citiesInfo[100000];
    
    //intialize last element citiesInfo[a_count - 1]
    citiesInfo[a_count - 1].isTraveled  =  0;
    citiesInfo[a_count - 1].maxFuel     =  0;
    citiesInfo[a_count - 1].endCity     =  a_count - 1;
    citiesInfo[a_count - 1].remFuel     =  0;
    
    uint64_t fuel = 0;
    do
    {
        uint64_t initFuel = fuel;
        
        fuel = min(
            fuel + a[citiesInfo[a_count - 1].endCity], 
            c
        );
        
        if(fuel >= b[citiesInfo[a_count - 1].endCity])
        {
            citiesInfo[a_count - 1].maxFuel = max(
                citiesInfo[a_count - 1].maxFuel, 
                fuel
            );
            
            citiesInfo[a_count - 1].isTraveled = 1;
            fuel -= b[citiesInfo[a_count - 1].endCity];
            citiesInfo[a_count - 1].endCity++;
            
            if(citiesInfo[a_count - 1].endCity == a_count)
                citiesInfo[a_count - 1].endCity = 0;
        }
        else 
        {
            citiesInfo[a_count - 1].remFuel = initFuel;
            break;
        }
    }while(citiesInfo[a_count - 1].endCity != a_count - 1);
    
    
    for(int strtCity = a_count - 2; strtCity >= 0; strtCity--)
    {
        citiesInfo[strtCity].isTraveled  =  0;
        citiesInfo[strtCity].maxFuel     =  0;
        citiesInfo[strtCity].remFuel     =  0;
        citiesInfo[strtCity].endCity     =  strtCity;
        
        fuel = min(a[strtCity], c);
        
        if(fuel < b[strtCity])
            continue;
        
        
        uint64_t maxFuel = fuel;
        uint64_t endCity = strtCity + 1;
        fuel -= b[strtCity];
        
        do 
        {
            if(citiesInfo[endCity].isTraveled)
            {
                fuel = min(
                    fuel + citiesInfo[endCity].remFuel,
                    c
                );
                
                if(fuel + citiesInfo[endCity].maxFuel >= c)
                    fuel = citiesInfo[endCity].remFuel;
                
                maxFuel = max(
                    maxFuel,
                    min(
                        fuel + citiesInfo[endCity].maxFuel, 
                        c
                    )
                );
                
                maxFuel = max(maxFuel, fuel);
                
                if(citiesInfo[endCity].endCity > endCity || citiesInfo[endCity].endCity <= strtCity)
                    endCity = citiesInfo[endCity].endCity;
                else 
                    endCity = strtCity;
            }
            else 
            {
                uint64_t initFuel = fuel;
                
                fuel = min(fuel + a[endCity], c);
                
                if(fuel >= b[endCity])
                {
                    maxFuel = max(maxFuel, fuel);
                    
                    fuel -= b[endCity];
                    endCity++;
                    
                    if(endCity == a_count)
                        endCity = 0;
                }
                else 
                {
                    fuel = initFuel;
                    break;
                }
            }
        }while (endCity > strtCity);
        
        
        
        if(endCity > strtCity)
        {
            citiesInfo[strtCity].endCity = endCity;
            citiesInfo[strtCity].remFuel = fuel;
            citiesInfo[strtCity].maxFuel = maxFuel;
            citiesInfo[strtCity].isTraveled = 1;
            
            continue;
        }
        
        
        while(endCity < strtCity)
        {
            uint64_t initFuel = fuel;
            
            fuel = min(fuel + a[endCity], c);
            
            if(fuel >= b[endCity])
            {
                maxFuel = max(maxFuel, fuel);
                
                fuel -= b[endCity];
                endCity++;
            }
            else 
            {
                fuel = initFuel;
                break;
            }
        }
        
        
        citiesInfo[strtCity].endCity = min(endCity, strtCity);
        citiesInfo[strtCity].remFuel = fuel;
        citiesInfo[strtCity].maxFuel = maxFuel;
        citiesInfo[strtCity].isTraveled = 1;
    }
    
    
    
    int count = 0;
    
    for(int i = 0; i < a_count; i++)
    {
        if(citiesInfo[i].isTraveled && citiesInfo[i].endCity == i)
            count++;
    }
    
    return count;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    unsigned long long c = parse_long(*(first_multiple_input + 1));

    char** a_temp = split_string(rtrim(readline()));

    int* a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int a_item = parse_int(*(a_temp + i));

        *(a + i) = a_item;
    }

    char** b_temp = split_string(rtrim(readline()));

    int* b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int b_item = parse_int(*(b_temp + i));

        *(b + i) = b_item;
    }

    int result = travelAroundTheWorld(n, a, n, b, c);

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
    int value = strtoul(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

unsigned long long parse_long(char* str) {
    char* endptr;
    unsigned long long value = strtoull(str, &endptr, 0);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
