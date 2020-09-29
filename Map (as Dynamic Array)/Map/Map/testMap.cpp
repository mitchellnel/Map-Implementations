//
//  testMap.cpp
//  Homework 1
//
//  Created by Mitchell McLinton on 16/1/20.
//  Copyright © 2020 Mitchell McLinton. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void doesCopyWork(Map m) {
    m.dump();
}

int main() {
    Map m; // maps strings to doubles
    assert(m.empty());
    KeyType champion = "hamilton";
    ValueType hManValue = 3.023;
    assert(m.insert(champion, hManValue));
    assert(m.size() == 1);
    assert(m.insert("vettel", 3.798));
    assert(m.size() == 2);
    assert(m.update("vettel", 3.817));
    assert(!m.insert("vettel", 3.000));

    assert(m.insertOrUpdate("ricciardo", 3.000));
    assert(m.size() == 3);
    assert(m.insertOrUpdate("vettel", 3.883));
    assert(m.size() == 3);
    assert(m.insertOrUpdate("verstappen", 3.300));
    assert(m.size() == 4);

    assert(m.erase("ricciardo"));
    assert(m.size() == 3);
    assert(!m.erase("norris"));

    assert(!m.contains("ricciardo"));
    assert(m.contains("verstappen"));

    double v = -99;
    assert(!m.get("ricciardo", v) && v == -99);
    assert(m.get("hamilton", v) && v == 3.023);

    v = -99;
    string k;
    assert(!m.get(5, k, v) && k == "" && v == -99);
    assert(m.get(2, k, v) && k == "verstappen" && v == 3.300);

    m.dump();

    Map m2; // maps strings to doubles
    m2.insert("mitchell", 44);
    m2.insert("alicia", 45);
    m2.insert("hman", 40);
    m2.insert("alyssa", 38);
    m2.insert("steve", 3);
    m2.insert("will", 24);
    m2.insert("david", 69);

    m2.dump();


    m.swap(m2);

    m.dump();
    m2.dump();

    Map m3;
    m3.dump();
    m3 = m2;
    m2.dump();
    m3.dump();
    
    doesCopyWork(m);

    cout << "Passed all tests!" << endl;
    return 0;
}

/*
int main() {
    Map m; // maps ints to bools
    assert(m.insert(44, true));
    assert(m.insert(69, true));
    assert(m.insertOrUpdate(69, false));
    assert(m.insertOrUpdate(33, true));
    assert(m.erase(69));
    assert(m.insertOrUpdate(3, true));
    
    Map m2; // maps ints to bools
    assert(m2.insertOrUpdate(44, true));
    assert(m2.insertOrUpdate(45, true));
    assert(m2.insertOrUpdate(23, false));
    assert(m2.insertOrUpdate(24, true));
    assert(m2.insertOrUpdate(40, true));
    assert(m2.insertOrUpdate(38, true));
    
    m.dump();
    m2.dump();
    
    m.swap(m2);
    
    m.dump();
    m2.dump();
    
    cout << "Passed all tests!" << endl;
}
*/
