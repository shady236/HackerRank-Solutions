

int main()
{
    int total_number_of_shelves;
    scanf("%d", &total_number_of_shelves);
    
    int total_number_of_queries;
    scanf("%d", &total_number_of_queries);
    
    while (total_number_of_queries--) {
        int type_of_query;
        scanf("%d", &type_of_query);
        
        if (type_of_query == 1) {
            /*
             * Process the query of first type here.
             */
            int x, y;
            scanf("%d %d", &x, &y);
            
            if(total_number_of_books == NULL)
            {
                total_number_of_books = malloc(total_number_of_shelves * sizeof(int));
                total_number_of_pages = malloc(total_number_of_shelves * sizeof(int*));
                
                for(int i = 0; i < total_number_of_shelves; i++)
                {
                    total_number_of_books[i] = 0;
                    total_number_of_pages[i] = NULL;
                }
            }
            
            total_number_of_books[x]++;
            
            if(total_number_of_pages[x] == NULL)
            {
                total_number_of_pages[x] = malloc(total_number_of_books[x] * sizeof(int));
                
                for(int i = 0; i < total_number_of_books[x]; i++)
                    total_number_of_pages[x][i] = 0;
            }
            else 
            {
                total_number_of_pages[x] = realloc(total_number_of_pages[x], total_number_of_books[x] * sizeof(int));
            }
            
            total_number_of_pages[x][total_number_of_books[x] - 1] = y;

