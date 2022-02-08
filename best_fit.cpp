#include <iostream>
#include <vector>
#include <algorithm>
#include "ZipTree.h"


// implement in best_fit.cpp
void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	// <key, value> : <left_space, bin_id>, bin_id
	ZipTree<std::pair<double,int>, int> tree;
    int n = items.size(), k=0;
	for(int i=0; i<n; i++){
		double cur_space = items[i] - 1e-4;
		if( !tree.has_equal_or_larger_key( std::make_pair(cur_space,-1) ) ){
			// a new bin
			k += 1;
			assignment[i] = k;
			tree.insert( std::make_pair(1.0-items[i],k), k );
			free_space.push_back(1.0-items[i]);
		}else{
			// find the best fit bin
			std::pair<double,int> key = tree.find_min_key( std::make_pair(cur_space,-1) );
			double left_space = key.first-items[i];
			int ik = key.second;
			assignment[i] = ik;
			
			// remove the old
			tree.remove(key);
			// insert the new
			tree.insert( std::make_pair(left_space,ik), ik );
			free_space[ik-1] = left_space;
		}
	}
}

void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	int n = items.size();
	// sort the item
	std::vector<double> item_sort(n, 0.0);
	for(int i=0; i<n; i++) item_sort[i] = items[i];
	std::sort(item_sort.begin(), item_sort.end(), std::greater<double>());
	
	// call function
	best_fit(item_sort, assignment, free_space);
}
