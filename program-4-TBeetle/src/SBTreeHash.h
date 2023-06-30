#ifndef SBTREEHASH_H
#define SBTREEHASH_H

#include <map> //  a self-balancing tree (red-black)
#include <unordered_map> // a hash table
#include <string>
#include <vector>

using std::string;
using std::sort;
using std::vector;
using std::unordered_map;
using std::pair;
using std::map;

struct ana_result {
    bool found = false;
    string s1;
    string s2;
};

//Do there exist two strings that are anagrams of each other ? (use std::sort and a custom Compare)
// See https://en.cppreference.com/w/cpp/algorithm/sort
// lambda functions are fine, even preferable here
ana_result anyAnagramsSorting(vector<string> ss){
	ana_result ar;
	vector < string > anagramSort;
	for (int i = 0; i < ss.size(); i++) {
		string sortedStr = ss[i];
		sort(sortedStr.begin(), sortedStr.end());
		anagramSort.push_back(sortedStr);
	}

	for(int i = 0; i < anagramSort.size(); i++) {
		for(int j = i + 1; j < anagramSort.size(); j++) {
		if(anagramSort[i] == anagramSort[j]) {
			ar.found = true;
			ar.s1 = ss[i];
			ar.s2 = ss[j];
		}
		}
	}
    return ar;
}

//Do there exist two strings that are anagrams of each other ? (use map, self-balancing tree)
ana_result anyAnagramsMap(vector<string> strings){
    ana_result res;
    map < string, string> sMaps; 
    for (int i = 0 ; i < strings.size(); i++) {
	    string s = strings[i];
	    sort(s.begin(), s.end());
	    if(sMaps.find(s) == sMaps.end())
		    sMaps.insert(pair <string, string > (s, strings[i]));
	    else {
		    res.found = true;
		    res.s1 = sMaps.find(s)->second;
		    res.s2 = strings[i];
	    }
    }

    return res;
}

//Do there exist two strings that are anagrams of each other ? (use unordered_map, hash table)
ana_result anyAnagramsHash(vector<string> strings){
    ana_result res;
    unordered_map<string, size_t> sMaps;
    for (int i = 0; i < strings.size(); i++) {
	    string s = strings[i];
	    sort(s.begin(), s.end());
	    auto it = sMaps.find(s);
	    if (it != sMaps.end()) {
		    res.found = true;
		    res.s1 = strings[it->second];
		    res.s2 = strings[i];
		    return res;
	    }
	    else {
		    sMaps[s] = i;
	    }
    }

    return res;
}

#endif //SBTREEHASH_H
