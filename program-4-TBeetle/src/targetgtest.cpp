#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "gtest/gtest.h"
#include "Graph.h"
#include "SBTreeHash.h"

using namespace std;
using std::string;
using std::vector;
using Graphs::adjMatrix2String;

typedef Graphs::DirectedWeightedGraph<int,double> DWG;
typedef Graphs::DirectedWeightedGraph<string,double> sDWG;
typedef Graphs::DirectedEdge<int,double> DE;
typedef vector<vector<double> > AdjMat;
typedef vector<vector<bool  > > BAdjMat;


sDWG build_8_11(){
	sDWG g;
	g.addVertex("a");
	g.addVertex("b");
	g.addVertex("c");
	g.addVertex("d");
		//g.
	g.addEdge("a","b",1.0);
	g.addEdge("b","d",1.0);
	g.addEdge("d","a",1.0);
	g.addEdge("d","c",1.0);
	return g;
}

TEST(ex_8_11_Warshalls, ex_8_11){
	sDWG g = build_8_11();
	BAdjMat R0=g.getBooleanAdjacencyMatrix();
	string s = adjMatrix2String(g.getVertices(),R0);
	stringstream ss;
	ss<<"Ex_8_11_Warshalls message:\n";
	ss<<s;
	BAdjMat Rf = g.getTransitiveClosure();
	string sRf = adjMatrix2String(g.getVertices(),Rf);
	ss <<"\nTransitive Closure=\n"<<sRf;
	
	BAdjMat gtRf;//gt == ground truth
	vector<string> vs = g.getVertices();
	for(string v:vs){
		vector<bool> trues;
		for(string v:vs){
			trues.push_back(true);
		}
		gtRf.push_back(trues);
	}
	for(int i =0;i<gtRf.size();++i){
		gtRf[2][i]=false;
	}
	string sgtRf = adjMatrix2String(g.getVertices(),gtRf);
	ss <<"\nTarget Transitive Closure=\n"<<sgtRf;
	bool match = true;
	ASSERT_EQ(gtRf.size(),Rf.size())
	 	<<"Your 1st dimension of the Adj.Matrix doesn't match target";
	for(int i = 0;i<gtRf.size();++i){
		ASSERT_EQ(gtRf[i].size(),Rf[i].size()) 
				<<"Your 2nd dimension of the Adj.Matrix doesn't match target (on row "<<i<<")";
		for(int j=0;j<gtRf[i].size();++j){
			if(gtRf[i][j]!=Rf[i][j]) match = false;
			ASSERT_TRUE(match)<<"Your result doesn't match target at "<<"["<<i<<","<<j<<"]\n"<<ss.str();
		}
	}
	
}

sDWG build_Warshalls_ex_1(){
	sDWG g;
	g.addVertex("a");
	g.addVertex("b");
	g.addVertex("c");
	g.addVertex("d");
	g.addVertex("e");
	g.addEdge("b","a",1.0);
	g.addEdge("b","c",1.0);
	g.addEdge("d","b",1.0);
	g.addEdge("d","c",1.0);
	g.addEdge("e","a",1.0);
	g.addEdge("e","d",1.0);
	return g;
}

