#include "header.h"

int create_db(Flist *f_head,Hash_t *ht)
{
    Flist *temp = f_head;

    //traverse all files present in Flist
    while(temp != NULL)
    {
       FILE *fptr = fopen(temp->arr,"r");
       if (fptr == NULL)
       {
         printf("Error:Unable to open %s\n",temp->arr);
         return FAILURE;
       }
       printf("%s opened successfuly\n",temp->arr);
       char word[100];

       //read word by word
       while(fscanf(fptr,"%99s",word) != EOF)
       {
            printf("word = %s\n",word);
            int index;
            //hashing logic
            //word start with alphabetical char or not.
            if(isalpha(word[0]))
            {
                index = tolower(word[0]) - 'a';
            }
            else
            {
                index = 26;
            }
            printf("Word = %s,Index = %d\n",word,index);
            
            Mlist *mtemp = ht[index].link;

            while(mtemp != NULL)
            {
                if(strcmp(mtemp->word,word) == 0)
                {
                    break;
                }
                mtemp = mtemp->link;
            }
            //word does not exist in main list
            if(mtemp == NULL)
            {
                Mlist *newM = malloc(sizeof(Mlist));
                if(newM == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }
                newM->word = malloc(strlen(word) + 1);

                if(newM->word == NULL)
                {
                    free(newM);
                    fclose(fptr);
                    return FAILURE;
                }
                strcpy(newM->word,word);
                newM->fileCount = 1;

                //create first sublist node
                Slist *newS = malloc(sizeof(Slist));
                //check memory allocation for subnode
                if (newS == NULL)
                {
                    free(newM->word);
                    free(newM);
                    fclose(fptr);
                    return FAILURE;
                }
                newS->fileName = malloc(strlen(temp->arr) + 1);
                //check memory allocation for newS->fileName
                if (newS->fileName == NULL)
                {
                    free(newS);
                    free(newM->word);
                    free(newM);
                    fclose(fptr);
                    return FAILURE;
                }
                strcpy(newS->fileName,temp->arr);

                newS->wordCount = 1;
                newS->link = NULL;

                newM->sublink = newS;

                //insert newM at beginning of MainNode list
                newM->link = ht[index].link;
                ht[index].link = newM;

            }
            //word is already exists.
            else
            {
                Slist *stemp = mtemp->sublink;
                while(stemp != NULL)
                {
                    //word is prest  in existing file or not.
                    if(strcmp(stemp->fileName,temp->arr) == 0)
                    {
                        break;
                    }
                    stemp = stemp->link;
                }
                if(stemp != NULL)
                {
                    //same file
                    stemp->wordCount++;
                }
                else
                {
                    //differant file
                    //create new slist node

                    Slist *newS = malloc(sizeof(Slist));
                    //check memory allocation is successful or not
                    if (newS == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }
                    newS->fileName = malloc(strlen(temp->arr) + 1);
                    //check memory allocation is successful or not
                    if (newS->fileName == NULL)
                    {
                        free(newS); 
                        fclose(fptr); 
                        return FAILURE;
                    }
                    strcpy(newS->fileName,temp->arr);
                    newS->wordCount = 1;
                    newS->link = NULL;

                    //Insert slist node
                    newS->link = mtemp->sublink;
                    mtemp->sublink = newS;

                    //increse the file count
                    mtemp->fileCount++;

                }
            }

        }
       fclose(fptr);
       temp = temp->link;
    }
    return SUCCESS;
}