#include "header.h"

int search_db(Hash_t *ht, char *word)
{
    int index;
    if (isalpha(word[0]))
    {
        index = tolower(word[0]) - 'a';
    }
    else
    {
        index = 26;
    }

    if (ht[index].link == NULL)
    {
        printf("Word \"%s\" not present in database.\n", word);
        return FAILURE;
    }

    Mlist *mtemp = ht[index].link;
    while (mtemp != NULL)
    {
        if (strcmp(mtemp->word, word) == 0)
        {
            printf("[%d][%s] %dfiles\n", index, mtemp->word, mtemp->fileCount);

            Slist *stemp = mtemp->sublink;
            while (stemp != NULL)
            {
                printf(": file : %s : %dtimes\n", stemp->fileName, stemp->wordCount);
                stemp = stemp->link;
            }
            printf("\n\n");
            return SUCCESS; 
        }
        mtemp = mtemp->link;
    }
    
    printf("Word \"%s\" not present in database.\n", word);
    return FAILURE;
}
