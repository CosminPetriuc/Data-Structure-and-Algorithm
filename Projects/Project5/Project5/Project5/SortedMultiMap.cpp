#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


SortedMultiMap::SortedMultiMap(Relation r) {
    root = nullptr;
    relation = r;
    count = 0;
}

//best case O(1)
//worst case O(1)
//average case O(1)
SortedMultiMap::~SortedMultiMap() {
    destroy(root);
}

//best case theta(1)
//worst case theta(1)
//average case theta(1)
void SortedMultiMap::destroy(Node* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

//best case theta(1)
//worst case theta(1)
//average case theta(1)
typename SortedMultiMap::Node* SortedMultiMap::createNode(const TElem& element) {
    typename Node* newNode = new Node;
    newNode->info = element;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

//best case theta(1)
//worst case theta(n)
//average case O(n)
void SortedMultiMap::insertNode(Node*& node, const TElem& element) {
    if (node == nullptr) {
        node = createNode(element);
    }
    else if (relation(element.first, node->info.first)) {
        insertNode(node->left, element);
    }
    else {
        insertNode(node->right, element);
    }
}
 
//best case theta(1)
//worst case theta(n)
//average case O(n)
typename SortedMultiMap::Node* SortedMultiMap::searchNode(typename SortedMultiMap::Node* node, TKey key) const {
    // If the current node is nullptr or its key matches the search key, return the current node
    if (node == nullptr || node->info.first == key) {
        return node;
    }
    else if (relation(key, node->info.first)) {
        return searchNode(node->left, key);
    }
    else {
        return searchNode(node->right, key);
    }
}

//best case O(1)
//worst case O(n)
//average case O(n)
void SortedMultiMap::removeNode(Node*& node, TKey key, TValue value) {
    if (node == nullptr) {
        return;
    }
    // If the key is less than the current node's key, recursively remove from the left subtree
    if (relation(key, node->info.first)) {
        removeNode(node->left, key, value);
    }
    // If the key is greater than the current node's key, recursively remove from the right subtree
    else if (relation(node->info.first, key)) {
        removeNode(node->right, key, value);
    }
    // If the key and value match the current node, perform removal
    else if (node->info.second == value) {
        // If the current node has no left child, replace it with its right child
        if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // If the current node has no right child, replace it with its left child
        else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else {
            Node* minimum = findMinimum(node->right); // Find the minimum node in the right subtree
            node->info = minimum->info; // Replace the current node's info with the info of the minimum node
            removeNode(node->right, minimum->info.first, minimum->info.second);
        }
    }
}

//best case O(1)
//worst case O(n)
//average case O(n)
typename SortedMultiMap::Node* SortedMultiMap::findMinimum(typename SortedMultiMap::Node* node) const {
    if (node->left == nullptr) {
        return node;
    }
    return findMinimum(node->left);
}

//best case O(1)
//worst case O(n)
//average case O(n)
void SortedMultiMap::add(TKey key, TValue value) {
    TElem element(key, value);
    insertNode(root, element);
    count++; // Increment count when adding a new key-value pair
}

//best case O(1)
//worst case O(n)
//average case O(n)
std::vector<TValue> SortedMultiMap::search(TKey key) const {
    std::vector<TValue> values;
    Node* node = searchNode(root, key);
    if (node != nullptr) {
        Node* currentNode = node;
        // Iterate over the nodes with the same key and collect their associated values
        while (currentNode != nullptr && currentNode->info.first == key) {
            values.push_back(currentNode->info.second);
            currentNode = currentNode->right;
        }
    }
    return values;
}

//best case O(1)
//worst case O(n)
//average case O(n)
bool SortedMultiMap::remove(TKey key, TValue value) {
    int initialCount = count;// Store the initial count of key-value pairs
    removeNode(root, key, value);
    if (count < initialCount) {
        count--; // Decrement count when removing a key-value pair
        return true;
    }
    return false;
}
//best case O(1)
//worst case O(1)
//average case O(1)
int SortedMultiMap::size() const {
    return count;
}

//best case O(1)
//worst case O(1)
//average case O(1)
bool SortedMultiMap::isEmpty() const {
    return root == nullptr;
}

//best case O(1)
//worst case O(1)
//average case O(1)
SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}
