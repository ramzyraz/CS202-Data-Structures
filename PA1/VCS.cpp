#ifndef VCS_CPP
#define VCS_CPP
#include "VCS.h"
#include <iostream>
#include <cstdio>
#include <sstream>

/*
I'm using 2 stack containers for VCS. The advantage of this is that a stack follows a LIFO structure so the topmost element will be the
latest version of the file. This makes it easier to perform undo and redo.
*/

//base constructor, init
VCS::VCS(string fname)
{
	curr_size=0;
	filename = fname;
}

//destructor
VCS::~VCS()
{
    VCS_node cpy;
    while(container1.isEmpty() && container2.isEmpty()){
        cpy = container1.pop();
        cpy = container2.pop();
    }
}


//time to commit
void VCS::commit(string msg)
{
    VCS_node com (msg, curr_size);
    container1.push(com);

    string out_string;
    stringstream ss;
    ss << com.time_stamp;
    out_string = ss.str();

    string Newfilename = filename + out_string + ".txt";
    string data;
    ifstream File;
    File.open((filename + ".txt").c_str());
    if (!File.is_open()){
        return;
    }

    ofstream File2;
    File2.open(Newfilename.c_str());
    if (!File2.is_open()){
        return;
    }

    while (true){
    	if (File >> data){
    		File2 << data;
    	}
    	else {
    		break;
    	}    
    }

    curr_size++;
    File.close();
    File2.close();
}

//print status of every version
void VCS::status()
{
    VCS_node checker;
    for (int looper = 0; looper < 5; looper++){
        checker = container1.top();
        cout << "Message : " << checker.message << "\nVersion Number: " << checker.time_stamp << "\n\n";
        container2.push(container1.pop());
    }
    container1.push(checker);
}

//goes one step back
string VCS::undo()
{
    string val, data;
    VCS_node retriever;
    container2.push(container1.pop());
    retriever = container1.top();

    string undoData;
    stringstream ss;
    ss << retriever.time_stamp;
    undoData = ss.str();

    string newFile = filename + undoData + ".txt";
    ifstream fileHandle(newFile.c_str());
    if (!fileHandle.is_open()){
        return NULL;
    }

    ofstream origFile((filename + ".txt").c_str());
    if (!origFile.is_open()){
        return NULL;
    }

    while (true){
    	if (fileHandle >> data){
    		origFile << data;
	        val = data;
    	}
    	else {
    		break;
    	}    
    }
    return val;
}

//one step ahead
string VCS::redo()
{
    string val, data;
    VCS_node retriever;
    container1.push(container2.pop());
    retriever = container1.top();

    string redoData;
    stringstream ss;
    ss << retriever.time_stamp;
    redoData = ss.str();

    string newFile = filename + redoData + ".txt";
    ifstream fileHandle(newFile.c_str());
    if (!fileHandle.is_open()){
        return NULL;
    }

    ofstream origFile((filename + ".txt").c_str());
    if (!origFile.is_open()){
        return NULL;
    }

    while (true){
    	if (fileHandle >> data){
    		origFile << data;
	        val = data;
    	}
    	else {
    		break;
    	}    
    }
    return val;
}

//goes t_stamp step back or ahead
string VCS::revert(int t_stamp)
{
    string data;

    while (true){
        VCS_node reverter = container1.top();
        int chek = reverter.time_stamp;

        if (chek > t_stamp){
            data = undo();
        }
        else if (chek < t_stamp){
            data = redo();
        }
        else {
            ofstream origFile((filename + ".txt").c_str());
            origFile << data;
            return data;
            break;
        }
    }
}

#endif
