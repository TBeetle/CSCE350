#include <iostream>
#include <string>
#include <time.h>

#include "gtest/gtest.h"
#include "algs.h"
#include "tree.h"

using namespace std;
using std::string;


TEST(heapsort_rand,heapsort_test){
	srand(time(0));
	const int arr_sz = 20;
	for(int i = 0;i<300;++i){
		vector<int> A;
		vector<int> A_lib_sorted;
		for(int j=0;j<arr_sz;++j){
			A.push_back(rand()%15);
		}
		vector<int> orig_A;


		for(int j = 0; j<arr_sz;++j){
			orig_A.push_back(A[j]);
			A_lib_sorted.push_back(A[j]);
		}

		std::sort(A_lib_sorted.begin(), A_lib_sorted.end());

		ASSERT_NO_THROW(heapsort(A) )<<"Your code threw an exception (probably segmentation fault)";

		string arr_cmp;
		arr_cmp+="\nA ( yours):[";
		for(int j = 0;j<arr_sz;++j) arr_cmp+=to_string(A[j])+",";
		arr_cmp+="]\n";
		arr_cmp+="\nA (target):[";
		for(int j = 0;j<arr_sz;++j) arr_cmp+=to_string(A_lib_sorted[j])+",";
		arr_cmp+="]\n";
		arr_cmp+="\nA ( orig.):[";
		for(int j = 0;j<arr_sz;++j) arr_cmp+=to_string(orig_A[j])+",";
		arr_cmp+="]\n";

		//std::cout<<arr_cmp<<std::endl;
		for(int j = 0;j<arr_sz;++j){
			ASSERT_EQ(A[j],A_lib_sorted[j]) << "Your code doesn't properly sort:\n"<<arr_cmp;
		}

	}	
}

struct ana_sample{
	std::string a;
	std::string b;
	bool are_anagrams;
};

ana_sample* gen_ana_sample(){
	int len = 6 + rand()%2; // bug here?...
	ana_sample* s = new ana_sample;
	std::string  temp;
	for(int i = 0;i<len;++i)
		temp+=(char)((int)'A' + rand()%26) ;
	s->a=temp;
	s->are_anagrams = (rand() % 2) < 1;
	
	s->b=s->a;
	std::random_shuffle(s->b.begin(),s->b.end());
	if(!s->are_anagrams) {
		int corruption = rand()%1;
		if(corruption ==0){//change letter
			int ind = rand()%len;
			char orig = s->b[ind];
			char diff_char = 
			    (char)( ( (int)s->b[ind]-(int)'A'+rand()%(25-1)+1 )//+ 1-25
			    %26+(int)'A');
			s->b = s->b.substr(0,ind)+diff_char+s->b.substr(ind+1,s->b.length() );

		}
	}
	return s;
}



TEST(ana_checker,ana_checker){
	srand(time(NULL));
	for (int i =0;i<100;++i){
		ana_sample* samp = gen_ana_sample();
		bool res = are_anagrams(samp->a,samp->b);
		std::string msg = "For strings\n" +
			samp->a +",\n" +
			samp->b + "\n"  +
			" your code returned " + (res?"true":"false")+ " when "+
			(samp->are_anagrams?"true":"false")+" was expected\n";
		ASSERT_TRUE(res==samp->are_anagrams)<<msg;
		delete samp;
	}
}

template<typename T>
BST_Node<T>* gen_tree(vector<T> vals){
    if(vals.size() == 0) return NULL;

    BST_Node<T>* root = new BST_Node<T> (vals[0]);
    for(int i = 1; i<vals.size();++i)
        root->insert(vals[i]);

    return root;
};

//obviously, size had better be smaller than max-min+1
template<typename T>
vector<T> gen_no_duplicate_vec(int size, int min, int max){
    vector<T> vec;

    int rand_range = max-min+1;

    for(int i=0;i<size;++i){
        T r = T(rand()%rand_range+min);//values all integral
        bool dup= false;
        for(int j=0;j<i;++j){
            if(r==vec[j]) dup= true;
        }

        if(dup) --i;
        else vec.push_back(r);
    }

    return vec;
}

template<typename T>
BST_Node<T>* gen_count_sample(int n, int max){
    vector<T> vec = gen_no_duplicate_vec<T>(n,0,max);
    return gen_tree<T>(vec);
};

template<typename T>
BST_Node<T>* gen_dup_sample(int n, int max){
    vector<T> vec = gen_no_duplicate_vec<T>(n,0,max);
    int size = vec.size();
    int dup_ind = rand()%size;
    int repl_ind = (dup_ind+rand()%(size-1)+1)%size;
    vec[repl_ind] = vec[dup_ind];
    return gen_tree<T>(vec);
};

TEST(bst_count,bst_count){
    for(int i = 0; i < 100 ; ++i){
        int ct = 20+rand()%10;
        if(rand()%2){
            BST_Node<double>* root = gen_count_sample<double>(ct,200);

            int student_ct = num_nodes<double>(root);
            ASSERT_EQ(ct,student_ct);
        }
        else{
            BST_Node<int>* root = gen_count_sample<int>(ct,200);

            int student_ct = num_nodes<int>(root);
            ASSERT_EQ(ct,student_ct);
        }
    }
}

TEST(dup_val,dup_val){
    for(int i = 0; i < 100 ; ++i){
        int ct = 15+rand()%10;
        if(rand()%2){
            BST_Node<double>* root =NULL;
            bool is_dup = rand()%2;
            if(is_dup) root=gen_dup_sample<double>(ct,200);
            else root =gen_count_sample<double>(ct,200);
            bool student_dup = has_duplicate_val<double>(root);
            ASSERT_EQ(is_dup,student_dup);
        }
        else{
            BST_Node<int>* root =NULL;
            bool is_dup = rand()%2;
            if(is_dup) root=gen_dup_sample<int>(ct,200);
            else root =gen_count_sample<int>(ct,200);
            bool student_dup = has_duplicate_val<int>(root);
            ASSERT_EQ(is_dup,student_dup);
        }
    }
}



TEST(tree_identical,tree_identical){
    int len = 20;
    for(int i = 0; i < 100 ; ++i){
        bool is_identical = rand()%2;
        if(rand()%1){
            vector<double> vec = gen_no_duplicate_vec<double>(len+1,0,200); //one extra
            vector<double> veca,vecb;
            for(int i =0;i <len;++i){
                veca.push_back(vec[i]);
                vecb.push_back(vec[i]);
            }
            if(!is_identical){
                vecb[rand()%len] = vec[len+1];
            }
            BST_Node<double>* a= gen_tree<double>(veca);
            BST_Node<double>* b= gen_tree<double>(vecb);
            ASSERT_EQ(is_identical,trees_identical<double>(a,b));
        }
        else{
            vector<int> vec = gen_no_duplicate_vec<int>(len+1,0,200); //one extra
            vector<int> veca,vecb;
            for(int i =0;i <len;++i){
            veca.push_back(vec[i]);
            vecb.push_back(vec[i]);
            }
            if(!is_identical){
            vecb[rand()%len] = vec[len+1];
            }
            BST_Node<int>* a= gen_tree<int>(veca);
            BST_Node<int>* b= gen_tree<int>(vecb);
            ASSERT_EQ(is_identical,trees_identical<int>(a,b));
        }
    }
}


