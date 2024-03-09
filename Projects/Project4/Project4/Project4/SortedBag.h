#pragma once

typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	struct Node {
		TComp info;
		Node* next;
	};

	Node** hashTable;
	int capacity;
	int count;
	Relation relation;

	// Hash function
	int hash(TComp e) const;

	// Resize the hash table if necessary
	void resize();

public:
	// Constructor
	SortedBag(Relation r);

	// Adds an element to the sorted bag
	void add(TComp e);

	// Removes one occurrence of an element from the sorted bag
	// Returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	// Checks if an element appears in the sorted bag
	bool search(TComp e) const;

	// Returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	// Returns the number of elements in the sorted bag
	int size() const;

	// Returns an iterator for the sorted bag
	SortedBagIterator iterator() const;

	// Checks if the sorted bag is empty
	bool isEmpty() const;

	// Destructor
	~SortedBag();
};
