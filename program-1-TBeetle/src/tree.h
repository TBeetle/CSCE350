#ifndef TREE_H
#define TREE_H

template<typename T>
struct BST_Node {
T val;
BST_Node* left;
BST_Node* right;

BST_Node(T v) : val(v),left(NULL),right(NULL)
{}

void insert(T v) {
    if(v>val){
        if (right==NULL) right = new BST_Node<T>(v);
        else right->insert(v);
    }
    else{
        if (left==NULL) left = new BST_Node<T>(v);
        else left->insert(v);
    }
}

};


template<typename T>
void delete_tree(BST_Node<T>* root){
    if (root==NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}


//your work starts here
template<typename T>
int num_nodes(BST_Node<T>* root){
    if (root==NULL) return 0;
    int left = num_nodes(root->left);
    int right = num_nodes(root->right);
    return 1+left+right;
}


template<typename T>
bool has_duplicate_val(BST_Node<T>* root){
	std::vector<T> v;
    return has_duplicate_val_helper(root, v);
}



template<typename T>
bool trees_identical(BST_Node<T>* a, BST_Node<T>* b){
	if (a == NULL && b == NULL) {
		return true;
	}
	if (a == NULL || a == NULL) {
		return false;
	}
	if (a != NULL && b!= NULL)
		return trees_identical(a->right,b->right) && trees_identical(a->left, b->left);
return false;
}

template<typename T>
bool has_duplicate_val_helper(BST_Node<T>* root,std::vector<T>& v) {
	if (root == NULL)
		return false;
	typename std::vector<T>::iterator i = find(v.begin(),v.end(),root->val);
	if (i != v.end()) {
		return true;
	}
	v.push_back(root->val);
	return has_duplicate_val_helper(root->left,v) || has_duplicate_val_helper(root->right,v);
}

#endif //TREE_H
