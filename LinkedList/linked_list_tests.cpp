
#include <iostream>
#include <cassert>
#include "linked_list.h"

using namespace std;


// This function is templated
// but actually it only works if 
// the linked list contains numbers (int, double, short, etc)
template <typename T>
string num_ll_to_string(T *ll){
	string s = "[";
	for(size_t i = 0; i < ll->size(); i++){
		s = s + std::to_string(ll->at(i));
		if( i < (ll->size()-1)){
			s = s + ", ";
		}
	}
	s = s + "]";
	return s;
}


string char_ll_to_string(LinkedList<char> *ll){
	string s = "[";
	for(size_t i = 0; i < ll->size(); i++){
		s = s + ll->at(i);
		if( i < (ll->size()-1)){
			s = s + ", ";
		}
	}
	s = s + "]";
	return s;
}


void BasicDoubleTest(){
	cout << "Basic Double Test..." << endl;

	LinkedList<double> ll;
	assert(num_ll_to_string(&ll) == "[]");
	assert(ll.size() == 0);

	cout << "PASSED!" << endl << endl;
}

void BasicIntTest(){
	cout << "Basic Int Test..." << endl;

	LinkedList<int> ll;
	assert(num_ll_to_string(&ll) == "[]");
	assert(ll.size() == 0);

	cout << "PASSED!" << endl << endl;
}

void PushBackTests(){
	cout << "Push Back Test..." << endl;

	LinkedList<unsigned int> *ll = new LinkedList<unsigned int>();
	ll->push_back(14);

	//cout << "ll: " << num_ll_to_string(ll) << endl;
	assert(num_ll_to_string(ll) == "[14]");
	assert(ll->size() == 1);


	ll->push_back(3);
	ll->push_back(56);
	ll->push_back(2147483647L + 10); // beyond the max signed int value.

	//cout << "ll: " << num_ll_to_string(ll) << endl;
	assert(num_ll_to_string(ll) == "[14, 3, 56, 2147483657]");
	assert(ll->size() == 4);

	delete ll;

	cout << "PASSED!" << endl << endl;
}


void PushFrontTests(){
	cout << "Push Front Test..." << endl;

	LinkedList<unsigned int> *ll = new LinkedList<unsigned int>();
	ll->push_front(35);

	//cout << "ll: " << num_ll_to_string(ll) << endl;
	assert(num_ll_to_string(ll) == "[35]");


	ll->push_front(6);
	ll->push_front(5);
	ll->push_front(2147483647L + 10); // beyond the max signed int value.

	//cout << "ll: " << num_ll_to_string(ll) << endl;
	assert(num_ll_to_string(ll) == "[2147483657, 5, 6, 35]");
	assert(ll->size() == 4);

	delete ll;

	cout << "PASSED!" << endl << endl;
}


void InsertTests(){
	cout << "Insert Test..." << endl;

	LinkedList<unsigned int> *ll = new LinkedList<unsigned int>();
	cout << "Insert empty list..." << endl;
	ll->insert(0, 35);

	cout << "test insert from 0" << endl;
	ll->insert(0, 12);
	ll->insert(0, 11);
	ll->insert(0, 10);
	ll->insert(0, 19);
	ll->insert(0, 18);

	cout << ll -> size() << endl;
	cout << "test insert from end" << endl;
	ll->insert(6, 999);

	cout << "test insert from middle" << endl;
	ll->insert(3, 7);
	ll->insert(3, 5);

	cout << "test invalid insert" << endl;
	try {
		ll->insert(100, 9999);
		assert(false);
	} catch (invalid_argument &e) {
		e.what();
	}

	delete ll;

	cout << "PASSED" << endl << endl;
}



int main(){
	
	BasicDoubleTest();
	BasicIntTest();
	PushBackTests();
	PushFrontTests();
	InsertTests();


	cout << "DONE!" << endl;
	return 0;
}
