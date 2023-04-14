

double areaSquare(triangle* tr)
{
    double p = ((tr->a) + (tr->b) + (tr->c)) / 2.0;
    return p * (p - (tr->a)) * (p - (tr->b)) * (p - (tr->c));
}

int minTriangleIdx(triangle* tr, int trSize)
{
    int minIdx = 0;

    for(int i = 1; i < trSize; i++)
    {
        if(areaSquare(&tr[i]) < areaSquare(&tr[minIdx]))
            minIdx = i;
    }
    
    return minIdx;
}

void swap(triangle* tr1, triangle* tr2)
{
    triangle temp = *tr1;
    *tr1 = *tr2;
    *tr2 = temp;
}

void sort_by_area(triangle* tr, int n)
{
	for(int i = 0; i < n - 1; i++)
    {
        int minIdx = i + minTriangleIdx(tr + i, n - i);
        swap(&tr[i], &tr[minIdx]);
    }
}

