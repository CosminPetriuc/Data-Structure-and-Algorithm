#pragma once

#include "SortedMultiMap.h"

class SMMIterator {
    friend class SortedMultiMap;
private:
    const SortedMultiMap& map;
    struct StackNode {
        typename SortedMultiMap::Node* node;
        int count;
    };
    StackNode* stack;
    int stackSize;

    void pushLeft(typename SortedMultiMap::Node* node);
    void resizeStack();
public:
    SMMIterator(const SortedMultiMap& map);
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};