TEST(run_Slides_War_1, run_slides_War_1){
	sDWG g=build_Warshalls_ex_1();
	BAdjMat R0=g.getBooleanAdjacencyMatrix();
	stringstream ss;
	string s = adjMatrix2String(g.getVertices(),R0);
	ss<<s;
	BAdjMat Rf = g.getTransitiveClosure();
	string sRf = adjMatrix2String(g.getVertices(),Rf);
	ss <<"\nTransitive Closure=\n"<<sRf;

	BAdjMat gtRf;//gt == ground truth
	vector<string> vs = g.getVertices();
	for(string v:vs){
		vector<bool> falses;
		for(string v:vs){
			falses.push_back(false);
		}
		gtRf.push_back(falses);
	}
	gtRf[1][0] = true;
	gtRf[1][2] = true;
	gtRf[3][0] = true;
	gtRf[3][1] = true;
	gtRf[3][2] = true;
	gtRf[4][0] = true;
	gtRf[4][1] = true;
	gtRf[4][2] = true;
	gtRf[4][3] = true;
	string sgtRf = adjMatrix2String(g.getVertices(),gtRf);
	ss <<"\nTarget Transitive Closure=\n"<<sgtRf;
	bool match = true;
	ASSERT_EQ(gtRf.size(),Rf.size())
	 	<<"Your 1st dimension of the Adj.Matrix doesn't match target";
	for(int i = 0;i<gtRf.size();++i){
		ASSERT_EQ(gtRf[i].size(),Rf[i].size()) 
				<<"Your 2nd dimension of the Adj.Matrix doesn't match target (on row "<<i<<")";
		for(int j=0;j<gtRf[i].size();++j){
			if(gtRf[i][j]!=Rf[i][j]) match = false;
			ASSERT_TRUE(match)<<"Your result doesn't match target at "<<"["<<i<<","<<j<<"]\n"<<ss.str();
		}
	}
}


//this one is with numbers
sDWG build_Floyd_Slide_1(){
	sDWG g;
	g.addVertex("a");
	g.addVertex("b");
	g.addVertex("c");
	g.addVertex("d");
	g.addVertex("e");
	g.addEdge("b","a",3.0);
	g.addEdge("b","c",2.0);
	g.addEdge("d","b",7.0);
	g.addEdge("d","c",6.0);
	g.addEdge("e","a",1.0);
	g.addEdge("e","d",2.0);
	return g;
}

bool doubleEquals(double a,double b){
	if( abs(a-b)<1e-10 ) return true;
	else return false;
}

TEST(test_Floyd_slide_1,run_Floyd_1){
	sDWG g = build_Floyd_Slide_1();
	AdjMat AM = g.getAdjacencyMatrix();
	string s = adjMatrix2String(g.getVertices(),AM);
	stringstream ss;
	ss<<s;
	AdjMat Df = g.getAllPairsShortestPaths();
	string sDf = adjMatrix2String(g.getVertices(),Df);
	ss <<"\nAll-Pairs ShortestPaths\n"<<sDf<<endl;

	AdjMat gtDf;//gt == ground truth
	vector<string> vs = g.getVertices();
	for(string v:vs){
		vector<double> infs;
		for(string v:vs){
			infs.push_back(std::numeric_limits<double>::infinity());
		}
		gtDf.push_back(infs);
	}
	for(int i=0;i<vs.size();++i) 
		gtDf[i][i] = 0.0;

	gtDf[1][0] = 3.0;
	gtDf[1][2] = 2.0;
	gtDf[3][0] = 10.0;
	gtDf[3][1] = 7.0;
	gtDf[3][2] = 6.0;
	gtDf[4][0] = 1.0;
	gtDf[4][1] = 9.0;
	gtDf[4][2] = 8.0;
	gtDf[4][3] = 2.0;

	string sgtDf = adjMatrix2String(g.getVertices(),gtDf);
	ss <<"\nTarget All-Pairs ShortestPaths=\n"<<sgtDf;
	bool match = true;
	ASSERT_EQ(gtDf.size(),Df.size())
	 	<<"Your 1st dimension of the Adj.Matrix doesn't match target";
	for(int i = 0;i<gtDf.size();++i){
		ASSERT_EQ(gtDf[i].size(),Df[i].size()) 
				<<"Your 2nd dimension of the Adj.Matrix doesn't match target (on row "<<i<<")";
		for(int j=0;j<gtDf[i].size();++j){
			if(gtDf[i][j]!=Df[i][j]) match = false;
			ASSERT_TRUE(match)<<"Your result doesn't match target at "<<"["<<i<<","<<j<<"]\n"<<ss.str();
		}
	}
}

