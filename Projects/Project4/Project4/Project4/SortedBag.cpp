#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cmath>

SortedBag::SortedBag(Relation r) {
	capacity = 10;
	count = 0;
	relation = r;
	hashTable = new Node * [capacity];
	for (int i = 0; i < capacity; i++) {
		hashTable[i] = nullptr;
	}
}

int SortedBag::hash(TComp e) const {
	return abs(e) % capacity;
}

//best case 
//worst case 
//average case 
void SortedBag::resize() {
	int newCapacity = capacity * 2; //Calculate the new capacity for the resized hash table
	Node** newHashTable = new Node * [newCapacity];// Create a new hash table with the new capacity
	for (int i = 0; i < newCapacity; i++)// Initialize all elements of the new hash table to nullptr
	{
		newHashTable[i] = nullptr;
	}

	for (int i = 0; i < capacity; i++)// Iterate over the old hash table
	{
		Node* current = hashTable[i];// Get the head node at the current index
		while (current != nullptr)// Traverse the linked list at the current index
		{
			Node* next = current->next;// Store the next pointer of the current node
			int newIndex = hash(current->info);// Calculate the new hash index for the current node's element
			current->next = newHashTable[newIndex];
			newHashTable[newIndex] = current;
			current = next;
		}
	}

	delete[] hashTable;
	hashTable = newHashTable;
	capacity = newCapacity;
}
//best case O(1)
//worst case
//average case 
void SortedBag::add(TComp e) {
	int index = hash(e);// Calculate the hash index for the given element
	Node* newNode = new Node; // Create a new node and assign the element to it
	newNode->info = e;
	newNode->next = hashTable[index];// Set the new node's next pointer to the head node at the hash index
	hashTable[index] = newNode;// Update the head node at the hash index to the new node
	count++;

	if (count >= capacity) // Check if the count exceeds the capacity
		resize();
}

//best case O(1)
//worst case O(n)
//average case O(n)
bool SortedBag::remove(TComp e) {
	int index = hash(e);// Calculate the hash index for the given element
	Node* current = hashTable[index];// Get the head node at the hash index
	Node* prev = nullptr;

	while (current != nullptr) // Traverse the linked list at the hash index 
	{
		if (current->info == e) // Check if the current node's element matches the given element
		{
			if (prev == nullptr)  // Check if the current node is the head node
			{
				hashTable[index] = current->next;// Update the head node to the next node
			}
			else {
				prev->next = current->next;// Update the previous node's next pointer to skip the current node
			}

			delete current;
			count--;
			return true;
		}
		// Update the previous and current pointers
		prev = current;
		current = current->next;
	}

	return false;
}


//best case O(1)
//worst case O(n)
//average case O(n)
bool SortedBag::search(TComp e) const {
	int index = hash(e);// Calculate the hash index for the given element
	Node* current = hashTable[index];// Get the head node at the hash index

	while (current != nullptr) // Traverse the linked list at the hash index
	{
		if (current->info == e)// Check if the current node's element matches the given element
		{
			return true;
		}
		current = current->next;
	}

	return false;
}

//best case O(1)
//worst case O(n)
//average case O(n)
int SortedBag::nrOccurrences(TComp e) const {
	int index = hash(e); // Calculate the hash index for the given element
	Node* current = hashTable[index];// Get the head node at the hash index
	int count = 0;

	while (current != nullptr)  // Traverse the linked list at the hash index
	{
		if (current->info == e) // Check if the current node's element matches the given element
		{
			count++;
		}
		current = current->next;
	}

	return count;
}
//average case theta(1)
int SortedBag::size() const {
	return count;
}

//average case theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

//average case theta(1)
bool SortedBag::isEmpty() const {
	return count == 0;
}

//best case O(1)
//worst case 
//average case 
SortedBag::~SortedBag() {
	for (int i = 0; i < capacity; i++) // Loop through each hash table slot
	{
		Node* current = hashTable[i]; // Get the current node in the slot
		while (current != nullptr)// Traverse the linked list in the slot 
		{
			Node* next = current->next;
			delete current;
			current = next;
		}
	}

	delete[] hashTable;
}
