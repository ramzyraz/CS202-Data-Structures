#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <chrono>

Dictionary::Dictionary() {
	wordsTree = NULL;
}

Dictionary::~Dictionary(){
    delete wordsTree;
    wordsTree = NULL;
}

void Dictionary::initialize(string wordsFile) {
    string data;
    wordsTree = new BST<string>;
    int counter = 0;

    ifstream file((wordsFile + ".txt").c_str());
    if (!file.is_open()){
        return;
    }

    while (true){
    	if (file >> data){
    		insertWord(data);
    		counter++;
    	}
    	else {
    		break;
    	}
    }
    file.close();
    cout << "\n" << counter << "    words inserted" << endl;
}

bool Dictionary::deleteWord(string word) {
    if (wordsTree != NULL)
    {
        if (wordsTree->search(word))
        {
            wordsTree->delete_node(word);
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
bool Dictionary::editWord(string oldWord, string newWord) {
	
    if (wordsTree == NULL)
        return false;
    else
    {
         if (wordsTree->search(oldWord)){

            if (deleteWord(oldWord)){
                wordsTree->insert(oldWord, newWord);
                return true;
            }
            else
                return false;
        }
        else {
            return false;
        }
    }
}
bool Dictionary::insertWord(string word) {
    if (wordsTree == NULL){
        return false;
    }
    else {
        wordsTree->insert(word, word);
        if (wordsTree->search(word)){
            return true;
        }
        else {
            return false;
        }
    }
}
node<string>* Dictionary::findWord(string word) {
	clock_t t;
    t = clock();
    // TODO your code here
    auto start = std::chrono::steady_clock::now();
    node<string> *tt = wordsTree->search(word);

    auto end = std::chrono::steady_clock::now();
    auto total_time = std::chrono::duration_cast<chrono::microseconds>(end - start).count();

    t = clock() - t;
    if (tt){
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        cout << "findWord() took " << total_time << " µs to search for " << word << endl;
        return tt;
    }
    else {
        return NULL; // TODO
    }
}

#endif

int main() {
    Dictionary obj;
    obj.initialize("words");

    int choice;

    do{
        cout << "-------------------\n";
        cout << "\nEnter 0 to Exit\n";
        cout << "Enter 1 to Insert\n";
        cout << "Enter 2 to Delete\n";
        cout << "Enter 3 to Search\n";
        cout << "Enter 4 to Edit\n";
        cout << "-------------------\n";
        cout << "\nEnter your Selection : ";
        cin >> choice;

        switch(choice){
        case 1:
            {
                string words;
                cout << "\nEnter word to Insert : ";
                cin >> words;
                if (obj.insertWord(words)){
                    cout << "\nValue has been inserted" << endl;
                }
                else {
                    cout << "\nCannot Insert" << endl;
                }
                break;
            }
            case 2:
            {
                string del_words;
                cout << "\nEnter word to delete : ";
                cin >> del_words;
                if (obj.deleteWord(del_words)){
                    cout << "\nValue has been deleted" << endl;
                }
                else {
                    cout << "\nCannot Delete" << endl;
                }
                break;
            }
            case 3:
            {
                string sear_words;
                cout << "\nEnter word to search : ";
                cin >> sear_words;
                node<string> *searcher = obj.findWord(sear_words);
                if (searcher != NULL){
                    cout << "\nValue : " << searcher->value << " has been found" <<endl;
                }
                else {
                    cout << "\nCannot find" << endl;
                }
                break;
            }
            case 4:
            {
                string edit_words;
                string old_words;
                cout << "\nEnter old Word : ";
                cin >> old_words;
                cout << "\nEnter word to edit : ";
                cin >> edit_words;
                if (obj.editWord(old_words, edit_words)){
                    cout << "\nValue has been edited " << endl;
                }
                else {
                    cout << "\nCannot find" << endl;
                }
                break;
            }
        case 0:
            cout << "\nFunction Ending!" << endl;
            break;
        }
    }
    while (choice != 0);

	return 0;
}
