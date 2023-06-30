#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>

using std::swap;

//note returns INDEX of median
//does NOT move the median into the pivot position
template<typename T> inline
int medianOf3(T A[], int l, int r){
	//this is overcommented... also, try and avoid using pointers
	T* a = A + l;//array name is just pointer to 1st (0 index) elem., + l shifts l*(T size)
	T* b = A + l + (r-l)/2;//middle item... int division rounds down
	T* c = A + r;

	//when a is a pointer, *a is the dereference operator (gives value a points to)
	T* m;
	if(*a < *b){
		if(*b < *c) m=b; 
		else if(*c < *a) m=a;
		else m=c;
	} else{ //b <=a
		if(*a < *c) m=a;
		else if(*c < *b) m=b;
		else m=c;
	}
	return m-A; //m-A is the number of elements from A[0]

}

//remember: l and r are INLCUSIVE (just like Lomuto)
//make sure to call medianOf3 on the subarray before partitioning
template<typename T>
int hoarePartition(T A[], int l, int r){
	T median = medianOf3(A,l,r);
	swap (A[l], A[median]);
	T pivot = A[l];
	int left = l;
	int right = r+1;
	do {
		do { 
			left++;
		} while (A[left] < pivot);
		do { 
			right--;
		}
		while (A[right] > pivot);
		swap(A[left], A[right]);

	} while (left < right);


	swap(A[left], A[right]);
	swap(A[l], A[right]);
	return right;

}

template<typename T>
void quicksort(T A[], int l, int r){
	int left = l;
	int right = r;
	if (left < right){
	T sort = hoarePartition(A, left, right);
	quicksort(A,l,sort-1);
	quicksort(A,sort+1,right);

	}
}

#endif
