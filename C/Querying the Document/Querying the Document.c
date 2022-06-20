

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n)
{
    return document[n - 1][m - 1][k - 1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m)
{
    return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, int k)
{
    return document[k - 1];
}

char**** get_document(char *text)
{
    char**** document = malloc(5 * sizeof(char***));
    
    for(int i = 0; i < 5; i++)
    {
        document[i] = malloc(30 * sizeof(char**));
        for(int j = 0; j < 30; j++)
        {
            document[i][j] = malloc(40 * sizeof(char*));
            for(int k = 0; k < 40; k++)
            {
                document[i][j][k] = malloc(20 * sizeof(char));
                for(int m = 0; m < 20; m++)
                {
                    document[i][j][k][m] = 0;
                }
            }
        }
    }
    
    unsigned int currentCharacter = 0;
    unsigned int currentWord = 0;
    unsigned int currentSentence = 0;
    unsigned int currentParagraph = 0;
    
    
    for(int i = 0; text[i]; i++)
    {
        switch (text[i])
        {
        case ' ':
            document[currentParagraph][currentSentence][currentWord][currentCharacter] = 0;
            currentWord++;
            currentCharacter = 0;
            break;

        case '\n':
            currentParagraph++;
            currentSentence = 0;
            currentWord = 0;
            currentCharacter = 0;
            break;

        case '.':
            switch (text[i + 1])
            {
            case '\n':
                currentParagraph++;
                currentSentence = 0;
                currentWord = 0;
                currentCharacter = 0;
                i++;
                break;

            default:
                currentSentence++;
                currentWord = 0;
                currentCharacter = 0;
                break;
            }
            break;

        default:
            document[currentParagraph][currentSentence][currentWord][currentCharacter] = text[i];
            currentCharacter++;
            break;
        }
    }
    
    return document;
}

