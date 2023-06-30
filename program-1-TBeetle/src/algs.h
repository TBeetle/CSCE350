#ifndef ALGS_H

#define ALGS_H

#include <algorithm>
#include <queue>
using std::swap;



template<typename T>
void heapsort(std::vector<T>& V){
	int counter = 0;
	std::priority_queue<int, std::vector<T>, std::greater<int>> pq;
	for (int i = 0; i < V.size(); i++) {
		pq.push(V[i]);
	}
	while(!pq.empty()) {
		V[counter++] = pq.top();
		pq.pop();

	}
}



bool are_anagrams(std::string a, std::string b){
    int asize = a.size();
    int bsize = b.size();
 
    if (asize != bsize)
        return false;
    else {
	    sort(a.begin(), a.end());
	    sort(b.begin(), b.end());
    	for (int i = 0; i < asize; i++)
        	if (a[i] != b[i])
            		return false;
}
	return true;
}


#endif
