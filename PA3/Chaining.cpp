#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){
    tableSize = size;
    hashTable = new LinkedList<string>[tableSize];
}
HashC::~HashC(){
}

unsigned long HashC :: hash(string input){
    return madCompression(bitHash(input), tableSize);
}

void HashC::insert(string word){
     unsigned long x = hash(word);
     hashTable[x].insertAtHead(word);
}

ListItem<string>* HashC :: lookup(string word){
    unsigned long y = hash(word);
    return hashTable[y].searchFor(word);
}

void HashC :: deleteWord(string word){
    unsigned long z = hash(word);
    hashTable[z].deleteElement(word);
}

#endif
