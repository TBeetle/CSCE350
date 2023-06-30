#ifndef PROGRAM6_H
#define PROGRAM6_H

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

typedef struct char_freq{
  char c;
  double freq;

  char_freq(char c, double freq)
    :c(c),
     freq(freq)
  {}
} CFreq;

typedef struct char_code{
  char c;
  std::string code;
  char_code(char c, std::string code)
    :c(c),
     code(code)
  {}
} CCode;

typedef struct nodes {
	nodes* left;
	nodes* right;
	char c;
	double freq;

	nodes(char c, double freq, nodes* left, nodes* right)
		:c(c),
		freq(freq),
		left(left),
		right(right)
	{}

	nodes(char c, double freq)
		:c(c),
		freq(freq),
		left(nullptr),
		right(nullptr)
	{}
} Node;

struct Comparison {
	bool operator()(Node* left, Node* right) const {
		return left->freq > right->freq;
	}
};

void assHuffCodes(Node* node, std::string code, std::vector<CCode>& codes) {
	if (!node) {
		return;
	}
	if (node->left == nullptr && node->right == nullptr) {
		codes.push_back({node->c, code});
	}
	else {
		assHuffCodes(node->left, code+"0", codes);
		assHuffCodes(node->right, code+"1", codes);
	}
}
Node* buildTree(std::vector<CFreq > cfs){
	 std::priority_queue<Node*, std::vector<Node*>, Comparison> pq;
        for (auto& freq : cfs ) {
                pq.push(new Node(freq.c, freq.freq));
        }

        while (pq.size() > 1) {
                Node* left = pq.top();
                pq.pop();

                Node* right = pq.top();
                pq.pop();

                Node* parent = new Node('\0',left->freq + right->freq, left, right);
                pq.push(parent);
                
        }
	Node* root = nullptr;
	if(pq.size() == 1) {
		root = pq.top();
	}
	return root;

}
//input: vector of CFreqs 
//returns: vector of CCodes
std::vector<CCode> getHuffCodes(std::vector<CFreq > cfs){
	Node* root = buildTree(cfs);
	std::vector<CCode> codes;
	assHuffCodes(root, "", codes);
	std::sort(codes.begin(), codes.end(), [](const CCode& a, const CCode& b) {return a.c < b.c;});
  //or define everything here (nothing in targetgtest.cpp)
  //
  //following is for compilation purposes
  return codes;
}
#endif //PROGRAM6_H
