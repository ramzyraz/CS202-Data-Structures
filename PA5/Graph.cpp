#ifndef GRAPH__CPP
#define GRAPH__CPP
#include <fstream>
#include <climits>
#include "Graph.h"

Graph::Graph(char* file, bool isUnitLength=false)
{
	
string data, data2;
float num;
ifstream file_handle(file);

if (!file_handle.is_open())
{
	cout << "File could not be opened!"<< endl;	
}

else {
	
	while (1){

	    if ((file_handle >> data) && (data != "CONNECTIONS")) {
	    		
	    		if (data == "PEOPLE"){
	    			continue;
	    		}

	    		else{
		    		node *traversal = new node;
		    		traversal->name = data;
		    		traversal->visit = 0;
		    		cities.push_back(traversal);
		    	}
	    	}
	    
	    else {
	    	break;
	    }
	}

	while (file_handle >> data >> data2 >> num){
	    			
		node *temp = new node;
		node *temDestin = new node;

		for (int x = 0; x < cities.size(); x++){
	
			if (data == cities[x]->name){
				temp = cities[x];
			}

			else if (data2 == cities[x]->name){
				temDestin = cities[x];
			}
		}

		edge eeg;
		edge eeg2;
		eeg.Origin = temp;
		eeg.Dest = temDestin;
		eeg2.Origin = temp;
		eeg2.Dest = temDestin;

		if (isUnitLength == true)
		{
			eeg.weight = 1;
			eeg2.weight = 1;
		}
		else
		{
			eeg.weight = num;
			eeg2.weight = num;
		}
		arcs.push_back(eeg);
		arcs.push_back(eeg2);
		temp->edges.push_back(eeg);
		temDestin->edges.push_back(eeg2);
	}

	file_handle.close();
	cout << "\nFile Reading has been Done. DataSet has been parsed." << endl;
}
}

void Graph::display(node* temp)
{
	if(temp->visit)
		return;
	
	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}

bool Graph::Reachable(string start, string dest)
{
	if (start == dest)
	{
		return true;
	}

	node *temp = new node;

	for (int x = 0; x < cities.size(); x++)
	{
		if (start == cities[x]->name)
		{
			cities[x]->visit = 1;
			temp = cities[x];
		}
	}

	if (temp->visit == 1)
	{
		return true;
	}

	for (int x = 0; x < temp->edges.size(); x++){

		node *checker = temp->edges[x].Dest;

		if (checker->visit == 0){
			Reachable(checker->name, dest);
		}
	}
}

vector<node*> Graph::Prims()
{

}

vector<node*> Graph::Kruskal()
{

}

vector<string> Graph::Dijkstra(string start, string dest, float &d)
{
	// Initially Set all values to Max Value and the visited to 0

	for (int i = 0; i < cities.size(); i++)
	{
		cities[i]->distance = INT_MAX; 
		cities[i]->visit = 0;
	}

	node* start_node = new node;
	node* dest_node = new node;

	// Find the starting and destination nodes

	for (int i = 0; i < cities.size(); i++)
	{
		if (start == cities[i]->name)
		{
			start_node = cities[i]; 
			break;
		}
	}

	for (int i = 0; i < cities.size(); i++)
	{
		if (dest == cities[i]->name)
		{
			dest_node = cities[i]; 
			break;
		}
	}

	// Make our starting node into 0
	start_node->distance = 0;

	// Making a vector and copying all contents of the cities into the vector
	vector<node*> v;

	for (int i = 0; i< cities.size(); i++)
	{
		// Insert Start Node warna baaki nodes vector mein push kardo
		if (cities[i]->name == start_node->name)
		{
			v.push_back(start_node);
		}

		else
		{
			v.push_back(cities[i]);
		}
	}

	while (v.size() > 0){

		node *new_node = NULL;
   
   // Finding the Shortest Distance
   int min_val = v[0]->distance; 
   int shortest_index;

   for (int ind = 1; ind < v.size(); ind++) 
     
     if (v[ind]->distance < min_val) {
         
         min_val = v[ind]->distance;
         shortest_index = ind; 
     }

		new_node = v[shortest_index];
		new_node->visit = 1;

		v.erase(v.begin() + shortest_index);

		for (int i = 0; i < new_node->edges.size(); i++){
			
			if (new_node->edges[i].Dest->visit == 0){
				float updated_distance = new_node->edges[i].weight + new_node->distance;

				if (updated_distance < new_node->edges[i].Dest->distance){
					new_node->edges[i].Dest->distance = updated_distance;
					new_node->edges[i].Dest->nex = new_node;
				}
			}
		}
	}

	vector <node*> node_vec;
	vector <string> name_res;
	node *traversal = dest_node;

	while(traversal != start_node)
	{
		node_vec.push_back(traversal);
		traversal = traversal->nex;
	}

	node_vec.push_back(start_node);
	d = dest_node->distance;
	int v_size = node_vec.size() - 1;

	for (int x = 0; x < node_vec.size(); x++){
		name_res.push_back(node_vec[v_size]->name);
		v_size--;
	}

	return name_res;
}

int main()
{
	cout<<"Initialize your graph in main!"<<endl;

	Graph grph ("friends.txt");

	int g_size_cities = grph.cities.size();
	cout << "Size of Cities: "<< g_size_cities << endl;

	int g_size_arc = grph.arcs.size();
	cout << "Size of arcs: " << g_size_arc << endl;
	
	cout << "\nName of Cities" << endl;
	for(int i = 0; i < g_size_cities; i++)
	{
		cout << grph.cities[i]->name << endl;
	}

	cout << "\nName of Arcs" << endl;
	for(int i = 0; i < g_size_arc; i++)
	{
		cout<< grph.arcs[i].Origin->name << "\t\t" << grph.arcs[i].Dest->name << "	" << grph.arcs[i].weight << endl;
	}

	cout << "\nCheck to see if Connected!" << endl;
	string s1 = "George";
	string s2 = "Amanda";

	bool check = grph.Reachable(s1, s2);
	
	if (check == 1)
	{
		cout << s1 << "  is connected to  " << s2 << endl;		
	}
	
	else
	{
		cout << s1 << "  is not connected to  " << s2 << endl;
	}

  cout << endl;
	float distance = 0;
	
	vector<string> final = grph.Dijkstra("Ali", "Mannan", distance);

	for (int i = 0; i < final.size(); i++)
	{
		cout<<final[i] << "   ";
	}

	cout<<distance<<endl;

	// write code for part 6 here
 
   /*Part 6 
	1)
		i- Mannan and Ali are connected
		ii- Mannan and Trump are connected
		iii- Ali and Trump are connected

		Deduction: Every node seems to be connected to every other node in the graph.*/

}

#endif
