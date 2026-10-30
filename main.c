#include "header.h"

/* 
 NAME : Pratik Kambire
 PROJECT NAME : Inverted Search
*/

int main(int argc,char *argv[])
{
    Flist *head = NULL;
    Hash_t ht[27];
    //initalize hash table 
    for(int i=0;i<27;i++)
    {
        ht[i].index = i;
        ht[i].link = NULL;
    }
    if(read_and_validation(argc,argv,&head)==SUCCESS)
    {
        int flag = 0;
        printf("read and validation is successful!!!\n\n");
        while(1)
        {
            int choice;
            printf("===== INVERTED SEARCH MENU ====\n");
            printf("1.Create Database\n");
            printf("2.Display Database\n");
            printf("3.search Database\n");
            printf("4.Update Database\n");
            printf("5.Save Database\n");
            printf("6.Exit\n");

            printf("Enter your choice: ");
            scanf("%d",&choice);

            switch(choice)
            {
                case 1:
                    //create_db
                    if (flag == 0)
                    {
                        if (create_db(head, ht) == SUCCESS)
                        {
                            printf("Database created successfully!\n");
                            flag = 1;
                        }
                        else
                        {
                            printf("Database creation failed!\n");
                        }
                    }
                    else
                    {
                        printf("Database is already created!\n");
                    }
                    break;
                case 2:
                    display_db(ht);
                    break;
                case 3:
                    //Search_db
                    {
                      char search_word[100];
                      printf("Enter the word to search: ");
                      scanf("%99s", search_word);
                      search_db(ht, search_word);
                    }
                    break;
                case 4:
                    update_db(&head, ht);
                    break;
                case 5:
                     save_db(ht);
                     break;
                case 6:
                    //6.Exit
                    return 0;
                default:
                    printf("Invalid choice!!!\n");
            }
        }
    }
    else
    {
        printf("Error : read and validation is not completed!!!\n");
    }
    return 0;

}