#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	currentPosition = 0;
	currentNode = nullptr;

	// Find the first non-empty slot in the hash table
	for (int i = 0; i < bag.capacity; i++) {
		if (bag.hashTable[i] != nullptr) {
			currentNode = bag.hashTable[i];
			break;
		}
	}

	if (currentNode != nullptr)
		currentElementCount = 1;
}

//average case theta(1)
TComp SortedBagIterator::getCurrent() {
	if (valid() && currentNode != nullptr) {
		return currentNode->info;
	}
	// Return a default value or throw an exception to handle the error case
	return NULL_TCOMP;
}


bool SortedBagIterator::valid() {
	return currentNode != nullptr;
}

//best case O(1)
//worst case 
void SortedBagIterator::next() {
	if (!valid())
		throw std::exception("Invalid iterator");

	if (currentElementCount < bag.nrOccurrences(currentNode->info)) {
		currentElementCount++;
	}
	else {
		// Move to the next node in the chain
		currentNode = currentNode->next;
		currentElementCount = 1;
	}
	if (currentNode == nullptr) {
		// Find the next non-empty slot in the hash table
		for (int i = bag.hash(currentNode->info) + 1; i < bag.capacity; i++) {
			if (bag.hashTable[i] != nullptr) {
				currentNode = bag.hashTable[i];
				break;
			}
		}
	}
}

void SortedBagIterator::first() {
	currentPosition = 0;
	currentNode = nullptr;

	// Find the first non-empty slot in the hash table
	for (int i = 0; i < bag.capacity; i++) {
		if (bag.hashTable[i] != nullptr) {
			currentNode = bag.hashTable[i];
			break;
		}
	}

	if (currentNode != nullptr)
		currentElementCount = 1;
}