sDWG build_floyd_slide_2(){
	sDWG g;
	g.addVertex("a");
	g.addVertex("b");
	g.addVertex("c");
	g.addVertex("d");
	g.addEdge("a","c",3.0);
	g.addEdge("b","a",2.0);
	g.addEdge("c","b",7.0);
	g.addEdge("c","d",1.0);
	g.addEdge("d","a",6.0);
	return g;
}

TEST(test_Floyd_slide_2,run_Floyd_2){
	sDWG g = build_floyd_slide_2();
	AdjMat AM = g.getAdjacencyMatrix();
	string s = adjMatrix2String(g.getVertices(),AM);
	stringstream ss;
	ss<<s;
	AdjMat Df = g.getAllPairsShortestPaths();
	string sDf = adjMatrix2String(g.getVertices(),Df);
	ss <<"\nAll-Pairs ShortestPaths\n"<<sDf<<endl;

	AdjMat gtDf;//gt == ground truth
	vector<string> vs = g.getVertices();
	for(string v:vs){
		vector<double> zeroes;
		for(string v:vs){
			zeroes.push_back(0.0);
		}
		gtDf.push_back(zeroes);
	}
	gtDf[0][1] = 10.0;
	gtDf[0][2] = 3.0;
	gtDf[0][3] = 4.0;
	gtDf[1][0] = 2.0;
	gtDf[1][0] = 2.0;
	gtDf[1][2] = 5.0;
	gtDf[1][3] = 6.0;
	gtDf[2][0] = 7.0;
	gtDf[2][1] = 7.0;
	gtDf[2][3] = 1.0;
	gtDf[3][0] = 6.0;
	gtDf[3][1] = 16.0;
	gtDf[3][2] = 9.0;
	string sgtDf = adjMatrix2String(g.getVertices(),gtDf);
	ss <<"\nTarget All-Pairs ShortestPaths=\n"<<sgtDf;
	bool match = true;
	ASSERT_EQ(gtDf.size(),Df.size())
	 	<<"Your 1st dimension of the Adj.Matrix doesn't match target";
	for(int i = 0;i<gtDf.size();++i){
		ASSERT_EQ(gtDf[i].size(),Df[i].size()) 
				<<"Your 2nd dimension of the Adj.Matrix doesn't match target (on row "<<i<<")";
		for(int j=0;j<gtDf[i].size();++j){
			if(gtDf[i][j]!=Df[i][j]) match = false;
			ASSERT_TRUE(match)<<"Your result doesn't match target at "<<"["<<i<<","<<j<<"]\n"<<ss.str();
		}
	}
}


/*********************************************************************************************
 *
 *
 *            ANAGRAM TESTS
 *
 *********************************************************************************************/

struct ana_problem{
	ana_result result;
	std::vector<std::string> input;
};


const int ana_prob_size = 5000; //5000 is short default;
//const int ana_prob_size = 500000; //500000 is long default;


void gen_string(string& char_set, vector<string>& strings, vector<int> active_splits, vector<int> pos_split_pos, int ct){
	int len = char_set.length();
	vector<int> used_splits;
	while(strings.size()<ct && pos_split_pos.size() != used_splits.size() ){
		vector<int> unused_splits;
		for(int sp : pos_split_pos){
			bool is_used = false;
			for(int i =0; i<used_splits.size();++i)
				if(used_splits[i] == sp) is_used = true;
			if(!is_used) unused_splits.push_back(sp);
		}
		int pos_split_ind = rand()%unused_splits.size();

		int curr_split = unused_splits[pos_split_ind];
		active_splits.push_back(curr_split);


		if(active_splits.size() == len ) {
			string s = "";
			for (int i = 0; i < len - 1; ++i) {
				while(s.length() < active_splits[i]) {
					s = s + char_set[i];
				}
			}
			while (s.length() < len) s = s + char_set[len - 1];
			strings.push_back(s);
			return;
		}
		else {
			vector<int> sub_splits;
			for (int s:pos_split_pos)
				if (s >= curr_split) sub_splits.push_back(s);
			gen_string(char_set,strings,active_splits,sub_splits,ct);

		}

		used_splits.push_back(curr_split);

		active_splits.pop_back();


	}
}


