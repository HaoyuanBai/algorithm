
#include <vector>

// each file should #include this header file
// implement in next_fit.cpp
void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	static int n = items.size();
	if( n==0 ) return;
	
	int k = 1; double space = 1.0;
	free_space.push_back(space);
	for(int i=0; i<n; i++){
		// a new bin
		if( space < items[i]-1e-4 ){
			k += 1;
			space = 1.0;
			free_space.push_back(1.0);
		}
		
		assignment[i] = k;
		space -= items[i];
		free_space[k-1] = space;
	}
}


