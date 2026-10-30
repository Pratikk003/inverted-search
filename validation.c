#include "header.h"

int read_and_validation(int argc,char *argv[],Flist **head)
{
    int valid_file_count = 0; 
    if (argc < 2)
    {
        printf("Error: Please pass file names through command line.\n");
        printf("Usage: ./a.out <file1.txt> <file2.txt> ...\n");
        return FAILURE;
    }

    for(int i=1;i<argc;i++)
    {
        //check argv[i] extn is .txt or not
        char *extn = strrchr(argv[i],'.');
        if(extn != NULL && strcmp(extn, ".txt") == 0)
        {
            printf("%s is valid txt file\n",argv[i]);

            //check the file is present or not
            FILE *fptr = fopen(argv[i],"r");
            if(fptr != NULL)
            {
                //check file is empty or not
                fseek(fptr,0,SEEK_END);
                if(ftell(fptr) > 0)
                {
                    if(insert_fileName(head,argv[i]) == SUCCESS)
                    {
                        printf("%s file is successfuly inserted in flist\n",argv[i]);
                        valid_file_count++;
                    }
                    else
                    {
                        printf("%s file is not inserted in flist\n",argv[i]);
                    } 
                }
                else
                {
                    printf("%s file is empty\n",argv[i]);
                }
                fclose(fptr);
            }
            else
            {
                printf("%s is not present\n",argv[i]);
            }
        }
        else
        {
            printf("%s is not valid txt file\n",argv[i]);
        }
    }
    if (valid_file_count > 0)
    {
        return SUCCESS;
    }
    return FAILURE;
}
int insert_fileName(Flist **head,char *fileName)
{
    //check for duplicate (needs to be impelement)
    Flist *temp = *head;
    while (temp != NULL)
    {
        if (strcmp(temp->arr, fileName) == 0)
        {
            return FAILURE; // Duplicate found, do not insert
        }
        temp = temp->link;
    }
    Flist *newNode = malloc(sizeof(Flist));
    //memory allocation is success or not
    if (newNode == NULL)
    {
        return FAILURE; // Memory allocation failed
    }
    newNode->arr = malloc(strlen(fileName) + 1);

    //memory allocation is success or not
    if (newNode->arr == NULL)
    {
        free(newNode); // Clean up previously allocated node memory
        return FAILURE; 
    }
    //store filename in newNode->arr
    strcpy(newNode->arr, fileName);
    newNode->link = NULL;
    //newNode-->Link = NULL

    if(*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        //insert in SLL
        Flist *curr = *head;
        while (curr->link != NULL)
        {
            curr = curr->link;
        }
        curr->link = newNode;
    }
    return SUCCESS;
}