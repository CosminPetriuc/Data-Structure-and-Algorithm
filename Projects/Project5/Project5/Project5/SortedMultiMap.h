#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class SMMIterator;

class SortedMultiMap {
    friend class SMMIterator;
private:
    struct Node {
        TElem info;
        Node* left;
        Node* right;
    };

    Node* root;
    Relation relation;

    void destroy(Node* node);
    Node* createNode(const TElem& element);
    void insertNode(Node*& node, const TElem& element);
    Node* searchNode(Node* node, TKey key) const;
    void removeNode(Node*& node, TKey key, TValue value);
    Node* findMinimum(Node* node) const;
    int count;

public:
    SortedMultiMap(Relation r);
    void add(TKey key, TValue value);
    std::vector<TValue> search(TKey key) const;
    bool remove(TKey key, TValue value);
    int size() const;
    bool isEmpty() const;
    SMMIterator iterator() const;
    ~SortedMultiMap();
};