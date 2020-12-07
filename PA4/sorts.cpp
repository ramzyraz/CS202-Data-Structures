#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.cpp"

//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
    int max_elem, setter;
    long *arr = &nums[0];
    int length = nums.size();

    for (int i = 1; i < length; i++) { 
    setter = arr[i];
        max_elem = i;

        while (max_elem > 0 && arr [max_elem - 1] > setter)
     {
           arr[max_elem] = arr[max_elem - 1];
           max_elem--;
      }
      arr[max_elem] = setter;
    }
    std::copy(arr, arr + (sizeof(arr)/sizeof(*arr) - 1), std::back_inserter(nums));

    return nums;
}

//=====================================================================================
ListItem<long> *merge_helper(ListItem<long> *temp_head, ListItem<long> *s_elem){

    if (temp_head == NULL){
         return s_elem;
    }

    else if (s_elem == NULL){
        return temp_head;
    }        

    // Merging the Elements
    else if (temp_head->value < s_elem->value) {
        temp_head->next = merge_helper(temp_head->next, s_elem);
        temp_head->next->prev = temp_head;
        return temp_head;
    } 
    else {
        s_elem->next = merge_helper(temp_head, s_elem->next);
        s_elem->next->prev = s_elem;
        return s_elem;
    }
}

ListItem<long>* division(ListItem<long>* temp_head){
  
  if (temp_head == NULL || temp_head->next == NULL){
     return temp_head;
  }
  
    ListItem<long> *f_elem = temp_head;
    ListItem<long> *sn_elem = temp_head;

    // Finding the halfway of the list
    while (f_elem->next != NULL && f_elem->next->next != NULL)
    {
        sn_elem = sn_elem->next;
        f_elem = f_elem->next->next;
    }

    // Breaking the the list into two
    ListItem<long> *t_elem = sn_elem->next;
    sn_elem->next = NULL;
  
   //Divides the List
   ListItem<long> *s_elem = division(t_elem);
   
   //Two Nodes found for Merging
   temp_head = division(temp_head);
   s_elem = division(s_elem);

   ListItem<long> *merged_res = merge_helper(temp_head, s_elem);
   
   return merged_res;
}


vector<long> MergeSort(vector<long> nums)
{
    int length = nums.size();
    List<long> obj_num;

    for (int i = 0; i < length; i++){
        obj_num.insertAtHead(nums[i]);
    }
    
    ListItem<long> *result = division(obj_num.getHead());

    for (int i = 0; i < length; i++){
        nums[i] = result->value;
        result = result->next;
    }

    return nums;
}

//=====================================================================================
long divide_using_first_pivot(long *arr, int low_part, int high_part) 
{ 
    // First Element as pivot 
    long pivot = arr[low_part];

    //Swap pivot with last element
    arr[low_part] = arr[high_part];
    arr[high_part] = pivot;  

    long i = low_part;   
    int j = low_part;
  
    while (j <= high_part){

        if (arr[j] < pivot) 
        {   
            swap(arr[i], arr[j]); 
            i++;
        }
        j++;
    }

    arr[high_part] = arr[i];
    arr[i] = pivot;
  
    return i;
}

long divide_using_last_pivot(long *arr, int low_part, int high_part) 
{ 
    // Last Element as pivot
    long pivot = arr[high_part];  
    long i = low_part;   
    int j = low_part;
  
    while (j <= high_part){

        if (arr[j] < pivot) 
        {   
            swap(arr[i], arr[j]); 
            i++;
        }
        j++;
    }

    arr[high_part] = arr[i];
    arr[i] = pivot;
  
    return i;
}

int find_median(long *array, int low_part, int high_part){

    int middle = (low_part + high_part) / 2;

    if (array[low_part] > array[middle])
        swap( array[middle], array[low_part]);
    if (array[low_part] > array[high_part])
        swap(array[low_part], array[high_part]);
    if (array[middle] > array[high_part])
        swap(array[high_part], array[middle]);

    return middle;
}

long divide_using_median(long *arr, int low_part, int high_part) 
{ 
    // Median Element as pivot
    long pivot_index = find_median(arr, low_part, high_part); 
    long pivot = arr[pivot_index];

    //Swap pivot with last element
    arr[pivot_index] = arr[high_part];
    arr[high_part] = pivot;

    long i = low_part;   
    int j = low_part;
  
    while (j <= high_part){

        if (arr[j] < pivot) 
        {   
            swap(arr[i], arr[j]); 
            i++;
        }
        j++;
    }

    arr[high_part] = arr[i];
    arr[i] = pivot;
  
    return i;
}

