#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD(){
    tableSize = 10000; // you cant change this
    count = 0;
    hashTable = new block*[tableSize];
    for (long i = 0; i < tableSize; i++){
        hashTable[i] = NULL;
    }
}

HashD::~HashD(){
}

unsigned long HashD::hash1(string value)
{
	return madCompression(bitHash(value), tableSize);
}

unsigned long HashD::hash2(string value)
{
	return 17 - (bitHash(value) % 17);
}

void HashD::resizeTable(){

	long t_Size = tableSize;
	tableSize *= 7;
	block **newArr = new block *[tableSize];
	for(int i = 0 ; i < tableSize ; i++)
	{
	    newArr[i] = NULL;
	}

	for(int i = 0; i < t_Size ; i++)
	{
		if(hashTable[i] != NULL)
		{
		  int counter = 1;
      	  unsigned long x = hash1(hashTable[i]->value);
		  unsigned long y = hash2(hashTable[i]->value);
				
			while(newArr[x] != NULL)	
			{
			 x = divCompression(x + counter * y, tableSize);
		     counter++;
			}
			newArr[x] = new block(x , hashTable[i]->value);
		}
	}
	for (int i = 0 ; i < t_Size ; i++)
	{
	  delete hashTable[i] ;
	}
	hashTable = newArr ;
	newArr = NULL ;
}	

void HashD::insert(string value){
	float factor = (count * 1.0) / tableSize;

    if(factor > 0.2){
        resizeTable();
    }

	int counter = 1;
    unsigned long x = hash1(value);
	unsigned long y = hash2(value);
	    
	 while (hashTable[x] != NULL)
	{
		x = divCompression(x + counter * y, tableSize);
		counter++;                                   
	} 

	hashTable[x] = new block(x, value);
    count++; 
}

void HashD::deleteWord(string value){

	unsigned long x = hash1(value);
	int counter = 1;
	unsigned long y = hash2(value);
	    
	 while (hashTable[x] != NULL)
	{
	        if (hashTable[x]->value == value){
	            hashTable[x] = NULL;
	            count--;
	        }
	    x = divCompression(x + counter * y, tableSize);
	    counter++;
	    }
}

block* HashD::lookup(string value){

	unsigned long x = hash1(value);
	int counter = 1;
	unsigned long y = hash2(value);
	 while (hashTable[x] != NULL)
	{
	      if (hashTable[x]->value == value){
	          return hashTable[x];
	      } 
	    x = divCompression(x + counter * y, tableSize);
	    counter++;
	}
      
  	return NULL;
}

#endif