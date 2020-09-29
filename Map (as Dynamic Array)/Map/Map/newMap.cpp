//
//  newMap.cpp
//  Homework 1
//
//  Created by Mitchell McLinton on 16/1/20.
//  Copyright © 2020 Mitchell McLinton. All rights reserved.
//

#include "newMap.h"
#include <iostream>
#include <array>

// TODO: Dynamic allocation
Map::Map(const int nItems) : m_maxItems(nItems), m_nItems(0) {
    m_items = new Item[m_maxItems];
}

// TODO: Destructor
Map::~Map() {
    delete [] m_items;
}

// TODO: Copy constructor
Map::Map(const Map& other) : m_maxItems(other.m_maxItems), m_nItems(other.m_nItems) {
    m_items = new Item[m_maxItems];
    
    for (int k=0; k < m_nItems; k++)
        m_items[k] = other.m_items[k];
}

// TODO: Assignment operator
Map& Map::operator=(const Map& rhs) {
    delete [] m_items;
    m_maxItems = rhs.m_maxItems;
    m_nItems = rhs.m_nItems;
    m_items = new Item[m_maxItems];
        
    for (int k=0; k < m_nItems; k++)
        m_items[k] = rhs.m_items[k];
    return *this;
}

bool Map::empty() const {
    if (m_nItems == 0)
        return true;
    else
        return false;
}

int Map::size() const {
    return m_nItems;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    if (m_nItems == m_maxItems)
        return false;
    
    for (int k=0; k < m_nItems; k++) {
        if (key == m_items[k].key)
            return false;
    }
    
    m_items[m_nItems].key = key;
    m_items[m_nItems].val = value;
    m_nItems++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
    for (int k=0; k < m_nItems; k++) {
        if (key == m_items[k].key) {
            m_items[k].val = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    if (update(key, value))
        return true;
    else
        return insert(key, value);
}

bool Map::erase(const KeyType& key) {
    for (int k=0; k < m_nItems; k++) {
        if (key == m_items[k].key) {
            for (int j=k+1; j < m_nItems; j++) {
                m_items[j-1] = m_items[j];
            }
            m_nItems--;
            return true;
        }
    }
    return false;
}

bool Map::contains(const KeyType& key) const {
    for (int k=0; k < m_nItems; k++) {
        if (key == m_items[k].key)
            return true;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
    for (int k=0; k < m_nItems; k++) {
        if (key == m_items[k].key) {
            value = m_items[k].val;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (i < 0 || i >= size())
        return false;
    
    key = m_items[i].key;
    value = m_items[i].val;
    return true;
}

// TODO: Change implementation of swap()
void Map::swap(Map& other) {
    int tempMaxItems = m_maxItems;
    m_maxItems = other.m_maxItems;
    other.m_maxItems = tempMaxItems;
    
    int tempInt = m_nItems;
    m_nItems = other.m_nItems;
    other.m_nItems = tempInt;
    
    Item* tempPtr = m_items;
    m_items = other.m_items;
    other.m_items = tempPtr;
}

void Map::dump() const {
    std::cerr << std::endl << "=== dump() called ===" << std::endl;
    std::cerr << "Max size of Map is: " << m_maxItems << std::endl;
    std::cerr << "Size of Map is: " << m_nItems << std::endl;
    std::cerr << "Printing contents of map: " << std::endl;
    for (int i=0; i < m_nItems; i++)
        std::cerr << "\t" << m_items[i].key << ": " << m_items[i].val << std::endl;
    std::cerr << "=== dump() called ===" << std::endl << std:: endl;
}