void extra_func(long *arr, int low_ind, int high_ind){
    
    if (low_ind < high_ind) 
    {
        //long pivot = divide_using_first_pivot(arr, low_ind, high_ind);
    
        long pivot = divide_using_median(arr, low_ind, high_ind);

        //long pivot = divide_using_last_pivot(arr, low_ind, high_ind);

        extra_func(arr, low_ind, pivot - 1); 
        extra_func(arr, pivot + 1, high_ind); 
    } 

}

vector<long> QuickSortArray(vector<long> nums)
{
    long *arr = &nums[0];
    int length = nums.size();

    int lowest_index = 0;
    int high_index = length - 1;

    extra_func(arr, lowest_index, high_index);

    std::copy(arr, arr + (sizeof(arr)/sizeof(*arr) - 1), std::back_inserter(nums));
  
   return nums;
}

//===================================================================================== 
 ListItem<long>* RandomizePivot(ListItem<long> *temp_traverse, int length)
 {
    srand(time(NULL));
    int i = 0; 
    int n = length;
    ListItem<long> *pivot = temp_traverse;
    
    int k = rand() % n;  
    while(i < k)
    {
        pivot = pivot->next;
        i++;
    }
    
    return pivot;
}

ListItem<long>* partition(ListItem<long>* first, ListItem<long>* last) 
{ 
    if(first == last) {
        return first;
    }
    
    /*int i = 0;
    ListItem<long> *traversal = first;
        
    while(traversal != last)
    {
        traversal = traversal->next;
        i++;
    }
    
    ListItem<long>* pivot = RandomizePivot(first, i, last);*/
    
    ListItem<long>* starter = first;
    ListItem<long>* pivot = last;
    ListItem<long>* current = first;

    while(current != NULL && current != last)
    {
        if(current->value < pivot->value)
        {
            swap(starter->value, current->value);
            starter = starter->next;
        }
        current = current->next;
    }    
    
    swap(pivot->value, starter->value);    
    return starter;
}

void RecursiveQuickCheck(ListItem<long>* first, ListItem<long>* last)
{
    ListItem<long>* p = partition(first, last);
    
   if(first != p){
      RecursiveQuickCheck(first, p->prev);
   }
   
   if(p != last){
     RecursiveQuickCheck(p->next, last);
   }
}

vector<long> QuickSortList(vector<long> nums)
{
    long *arr = &nums[0];
    List<long> obj_num;
    int length = nums.size();

    int lowest_index = 0;
    int high_index = length - 1;

    for (int i = 0; i < length; i++){
        obj_num.insertAtHead(nums[i]);
    }
    
    RecursiveQuickCheck(obj_num.getHead(), obj_num.getTail());
    ListItem<long> *merging_result = obj_num.getHead();

    for (int i = 0; i < length; i++){
        nums[i] = merging_result->value;
        merging_result = merging_result->next;
    }
  
   return nums;
}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
  long *arr = &nums[0];
  int length = nums.size();
  MinHeap *traverse = new MinHeap(length);
    
   for (int i = 0; i < length; i++) { 
          traverse->insertKey(nums[i]);
   }
   
   for (int i = 0; i < length; i++){
       arr[i] = traverse->extractMin();
   }
   
   std::copy(arr, arr + (sizeof(arr)/sizeof(*arr) - 1), std::back_inserter(nums));
  
   return nums;
}

//=====================================================================================
vector<long> QueenOfAllSorts(vector<long> nums)
{
    int length = nums.size();
    int new_Arrsize = 2 * length;
    int min = nums[0];
    long *arr = &nums[0];
    List<long> *inserter = new List<long>[new_Arrsize];
    vector<long> party;

    for (int i = 0 ; i < length ; i++)
    {
        if (min < arr[i]){
            min = arr[i];
        }
    }

    for (int i = 0; i < length; i++)
    {
        arr[i] = arr[i] + min + 5;
        long ind = arr[i];
        inserter[ind].insertAtHead(ind);
    }

    for (int i = 0; i < new_Arrsize; i++)
    {
        ListItem<long> *header = inserter[i].getHead();

        while(header != NULL)
        {   
            party.push_back((header->value) - min - 5);
            header = header->next;
        }
    }
    return party;   
}
#endif