//include any header files as required
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "cachelinearprobing.h"

using namespace std;

int main(){

	HashL hash_obj;
	string filename, read_data, read_data2, words1, words2;
	int read_codes, read_dict;
	int counter = 0;
	cout << "\nEnter the name of your file you want to read : ";
	cin >> filename;
	fstream file((filename + ".txt").c_str());
	ifstream file2("dictionary.txt");

	auto start = std::chrono::steady_clock::now();
	while (file >> read_codes) {

		count++;
		stringstream ss;
		ss << read_codes;
    	read_data = ss.str();

    	block *hash_cache = hash_obj.lookup(read_codes);

    	if(hash_cache == NULL){

			while (file2 >> read_dict >> words2){
	    	
	    		if(counter == read_codes)
	            {
	    	      hash_obj.insert(read_dict, read_data);
	    	      cout << read_dict << " " << read_data << endl;
	    	      counter = 0;
	    	      break;
	            }
	            counter++;
	    	}
	    	file2.close();
		    file >> read_data2;

	        	auto end = std::chrono::steady_clock::now();
	        	cout<< "\nFinal Result = "<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << endl;
	        	return 0;
	        }
    }

	return 0;
}