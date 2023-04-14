
int lexicographic_sort(const char* a, const char* b)
{
    int i;
    for(i = 0; a[i] && b[i]; i++)
    {
        if(a[i] < b[i])         return 1;
        else if(a[i] > b[i])    return 2;
    }
    
    if(a[i] == 0 && b[i] == 0)      return 0;
    if(a[i] == 0)                   return 1;
    return 2;
}


int lexicographic_sort_reverse(const char* a, const char* b)
{
    int x = lexicographic_sort(a, b);
    
    if(x == 0)      return 0;
    if(x == 1)      return 2;
    return 1;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) 
{
    char isCharExcist[26] = {0};
    for(int i = 0; a[i]; i++)
        isCharExcist[a[i] - 'a'] = 1;
    
    char aCharCnt = 0;
    for (int i = 0; i < 26; i++)
    {
        aCharCnt += isCharExcist[i];
        isCharExcist[i] = 0;
    }
    
    for(int i = 0; b[i]; i++)
        isCharExcist[b[i] - 'a'] = 1;
    
    char bCharCnt = 0;
    for (int i = 0; i < 26; i++)
    {
        bCharCnt += isCharExcist[i];
    }
    
    
    if(aCharCnt <  bCharCnt)    return 1;
    if(aCharCnt >  bCharCnt)    return 2;
    
    return lexicographic_sort(a, b);
}



int sort_by_length(const char* a, const char* b) 
{
    int aLen = strlen(a);
    int bLen = strlen(b);
    
    if(aLen == bLen)       return lexicographic_sort(a, b);
    if(aLen <  bLen)       return 1;
    return 2;
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b))
{
    for(int i = 0; i < len - 1; i++)
    {
        int firstStringIdx = i;
        for(int j = i + 1; j < len; j++)
        {
            if(cmp_func(arr[firstStringIdx], arr[j]) == 2)
                firstStringIdx = j;
        }
        
        char* temp = arr[i];
        arr[i] = arr[firstStringIdx];
        arr[firstStringIdx] = temp;

    }
}

