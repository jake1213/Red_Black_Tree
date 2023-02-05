#ifndef _MERGE_VECTOR_CPP
#define _MERGE_VECTOR_CPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "../include/NodeInfo.h"
//#include "../src/NodeInfo.cpp"

using std::cout; using std::endl;
using std::string; using std::vector;

void printVector(vector<char *> vec) {
    for (auto &i : vec) {
        cout << i << " ";
    }
    cout << endl;

	// for(int i = 0; i < vec.size(); i+=2){
	// 	cout << vec.at(i) << " ";
	// }
	// cout << endl;
}

bool compare(string x, string y){
	//if same string return true
	if(x == y){
		return true;
	}

	//find index where x and y are not equal
	unsigned int i = 0;
	while(x.at(i) == y.at(i) && i < x.size() && i < y.size()){
		i++;
	}

	//return if x is first alphabetically returns true else returns false
	return (int(x.at(i)) < int(y.at(i)));	
}

//Complete Merge
void merge(vector<char *> *vec, int low, int high){
	//Intialize temp vectors
	vector<char *> left_vec;
	vector<char *> right_vec;

	//Find middle 
	int mid = (high + low)/2;
	int vec1_size = mid - low + 1; 
	int vec2_size = high - mid;

	//Populate left temp vector
	for(int i = 0; i < vec1_size; i++){
		left_vec.push_back(vec->at(low+i));
	}

	//Populate left temp vector
	for(int i = 0; i < vec2_size; i++){
		right_vec.push_back(vec->at(mid + 1 + i));
	}

	//Create iterators to use later for indexing vectors
	int right_index = 0;
	int left_index = 0;
	int vec_index = low;

	//While loop to look at 2 temp array and translate/sort into vec
	while(left_index < vec1_size && right_index < vec2_size){

		//Check for which one comes first alphabetically and place it in vec
		if(compare(left_vec.at(left_index), right_vec.at(right_index))){
			vec->at(vec_index) = left_vec.at(left_index);
			left_index++;
		}else{
			vec->at(vec_index) = right_vec.at(right_index);
			right_index++;	
		}

		//Incriment vec_index so that new values will be placed in correct spot in vec
		vec_index++;
	}

	//Make sure all remaining values are out of vec2
	while(right_index < vec2_size){
		vec->at(vec_index) = right_vec.at(right_index);

		//Incriment right_index and vec_index
		right_index++;
		vec_index++;
	}

	//Make sure all remaining values are out of vec1
	while(left_index < vec1_size){
		vec->at(vec_index) = left_vec.at(left_index);

		//Incriment left_index and vec_index
		left_index++;
		vec_index++;
	}
}

//Complte mergeSort
void mergeSort(vector<char *> *vec, int low, int high){
	//Base case
	if(low >= high){
		return; 
	}

	//middle int for function calls
	int middle = (low + high)/2;

	//Function calls
	mergeSort(vec, low, middle);
	mergeSort(vec, middle+1, high);
	merge(vec, low, high);
}

int main(int argc, char**argv){
	vector<char *> list;
	for (int i = 0; i < argc; i++)
	{
		list.push_back(argv[i]);
	}

	list.erase(list.begin());
	mergeSort(&list, 0, list.size()-1);
	printVector(list);

	return 0;
}
#endif
