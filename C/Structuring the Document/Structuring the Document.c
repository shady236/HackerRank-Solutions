


struct document get_document(char* text)
{
    struct document doc = {0};
    doc.data = malloc(5 * sizeof(struct paragraph));
    for(int i = 0; i < 5; i++)
    {
        doc.data[i].sentence_count = 0;
        doc.data[i].data = malloc(40 * sizeof(struct sentence));
        
        for(int j = 0; j < 40; j++)
        {
            doc.data[i].data[j].word_count = 0;
            doc.data[i].data[j].data = malloc(40 * sizeof(struct word));
            
            for(int k = 0; k < 40; k++)
            {
                doc.data[i].data[j].data[k].data = malloc(20 * sizeof(char));
                
                for(int m = 0; m < 20; m++)
                {
                    doc.data[i].data[j].data[k].data[m] = 0;
                }
            }
        }
    }
    
    
    unsigned int currentCharacter = 0;
    unsigned int currentWord = 0;
    unsigned int currentSentence = 0;
    unsigned int currentParagraph = 0;
    
    for (int i = 0; text[i]; i++)
    {
        switch (text[i])
        {
        case ' ':
            doc.data[currentParagraph].data[currentSentence].data[currentWord].data[currentCharacter] = 0;
            currentWord++;
            doc.data[currentParagraph].data[currentSentence].word_count++;
            currentCharacter = 0;
            break;

        case '\n':
            doc.data[currentParagraph].data[currentSentence].word_count++;
            doc.data[currentParagraph].sentence_count++;
            currentParagraph++;
            doc.paragraph_count++;
            currentSentence = 0;
            currentWord = 0;
            currentCharacter = 0;
            break;

        case '.':
            switch (text[i + 1])
            {
            case '\n':
                doc.data[currentParagraph].data[currentSentence].word_count++;
                doc.data[currentParagraph].sentence_count++;
                currentParagraph++;
                doc.paragraph_count++;
                currentSentence = 0;
                currentWord = 0;
                currentCharacter = 0;
                i++;
                break;

            default:
                doc.data[currentParagraph].data[currentSentence].word_count++;
                currentSentence++;
                doc.data[currentParagraph].sentence_count++;
                currentWord = 0;
                currentCharacter = 0;
                break;
            }
            break;

        default:
            doc.data[currentParagraph].data[currentSentence].data[currentWord].data[currentCharacter] = text[i];
            currentCharacter++;
            break;
        }
    }
    
    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) 
{
    return Doc.data[n - 1].data[m - 1].data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m)
{
    return Doc.data[m - 1].data[k - 1];
}


struct paragraph kth_paragraph(struct document Doc, int k) 
{
    return Doc.data[k - 1];
}



