
int  sum (int count,...) 
{
    int sum = 0;
    
    va_list ptr;
    va_start(ptr, count);
    for(int i = 0; i < count; i++)
    { 
        sum += va_arg(ptr, int);
    }
    va_end(ptr);
    
    return sum;
}

int min(int count,...) 
{
    int min = 10000000;
    
    va_list ptr;
    va_start(ptr, count);
    for(int i = 0; i < count; i++)
    {
        int x = va_arg(ptr, int);
        if(x < min)   min = x;
    }
    va_end(ptr);
    
    return min;
}

int max(int count,...) 
{
    int max = 0;
    
    va_list ptr;
    va_start(ptr, count);
    for(int i = 0; i < count; i++)
    {
        int x = va_arg(ptr, int);
        if(x > max)   max = x;
    }
    va_end(ptr);
    
    return max;
}

