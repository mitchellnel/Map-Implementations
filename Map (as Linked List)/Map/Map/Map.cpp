//
//  Map.cpp
//  Proj2
//
//  Created by Mitchell McLinton on 23/1/20.
//  Copyright © 2020 Mitchell McLinton. All rights reserved.
//

#include "Map.h"
#include <iostream>

// TODO: Implement constructor
Map::Map() : m_nItems(0) {
    dummy.next = &dummy;
    dummy.prev = &dummy;
}

// TODO: Implement destructor
Map::~Map() {
    Node* t = dummy.next;
    while (t != &dummy) {
        Node* delNode = t;
        t = t->next;
        delete delNode;
    }
}

// TODO: Implement copy constructor
Map::Map(const Map& other) : m_nItems(other.m_nItems) {
    if (other.empty()) {
        dummy.next = &dummy;
        dummy.prev = &dummy;
    } else {
        // dynamically allocate and copy item of first meaningful node
        dummy.next = new Node;
        dummy.next->item = other.dummy.next->item;
        // pointers to track current node in traversal
        Node* p1 = dummy.next;
        Node* p2 = other.dummy.next;
        
        for (int i=1; i < m_nItems; i++, p2 = p2->next) {
            p1->next = new Node;
            p1->next->item = p2->next->item;    // copy item
            Node* temp = p1;    // linking nodes
            p1 = p1->next;
            p1->prev = temp;
        }
        
        p1->next = &dummy;  // make linked list doubly and circular
        dummy.prev = p1;
    }
}

// TODO: Implement assignment operator
// Remember to check for aliasing issues, i.e. trying to call m = m;
// Remember to use the swap function
Map& Map::operator=(const Map& rhs) {
    if (this != &rhs) {
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}

// TODO: Implement empty() function
bool Map::empty() const {
    return dummy.next == &dummy;
}

// TODO: Implement size() function
int Map::size() const {
    return m_nItems;
}

// TODO: Implement insert() function
bool Map::insert(const KeyType& key, const ValueType& value) {
    for (Node* t = dummy.next; t != &dummy; t = t->next)
        if (t->item.key == key) return false;   // trying to add duplicate key, so return false
    
    Node* ptr = new Node;
    
    ptr->next = &dummy;     // by default we add to the back of the linked list
    ptr->prev = dummy.prev;
    ptr->prev->next = ptr;
    dummy.prev = ptr;
    
    ptr->item.key = key;
    ptr->item.val = value;
    m_nItems++;
    return true;
}

// TODO: Implement update() function
bool Map::update(const KeyType& key, const ValueType& value) {
    for (Node* t = dummy.next; t != &dummy; t = t->next) {
        if (t->item.key == key) {
            t->item.val = value;
            return true;
        }
    }
    return false;
}

// TODO: Implement insertOrUpdate() function
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    if (!update(key, value))
        insert(key, value);
    return true;
}

// TODO: Implement erase() function
bool Map::erase(const KeyType& key) {
    if (empty())
        return false;
    
    for (Node* t = dummy.next; t != &dummy; t = t->next) {
        if (t->item.key == key) {
            t->prev->next = t->next;
            t->next->prev = t->prev;
            delete t;
            m_nItems--;
            return true;
        }
    }
    return false;
}

// TODO: Implement contains() function
bool Map::contains(const KeyType& key) const {
    for (Node* t = dummy.next; t != &dummy; t = t->next)
        if (t->item.key == key) return true;
    return false;
}

// TODO: Implement two parameter get() function
bool Map::get(const KeyType& key, ValueType& value) const {
    for (Node* t = dummy.next; t != &dummy; t = t->next) {
        if (t->item.key == key) {
            value = t->item.val;
            return true;
        }
    }
    return false;
}

// TODO: Implement three parameter get() function
bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (i < 0 || i >= size())
        return false;
    
    int j = 0;
    Node* t = dummy.next;
    while (j <= i) {
        key = t->item.key;
        value = t->item.val;
        
        t = t->next;
        j++;
    }
    return true;
}

// TODO: Implement swap() function
void Map::swap(Map& other) {
    Node* tempNext = dummy.next;
    dummy.next = other.dummy.next;
    other.dummy.next = tempNext;
    tempNext->prev = &other.dummy;
    dummy.next->prev = &dummy;
    
    Node* tempPrev = dummy.prev;
    dummy.prev = other.dummy.prev;
    other.dummy.prev = tempPrev;
    tempPrev->next = &other.dummy;
    dummy.prev->next = &dummy;
    
    int tempItems = m_nItems;
    m_nItems = other.m_nItems;
    other.m_nItems = tempItems;
}

void Map::dump() const {
    std::cerr << std::endl << "=== dump() called ===" << std::endl;
    std::cerr << "Size of Map is: " << m_nItems << std::endl;
    std::cerr << "Printing contents of map: " << std::endl;
    for (Node* t = dummy.next; t != &dummy; t = t->next)
        std::cerr << "\t" << t->item.key << ": " << t->item.val << std::endl;
    std::cerr << "=== dump() called ===" << std::endl << std::endl;
}

// TODO: Implement combine() function
bool combine(const Map& m1, const Map& m2, Map& result) {
    Map combinedMap;
    
    // fill in combinedMap with m1's values
    for (int i=0; i < m1.size(); i++) {
        KeyType m1key;
        ValueType m1value;
        m1.get(i, m1key, m1value);
        combinedMap.insert(m1key, m1value);
    }
    
    bool returnFlag = true;
    
    // now check each of m2's values against those in combinedMap, inserting/deleting according to spec rules
    for (int i=0; i < m2.size(); i++) {
        KeyType m2key;
        ValueType m2value;
        m2.get(i, m2key, m2value);
        
        if (!combinedMap.contains(m2key)) {
            combinedMap.insert(m2key, m2value);
        } else {
            ValueType resultValue;
            combinedMap.get(m2key, resultValue);
            if (resultValue == m2value)
                continue;
            else {
                combinedMap.erase(m2key);
                returnFlag = false;
            }
        }
    }
    
    result = combinedMap;
    
    return returnFlag;
}

// TODO: Implement reassign() function
void reassign(const Map& m, Map& result) {
    Map reassignedMap;
    
    // if map only has one key-value pair, can't reassign anything, so result will just be m
    if (m.size() == 1) {
        reassignedMap = m;
        return;
    }
    
    // use two int counters to keep track of pairs in Map m
    for (int i = 0, j = 1; j < m.size() && i < m.size(); i += 2, j += 2) {
        KeyType p1Key;
        ValueType p1Val;
        KeyType p2Key;
        ValueType p2Val;
        
        // get details of items
        m.get(i, p1Key, p1Val);
        m.get(j, p2Key, p2Val);
        
        // swap them
        reassignedMap.insertOrUpdate(p1Key, p2Val);
        reassignedMap.insertOrUpdate(p2Key, p1Val);
    }
    
    // if m.size() returned an odd number, result wouldn't contain the very last item in Map m
    // so we swap the values that the first and last keys have
    if (m.size() % 2 != 0) {
        KeyType hKey;
        ValueType hValue;
        KeyType tKey;
        ValueType tValue;
        
        m.get(m.size()-1, tKey, tValue);    // take value of last item in m (not yet in result)
        reassignedMap.get(0, hKey, hValue);        // take new value of first item in result
        
        reassignedMap.update(hKey, tValue);        // reassign first item in result
        reassignedMap.insert(tKey, hValue);        // and add the last item to result
    }
    
    result = reassignedMap;
}
