
#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {
	//TODO - Implementation
	this->r = r;
	head = tail = nullptr;
}

//best case  T(n)
//worst case T(n)
//overall O(n)
void PriorityQueue::push(TElem e, TPriority p) {
	//TODO - Implementation
	Element elem = make_pair(e, p);
	Node* newNode = new Node{ elem, nullptr, nullptr };

	if (isEmpty()) {
		head = tail = newNode;
	}
	else {
		Node* current = head;
		while (current != nullptr && r(current->elem.second, p)) {
			current = current->next;
		}
		if (current == nullptr) {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		else {
			newNode->prev = current->prev;
			newNode->next = current;
			if (current->prev != nullptr) {
				current->prev->next = newNode;
			}
			current->prev = newNode;
			if (current == head) {
				head = newNode;
			}
		}
	}
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {
	//TODO - Implementation
	if (isEmpty()) {
		throw exception("Priority queue is empty.");
	}
	return head->elem;
	
}

//base case T(1)
//worst case T(1)
//overall T(1)
Element PriorityQueue::pop() {
	//TODO - Implementation
	if (isEmpty()) {
		throw exception("Priority queue is empty.");
	}
	Element elem = head->elem;
	Node* temp = head;
	if (head == tail) {
		head = tail = nullptr;
	}
	else {
		head = head->next;
		head->prev = nullptr;
	}
	delete temp;
	return elem;
	
}

bool PriorityQueue::isEmpty() const {
	//TODO - Implementation
	return head == nullptr;
	return false;
}

//best case O(1)
//worst case O(n)
//all cases O(n)
PriorityQueue::~PriorityQueue() {
	//TODO - Implementation
	Node* current = head;
	while (current != nullptr) {
		Node* temp = current;
		current = current->next;
		delete temp;
	}
};

