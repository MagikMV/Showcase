/* dictionary.cpp
 *
 * CS 121 Bolden
 * Miguel Villanueva  //  vill9577@vandals.uidaho.edu
 * December 1, 2019
 *
 * Eluktronics P65_67HSHP  //  Intel Core i7-7700HQ
 * GCC 5.1.0
 *
 * 
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "hash.h"
using namespace std;

int main()
{
    ifstream infile;
    infile.open("dict0.txt");
    if(!infile)
    {
        cout << "Unable to open input file" << endl;
        exit (-1);
    }
    const int wordLength = 32;
    char word[wordLength];
    while(infile >> word)
    {
        (void)Insert(word);
    }
    infile.close();
    PrintHashTable();
    WordCount(1);
    MinMaxWords(1);
    WordCount(4);
    MinMaxWords(4);
    Search("abbot");
    Search("JeffDunham");
}