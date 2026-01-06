/*  hash.h
 */

#ifndef HASH_H
#define HASH_H

#include <iostream>
using namespace std; 

struct nList
{
   char *word;
   struct nList *next;
};

typedef struct nList *NListPtr;

unsigned Hash(const char *s);
NListPtr Lookup(const char *s);
NListPtr Insert(const char *word);
void WordCount(int index);
void MinMaxWords(int index);
void Search(const char *word);

void PrintHashTable();

#endif  /*  HASH_H  */