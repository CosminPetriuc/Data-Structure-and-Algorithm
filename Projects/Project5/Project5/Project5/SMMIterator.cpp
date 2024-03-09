#include "SMMIterator.h"

SMMIterator::SMMIterator(const SortedMultiMap& map) : map(map) {
    stack = new StackNode[10];
    stackSize = 0;
    first();
}

//best case O(1)
//worst case O(n)
//average case O(n)
void SMMIterator::pushLeft(typename SortedMultiMap::Node* node) {
    while (node != nullptr) {
        // Push the current node to the stack along with the count of visited nodes in its left subtree
        stack[stackSize].node = node;
        stack[stackSize].count = 0;
        stackSize++;
        node = node->left;// Move to the left child of the current node
    }
}

//best case O(1)
//worst case O(n)
//average case O(n)
void SMMIterator::resizeStack() {
    // Create a new stack with double the size of the current stack
    StackNode* newStack = new StackNode[2 * stackSize];
    for (int i = 0; i < stackSize; i++) {
        newStack[i] = stack[i];
    }
    delete[] stack;
    stack = newStack;
}

//best case O(1)
//worst case O(n)
//average case O(n)
void SMMIterator::first() {
    stackSize = 0;
    pushLeft(map.root);
}

//best case O(1)
//worst case O(n)
//average case O(n)
void SMMIterator::next() {
    if (!valid()) {
        throw std::exception("Invalid iterator");
    }

    StackNode topNode = stack[stackSize - 1];
    stackSize--;

    pushLeft(topNode.node->right);
}

//best case O(1)
//worst case O(1)
//average case O(1)
bool SMMIterator::valid() const {
    return stackSize > 0;
}


//best case O(1)
//worst case O(1)
//average case O(1)
TElem SMMIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception("Invalid iterator");
    }

    StackNode topNode = stack[stackSize - 1];
    return topNode.node->info;
}
