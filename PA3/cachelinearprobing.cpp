#ifndef CACHELINEARPROBING_CPP
#define CACHELINEARPROBING_CPP

#include "cachelinearprobing.h"
#include "hashfunctions.cpp"
#include <string>
#include <sstream>


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

void HashL::LFU(){
    int first; 
    int second;

    for (int i = 0; i < tableSize; i++){
        if (hashTable[i] != NULL){
            first = hashTable[i]->key;
            second = i;
            for (int j = i+1; i < tableSize; j++)
            {
                if (hashTable[i] != NULL){
                    if (first > hashTable[i]->key){
                        first = hashTable[i]->key;
                        second = j;
                    }
                }
            }
        }
    }

    hashTable[second] = NULL;
    delete hashTable[second];
    count--;
}

void HashL::insert(int keys, string value){

    if(count == tableSize){
        LFU();
    }
    
    unsigned long x = hash(value);
    while (hashTable[x] != NULL){
        x++;
        x %= tableSize;
    }
    hashTable[x] = new block(x, value);
    count++;
}

block* HashL::lookup(int keys){
    string read_keys;
    stringstream ss;
    ss << keys
    read_keys = ss.str();

    unsigned long z = hash(read_keys);

    while(hashTable[z] != NULL){
        if (hashTable[z]->key == keys){
            return hashTable[z];
        }
        if (count >= tableSize){
            break;
        }
        z++;
        z %= tableSize;
    }
    return NULL;
}
#endif
