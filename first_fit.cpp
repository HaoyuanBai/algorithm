
#include <iostream>
#include <vector>
#include <algorithm>
#include "ZipTree.h"


//implement in first_fit.cpp
void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	// <key,value> : bin_id, left_space
	ZipTree<int,double> tree;
	int n = items.size(), k = 0;
	for(int i=0; i<n; i++){
		double cur_space = items[i] - 1e-4;
		if( !tree.has_equal_or_larger_value(cur_space) ){
			// a new bin
			k += 1;
			assignment[i] = k;
			tree.insert( k, 1.0-items[i] );
			free_space.push_back(1.0-items[i]);
		}else{
			// find the first bin
			int key = tree.find_first_key(cur_space);
			double left_space = tree.find(key)-cur_space;
			assignment[i] = key;
			
			// remove the old
			tree.remove(key);
			// insert the new
			tree.insert( key, left_space );
			free_space[key-1] = left_space;
		}
	}
}

void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	int n = items.size();
	// sort the item
	std::vector<double> item_sort(n, 0.0);
	for(int i=0; i<n; i++) item_sort[i] = items[i];
	std::sort(item_sort.begin(), item_sort.end(), std::greater<double>());
	
	// call function
	first_fit(item_sort, assignment, free_space);
	
}
