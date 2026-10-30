#include "header.h"

int update_db(Flist **head, Hash_t *ht)
{
    char filename[100];
    printf("Enter the fileName: ");
    scanf("%99s", filename);

    int len = strlen(filename);
    if (len < 4 || strcmp(&filename[len - 4], ".txt") != 0)
    {
        printf("Error: Invalid file extension. Please use '.txt' file.\n");
        return FAILURE;
    }

    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error: File %s is not present or cannot be opened.\n", filename);
        return FAILURE;
    }
    char first_char = fgetc(fptr);
    if (first_char == '#')
    {
        printf("Error: \"%s\" is a saved database file! You cannot use it in Update Database.\n", filename);
        fclose(fptr);
        return FAILURE;
    }
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    fclose(fptr);
    if (size <= 0)
    {
        printf("Error: File %s is empty.\n", filename);
        return FAILURE;
    }
    Flist *temp = *head;
    while (temp != NULL)
    {
        if (strcmp(temp->arr, filename) == 0)
        {
            printf("Error: File %s is already updated/present in the database.\n", filename);
            return FAILURE;
        }
        temp = temp->link;
    }
    if (insert_fileName(head, filename) != SUCCESS)
    {
        printf("Error: Failed to insert filename into list.\n");
        return FAILURE;
    }
    printf("%s file is successfully inserted in flist\n", filename);
    Flist *last_node = *head;
    while (last_node->link != NULL)
    {
        last_node = last_node->link;
    }
    
    if (create_db(last_node, ht) == SUCCESS)
    {
        printf("Database successfully updated with file \"%s\"!\n", filename);
        return SUCCESS;
    }

    printf("Error: Database update failed.\n");
    return FAILURE;
}
