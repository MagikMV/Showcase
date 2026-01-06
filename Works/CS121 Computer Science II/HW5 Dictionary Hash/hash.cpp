/* hash.cpp
 *
 *  Modified Hash table implementation from:
 *  Kernighan & Ritchie, The C Programming Language,
 *     Second Edition, Prentice-Hall, 1988.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include "hash.h"
using namespace std;

const int HASH_TABLE_SIZE = 7;
static NListPtr hashTable[HASH_TABLE_SIZE];

    // Prototypes
static char *Strdup(const char *s);


// Hash
    // Generate hash value for string s
unsigned Hash(const char *s)
{
    unsigned hashVal;
    for(hashVal = 0; *s != '\0'; s++)
    {
        hashVal = *s + 31 * hashVal;
    }

    return  hashVal % HASH_TABLE_SIZE;
}

// Lookup
     // Look for string s in hashTable
NListPtr Lookup(const char *s)
{
    NListPtr np;
    for(np = hashTable[Hash(s)]; np != NULL; np = np->next)
    {
        if(strcmp(s, np->word) == 0)
        {
            return np;    //  found
        }
    }

    return NULL;          //  not found
}

// Insert
    // Put (word) in hashTable
NListPtr Insert(const char *word)
{
    unsigned hashVal;
    NListPtr np;

    if((np = Lookup(word)) == NULL)  // not found
    {
        np = (NListPtr) malloc(sizeof(*np));
        if( np == NULL || (np->word = Strdup(word)) == NULL )
        {
            return NULL;
        }
        hashVal = Hash(word);
        np->next = hashTable[hashVal];
        hashTable[hashVal] = np;
    }
    return np;
}

// PrintHashTable
    // Print hashTable contents
void PrintHashTable()
{
    NListPtr np;

    cout << "Hash table contents:" << endl;
    cout << "--------------------\n" << endl;

    for(int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        np = hashTable[i];
        while(np != NULL)
        {
             cout << setw(3) << i << ":    ";
             cout << np->word;
             cout << endl;
             np = np->next;
        }
    }
}

// WordCount
    // Display the number of words stored in a given bucket
void WordCount(int index)
{
    int count = 0;
    NListPtr np;
    
    np = hashTable[index];
    if(np == NULL)
    {
        cout << "Bucket " << index << " is empty!\n";
    }
    else
    {
        while(np != NULL)
        {
            count += 1;
            np = np->next;
        }
        cout << "Word count in bucket " << index << " is: ";
        cout << count << endl;
    }
    
    
}

// MinMaxWords
    // Display the longest and shortest words in a given bucket
void MinMaxWords(int index)
{
    NListPtr np;
    np = hashTable[index];
    if(np == NULL)
    {
        cout << "Bucket " << index << " is empty!\n";
    }
    else
    {
        char *longestWord = hashTable[index]->word;
        char *shortestWord = hashTable[index]->word;
        if(np->next != NULL)
        {
            np = np->next;
            while(np != NULL)
            {
                if(strlen(np->word) < strlen(shortestWord))
                {
                    shortestWord = np->word;
                }
                if(strlen(np->word) > strlen(longestWord))
                {
                    longestWord = np->word;
                }
                np = np->next;
            }
            cout << "The longest word in bucket " << index << " is ";
            cout << longestWord << endl;
            cout << "The shortest word in bucket " << index << " is ";
            cout << shortestWord << endl;
        }
        else
        {
            cout << "The longest and shortest words in bucket " << index << " are ";
            cout << "the same: " << shortestWord << endl;
        }   
    }
}

// Search
    // Search for a given word within hashTable
    // Additionally track number of probes required to find a given word
void Search(const char *word)
{
    NListPtr np;
    if((np = Lookup(word)) == NULL)
    {
        cout << "The word " << word << " is not in the hash table";
        cout << endl;
    }
    else if((np = Lookup(word)) != NULL)
    {
        cout << "The word " <<  word << " is located in bucket ";
        cout << Hash(word) << ", "; 

        int probeCount = 1;
        NListPtr x;

        x = hashTable[Hash(word)];
        while(strcmp(x->word, word) != 0)
        {
            probeCount += 1;
            x = x->next;
        }
        /*for(x = hashTable[Hash(word)]; x->word != word; x = x->next)
        {
            probeCount += 1;
        }*/
        cout << probeCount << " probes deep!" << endl;
    }
}

// Changed ***
// WordCount
    // Displays the number of words stored in each bucket
/*void WordCount()
{
    NListPtr np;
    for(int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        int count = 0;
        np = hashTable[i];
        if(np == NULL)
        {
            continue;
        }
        while(np != NULL)
        {
            count += 1;
            np = np->next;
        }
        cout << "Word count in bucket " << i << " is: ";
        cout << count << endl;
    }
}*/


// Strdup
    // Make a duplicate copy of string s
static char *Strdup(const char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);  /*  +1 for '\0'  */
    if( p != NULL )
    {
        strcpy(p, s);
    }

    return p;
}
