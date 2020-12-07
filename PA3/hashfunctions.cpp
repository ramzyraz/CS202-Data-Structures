#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 9){
	unsigned long poly_sum = 0.0;
	int str_length = value.length();

	for(int i = value.length() - 1 ; i >= 0; i--)
		poly_sum += poly_sum * a + (unsigned long)value[i];
	}
	return poly_sum;
}
//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
	unsigned long bit_val = 0;
	int val_length = value.length();

	for (int  i = 0; i < val_length; i++) {
		bit_val ^= (bit_val << 5) + (bit_val >> 2) + (unsigned long)value[i];
	}
	return bit_val;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
	return (hash % size);
}
// multiplication addition and division compression.
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
	return (m*hash + a) % size;
}
#endif
// you may write your own program to test these functions.
