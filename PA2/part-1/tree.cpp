#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"
//#include <algorithm>
// try to make get_node() and get_file() after tree initialization


Tree::Tree(string data)
{
    // write the rest of the code here
    TreeItem* new_node = new TreeItem();
	new_node->id = 1;
	new_node->latest_data = data;

	root = new_node;
	VCS_node ins(data, 0);
	new_node->container.push_back(ins);
}

Tree::~Tree()
{
}


void Tree::branch(int id)
{
    TreeItem *par = get_node(id);
    int child_size = par->child.size();

    if (child_size <= 9){
        int child_id = id * 10 + child_size + 1;
        TreeItem *par_child = new TreeItem(child_id, par->latest_data);

        VCS_node initial_ver(par->latest_data, 0);
        par_child->container.push_back(initial_ver);
        par->child.push_back(par_child);
    }
}

void Tree::merge(int src_id,int dst_id)
{
    TreeItem *source = get_node(src_id);
    TreeItem *dest = get_node(dst_id);

    string dst = dest->latest_data;
    string combo_concat = dst + source->latest_data;

    VCS_node pusher(combo_concat, dst_id);
    dest->container.push_back(pusher);

    merge_state mer_hist;
    mer_hist.src_id = src_id;
    mer_hist.dst_id = dst_id;
    history.push_back(mer_hist);
}

void Tree::commit(int src_id,string new_data)
{
    TreeItem* com_node = get_node(src_id);
    string combo = com_node->latest_data + new_data;
    com_node->latest_data = combo;

    int timeStamp = com_node->container.size();
    VCS_node com (combo, timeStamp);
    com_node->container.push_back(com);
}

string Tree::get_file(int id, int t_stamp)
{
    TreeItem* getter_node = get_node(id);
    int s = 0;

    if (getter_node != NULL){
        while (s != getter_node->container.size() - 1){
            if (getter_node->id == t_stamp){
                 return getter_node->latest_data;
                 break;
            }
            s++;
        }
    }
    else {
        return NULL;
    }
}

TreeItem* Tree::get_node(int id)
{
    TreeItem *searcher = root;
    int counter = 0;
    int n1, n2, n3, n4;

    n1 = id;
    
    while(n1 != 0)
    {
        counter++;
        n1 /= 10;
    }


    if (counter == 1){
        if (id == 1)
            return root;
    }
    else if (counter == 2){
        n2 = id;

      if (n2 >= 11 && n2 <= 19){
            if (root->child.empty()){
                return NULL;
            }
            else {
                vector<TreeItem*>::iterator it;
                for(it = root->child.begin(); it != root->child.end(); it++){
                    if ((*it)->id == n2){
                        searcher = root->child[(*it)->id];
                        if ((*it)->id == n2){
                          return *it;
                        }
                    }
                }
          }
      }
    }
    else if (counter == 3){
        n3 = id / 10;
        if (id >= 111 && id <= 199){

            if (root->child.empty()){
                return NULL;
            }
            else {
                vector<TreeItem*>::iterator it;
                for(it = root->child.begin(); it != root->child.end(); it++){
                    if ((*it)->id == n3){
                        n2 = (*it)->id;
                        searcher = root->child[n2];
                        if ((*it)->id == n2){
                          return *it;
                        }
                    }
                }
            }
        }
    }
    else if (counter == 4){
        n4 = id/100;
        if (id >= 1111 && id <= 1999){
            if (root->child.empty()){
                return NULL;
            }
            else {
                vector<TreeItem*>::iterator it;
                for(it = root->child.begin(); it != root->child.end(); it++){
                    if ((*it)->id == n4){
                      n3 = (*it)->id;
                        searcher = root->child[n3];
                        if ((*it)->id == n3){
                          return *it;
                        }
                    }
                }
            }
        }
    }
}

vector<merge_state> Tree::merge_history()
{
    return history;
}

void Tree::level_traversal()
{

}


#endif