vector<string> gen_unique_strings(string char_set, int ct){
	vector<string> strings;
	vector<int> pos_split_pos;
	for(int i = 0;i<char_set.length()+1;++i){
		pos_split_pos.push_back(i);
	}
	gen_string(char_set,strings,vector<int>(),pos_split_pos, ct);
	return strings;
}

ana_problem gen_ana_prob(){
	vector< vector< unsigned> > sample_counts;
	vector<string> ss = gen_unique_strings("abcdefghijklmnopq",ana_prob_size);
	for(string& s : ss)
		random_shuffle(s.begin(),s.end());




	ana_problem prob;
	prob.result.found = false;
	prob.input = ss;

	if(rand()%2){
		int is = prob.input.size();
		int i1 = rand()%is;
		int i2 = (rand()%(is -1) +i1 )%is;

		prob.input[i2] = prob.input[i1];
		random_shuffle(prob.input[i2].begin(),prob.input[i2].end() );
		prob.result.found = true;

		prob.result.s1 = prob.input[i1];
		prob.result.s2 = prob.input[i2];
	}

	return prob;
}



const int ana_prob_ct =20;
vector< ana_problem> gen_ana_problems(){
	static vector< ana_problem> probs;
	if(probs.size()==0){
		for(int i = 0;i<ana_prob_ct;++i){
			probs.push_back(gen_ana_prob());
		}
	}
	return probs;
}

TEST(test_anyAnagrams,gen_anyAnagrams_TIME){
	srand(time(NULL));
	vector<string> ss = gen_unique_strings("abcdefghijklmnopq",ana_prob_size);

	gen_ana_problems();

}

TEST(test_anyAnagrams,test_anyAnagrams_sorting){
	vector<ana_problem> aps = gen_ana_problems();

	for(ana_problem ap : aps){
		ana_result alg_res = anyAnagramsSorting(ap.input);
		ASSERT_TRUE(alg_res.found == ap.result.found) << "anyAnagramsSorting failed a test";
		if(ap.result.found){
			ASSERT_TRUE(ap.result.s1==alg_res.s1 && ap.result.s2==alg_res.s2
		              ||ap.result.s1==alg_res.s2 && ap.result.s2==alg_res.s1) << "didn't find correct anagrams";
		}
	}
}


TEST(test_anyAnagrams,test_anyAnagrams_SBTree){
	vector<ana_problem> aps = gen_ana_problems();

	for(ana_problem ap : aps){
		ana_result alg_res = anyAnagramsMap(ap.input);
		ASSERT_TRUE(alg_res.found == ap.result.found) << "anyAnagramsSorting failed a test";
		if(ap.result.found){
			ASSERT_TRUE(ap.result.s1==alg_res.s1 && ap.result.s2==alg_res.s2
			          ||ap.result.s1==alg_res.s2 && ap.result.s2==alg_res.s1) << "didn't find correct anagrams";
		}
	}
}

TEST(test_anyAnagrams,test_anyAnagrams_Hash){
	vector<ana_problem> aps = gen_ana_problems();

	for(ana_problem ap : aps){
		ana_result alg_res = anyAnagramsHash(ap.input);
		ASSERT_TRUE(alg_res.found == ap.result.found) << "anyAnagramsSorting failed a test";
		if(ap.result.found){
			ASSERT_TRUE(ap.result.s1==alg_res.s1 && ap.result.s2==alg_res.s2
                      ||ap.result.s1==alg_res.s2 && ap.result.s2==alg_res.s1) << "didn't find correct anagrams";
		}
	}
}





