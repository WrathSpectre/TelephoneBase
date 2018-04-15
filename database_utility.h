#ifndef DATABASE_UTILITY_H
#define DATABASE_UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** Data structures ***/

typedef struct Params
{
    char fileName[256]; //trunc if longer then 256
    char seekNumber[10];
}Params;

typedef struct Data
{
    char user[256];
    char phone_number[10];
}Data;

typedef struct _Node Node;
struct _Node
{
    Data data;
    Node *next;
};

/*** User input ***/

void helpArgument(char **);
Params mainArguments(char **);
int isNumberValid(char *);

/*** List management ***/

Node *createNode(const Data);
Node *pushToList(Node *, const Data);
void deleteList(Node *);

/*** File management ***/

Node *parseDatabase(char *, Node *);
Data parseFileLine(char *);

/*** User output ***/

void helpPrompt(char *);
void databaseSearch(Node *, char *);

#endif
