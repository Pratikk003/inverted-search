#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define SUCCESS 0
#define FAILURE -1
//fileList Node struct
typedef struct node{
    char *arr;
    struct node *link;

}Flist;
// Sub Node
typedef struct sub_node
{
    int wordCount;
    char *fileName;
    struct sub_node *link;
} Slist;

// Main Node
typedef struct main_node
{
    int fileCount;
    char *word;
    struct main_node *link;
    Slist *sublink;
} Mlist;

// Hash Table
typedef struct hash_table
{
    int index;
    Mlist *link;
} Hash_t;

int read_and_validation(int argc, char *argv[], Flist **head);
int insert_fileName(Flist **head, char *fileName);
int create_db(Flist *f_head, Hash_t *ht);
int display_db(Hash_t *ht);
int search_db(Hash_t *ht, char *word);
int save_db(Hash_t *ht);
int update_db(Flist **head, Hash_t *ht);
#endif