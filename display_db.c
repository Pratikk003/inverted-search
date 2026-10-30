#include "header.h"

int display_db(Hash_t *ht)
{
    printf("\n===================DATABASE=========================================");

    for (int i = 0; i < 27; i++)
    {
        // check whether this index contains any Mlist
        // If Mlist is empty move to next slot in Ht
        if (ht[i].link == NULL)
        {
            continue;
        }

        Mlist *mtemp = ht[i].link;

        while (mtemp != NULL)
        {
            printf("\n[%d][%s] %dfiles:", i, mtemp->word, mtemp->fileCount);

            // Taverse through subnode
            Slist *stemp = mtemp->sublink;

            while (stemp != NULL)
            {
                // print wordCount and FileName
                 printf("file : %s : %dtimes", stemp->fileName, stemp->wordCount);
                 stemp = stemp->link;
            }
            printf("\n");
            mtemp = mtemp->link;
        }
    }
    printf("\n====================================================================\n");
    return SUCCESS;
}
