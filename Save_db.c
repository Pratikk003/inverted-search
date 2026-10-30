#include "header.h"

int save_db(Hash_t *ht)
{
    char filename[100];
    printf("Enter the fileName: ");
    scanf("%99s", filename);

    char *extn = strrchr(filename, '.');
    if (extn == NULL || strcmp(extn, ".txt") != 0)
    {
        printf("Error: Invalid file extension. Please use '.txt' file.\n");
        return FAILURE;
    }

    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Error: Unable to open or create file %s\n", filename);
        return FAILURE;
    }

    for (int i = 0; i < 27; i++)
    {
        if (ht[i].link == NULL)
        {
            continue;
        }

        Mlist *mtemp = ht[i].link;

        while (mtemp != NULL)
        {
            fprintf(fptr, "#%d;%s;%d", i, mtemp->word, mtemp->fileCount);

            Slist *stemp = mtemp->sublink;

            while (stemp != NULL)
            {
                fprintf(fptr, ";%s;%d", stemp->fileName, stemp->wordCount);
                stemp = stemp->link;
            }
            
            fprintf(fptr, "\n");
            mtemp = mtemp->link;
        }
    }

    fclose(fptr);
    printf("Database successfully saved in \"%s\"!\n", filename);
    return SUCCESS;
}
