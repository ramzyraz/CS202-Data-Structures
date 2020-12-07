#ifndef QUADRATICPROBING_CPP
#define QUADRATICPROBING_CPP

#include "quadraticProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this
    count = 0;
    hashTable = new block*[tableSize];
    for (long i = 0; i < tableSize; i++){
        hashTable[i] = NULL;
    }
}

HashL::~HashL(){
}

unsigned long HashL :: hash(string value){
    return madCompression(bitHash(value), tableSize);
}

void HashL::resizeTable(){
    long t_size = tableSize;
    tableSize *= 2;
    int j = 0
    block **newArr = new block*[tableSize];
    for (int i = 0; i < tableSize; i++){
            newArr[i] = NULL;
    }
    for (int i = 0; i < t_size; i++){
        if (hashTable[i] != NULL){
         unsigned long x = hash(hashTable[i]->value);
         while (newArr[x] != NULL){
           x = x + (j*j);
           x %= tableSize;
           j++;
          }
         newArr[x] = new block(x , hashTable[i] -> value);
        }
    }
    for (int i = 0 ; i < t_size ; i++)
      {
            delete hashTable[i] ;
      }
    hashTable = newArr;
    newArr = NULL;
}

void HashL::insert(string value){

    float factor = (count * 1.0) / tableSize;
    int j = 0;
    if(factor > 0.25){
        resizeTable();
    }
    
    unsigned long x = hash(value);
    while (hashTable[x] != NULL){
        x = x + (j*j);
        x %= tableSize;
        j++;
    }
    hashTable[x] = new block(x, value);
    count++;
}

void HashL::deleteWord(string value){
    unsigned long y = hash(value);
    int j = 0;
    while(hashTable[y] != NULL) {
        if (hashTable[y]->value == value){
            hashTable[y] = NULL;
            count--;
        }
        y = y + (j*j);
        y %= tableSize;
        j++;
    }
}
block* HashL::lookup(string value){
    unsigned long z = hash(value);
    int j = 0;
    while(hashTable[z] != NULL){
        if (hashTable[z]->value == value){
            return hashTable[z];
        }
        if (count >= tableSize){
            break;
        }
        z = z + (j*j);
        z %= tableSize;
        j++;
    }
    return NULL;
}
#endif
