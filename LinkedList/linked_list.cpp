
#include "linked_list.h"
#include <stdexcept>
//#include <iostream>

using namespace std;

template <typename T>
LinkedList<T>::~LinkedList(){
	Node<T> *cur = head;
	while(cur != nullptr){
		Node<T> *next = cur->next;
		delete cur;
		cur = next;
	}
}

template <typename T>
void LinkedList<T>::insert(size_t pos, T item){
	if(pos > numItems){
		throw invalid_argument("List index out of range: " + to_string(pos));
	}
	
	Node<T> *n = new Node<T>;
	n->data = item;

	if(pos == 0){
		// call push_front
		this -> push_front(item);
		delete n;
		return;
	}
	
	if(pos == numItems){
		// call push_back
		this -> push_back(item);
		delete n;
		return;
	}
	
	numItems++;
	Node<T> *cur = get_node(pos);
	cur->prev->next = n;
	n->prev = cur->prev;
	n->next = cur;
	cur->prev = n;
}

template <typename T> 
void LinkedList<T>::push_back(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;
	
	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	tail->next = n;
	n->prev = tail;
	tail = n;	
}


template <typename T>
void LinkedList<T>::push_front(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;

	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	head->prev = n;
	n->next = head;
	head = n;
}


template <typename T>
T LinkedList<T>::at(size_t idx){
	if(idx >= numItems){
		throw std::invalid_argument("List index out of range: " + std::to_string(idx));
	}

	Node<T> *n = get_node(idx);
	return n->data;
}


template <typename T>
Node<T> *LinkedList<T>::get_node(size_t idx){

	size_t i = 0;
	Node<T> *cur = head;
	while(i < idx){
		cur = cur->next;
		i++;
	}

	return cur;
}



