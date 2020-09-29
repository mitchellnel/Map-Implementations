//
//  testMap.cpp
//  Proj2
//
//  Created by Mitchell McLinton on 23/1/20.
//  Copyright © 2020 Mitchell McLinton. All rights reserved.
//

#include "Map.h"
#include <cassert>
#include <iostream>
using namespace std;

/* ACTUAL TESTING */
int main() {
      // Default constructor should create an empty Map
    Map m;  // maps std::strings to doubles
    
      // For an empty Map:
    assert(m.empty());              // test Map::empty
    assert(m.size() == 0);          // test Map::size
    assert(!m.erase("hamilton"));   // nothing to erase; testing Map::erase
    
      // Test type aliases
    KeyType champ = "hamilton";         // KeyType is alias for std::string
    ValueType ageInYrs = 35.04;         // ValueType is alias for double
    assert(m.insert(champ, ageInYrs));  // test Map::insert
    assert(m.size() == 1);              // test Map::insert has inserted sucessfully & Map::size returns appropriately
    
      // Test Map::insert a bit more
    assert(m.insert("ricciardo", 30.57));       // test Map::insert
    assert(!m.insert("ricciardo", 890.123));    // test Map::insert; "ricciardo" already exists in Map, so insert returns false
    assert(m.size() == 2);                      // test previous line hasn't added another node into the Map
    
      // Test Map::update
    assert(m.insert("verstappen", 2.32));       // insert a new node
    assert(m.update("verstappen", 22.32));      // test Map::update
    assert(!m.update("vettel", 32.56));         // test Map::update; "vettel" doesn't exist in Map, so update returns false
    assert(m.size() == 3);                      // test Map::size
    
      //Test two parameter Map::get
    ValueType maxAge = -3.14159;
    assert(m.get("verstappen", maxAge) && maxAge == 22.32);     // test two parameter Map::get; it should set maxAge to the value of "verstappen" currently in the Map
    assert(!m.get("max", maxAge) && maxAge == 22.32);           // test two parameter Map::get; it should not change maxAge as key "max" does not belong to any node in the Map
    
      // Test Map::insertOrUpdate
    assert(m.insertOrUpdate("vettel", 3.56));             // test Map::insertOrUpdate; this should insert a new node into the Map
    assert(m.size() == 4);                                // size of Map should now be 4
    assert(m.insertOrUpdate("vettel", 32.56));            // test Map::insertOrUpdate; this should update the previously added "vettel" node
    assert(m.size() == 4);                                // size of Map should still be 4
    ValueType sebAge = -3.14159;                          // create ValueType variable for get function
    assert(m.get("vettel", sebAge) && sebAge == 32.56);   // get function should set sebAge to 32.56, as reflective of our previous update
    
      // Test Map::contains
    assert(m.contains("vettel"));       // key "vettel" is found in the Map, so this returns true
    assert(!m.contains("kubica"));      // key "kubica" is not found in the Map, so this returns false
    
      // Test Map::erase
    assert(m.insert("hulkenberg", 32.43));      // key "hulkenberg" is added to the Map
    assert(m.size() == 5);                      // checking that size has been updated accordingly
    assert(m.contains("hulkenberg"));           // checking that the node has been properly added
    
    assert(m.erase("hulkenberg"));              // test Map::erase; this unlinks and deletes the "hulkenberg" node
    assert(m.size() == 4);                      // checking that size has been updated accordingly
    assert(!m.contains("hulkenberg"));          // checking that the node has been properly deleted
    
    assert(!m.erase("norris"));                 // test Map::erase; this returns false as key "norris" is not found in the Map
    
      // Test three parameter Map::get
    for (int i = 0; i < 4; i++) {
        KeyType driver;
        ValueType age;
        assert(m.get(i, driver, age));          // test three parameter Map::get returns true if driver key is found in the Map
        switch (i) {                            // this switch statement test what should be uniquely returned for each i value
            case 0:
                assert(driver == "hamilton" && age == 35.04);       // i == 0
                break;
            case 1:
                assert(driver == "ricciardo" && age == 30.57);      // i == 1
                break;
            case 2:
                assert(driver == "verstappen" && age == 22.32);     // i == 2
                break;
            case 3:
                assert(driver == "vettel" && age == 32.56);         // i == 3
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
            // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
        }
    }
    
    {
        KeyType driver = "this stays";
        ValueType age = -3.14159;
        int i = 4;
        assert(m.size() == 4);      // checking Map has a size of 4; in the three parameter get, only values of i 0<= i < size() are valid input
        assert(!m.get(i, driver, age) && driver == "this stays" && age == -3.14159);    // test three parameter Map::get should return true and not change values of driver and age
    }
    
      // Test Map::swap
    Map m2;  // maps std::strings to doubles
    assert(m2.insert("sainz", 29.4));
    assert(m2.insertOrUpdate("norris", 20.2));
    assert(m2.size() == 2);
    
    m.swap(m2);     // swaps m and m2
    
    assert(m.contains("sainz") && m.contains("norris"));            // check that m now contains keys of "sainz" and "norris"
    assert(!m.contains("hamilton") && !m.contains("ricciardo")
           && !m.contains("verstappen") && !m.contains("vettel"));  // check that m no longer contains keys of "hamilton", "ricciardo", "verstappen" and "vettel"
    
    ValueType crlAge = -3.14159;
    assert(m.get("sainz", crlAge) && crlAge == 29.4);               // check that the value for "sainz" has been swapped correctly
    ValueType lndAge = -3.14159;
    assert(m.get("norris", lndAge) && lndAge == 20.2);              // check that the value for "norris" has been swapped correctly
    ValueType lewAge = -3.14159;
    assert(!m.get("hamilton", lewAge) && lewAge == -3.14159);       // Map::get should return false, as "hamilton" no longer exists in m, and subsequently, lewAge shouldn't change
    
    assert(m2.contains("hamilton") && m2.contains("ricciardo")
           && m2.contains("verstappen") && m2.contains("vettel"));    // check that m2 now contains keys of "hamilton", "ricciardo", "verstappen" and "vettel"
    assert(!m2.contains("sainz") && !m2.contains("norris"));          // check that m2 no longer contains keys of "sainz" and "norris"
    
    for (int i = 0; i < 4; i++) {                                   // use for loop and switch statement to check all keys have had their paired values swapped correctly
        KeyType driver;
        ValueType age;
        assert(m2.get(i, driver, age));
        switch (i) {
            case 0:
                assert(driver == "hamilton" && age == 35.04);       // i == 0
                break;
            case 1:
                assert(driver == "ricciardo" && age == 30.57);      // i == 1
                break;
            case 2:
                assert(driver == "verstappen" && age == 22.32);     // i == 2
                break;
            case 3:
                assert(driver == "vettel" && age == 32.56);         // i == 3
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
            // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
        }
    }
    
      // Test copy constructor
    Map copyOfM2(m2);
    assert(copyOfM2.contains("hamilton") && copyOfM2.contains("ricciardo")
    && copyOfM2.contains("verstappen") && copyOfM2.contains("vettel"));         // check that copyOfM2 has all the keys from m2
    assert(copyOfM2.size() == m2.size());                                       // check that copyOfM2 has the same size as m2
    
    assert(copyOfM2.erase("vettel"));                                           // erase "vettel" node from m2
    assert(!copyOfM2.contains("vettel") && m2.contains("vettel"));              // check that "vettel" was removed from copyOfM2, but not from m2 (then copyOfM2 is a true copy)
    
      // Test copy constructor with empty Map
    Map anEmptyMap;                                                             // default constructor creates an empty Map
    assert(anEmptyMap.empty());                                                 // reconfirming anEmptyMap is empty
    Map anotherEmptyMap(anEmptyMap);                                            // copying anEmptyMap to anotherEmptyMap
    assert(anotherEmptyMap.empty());                                            // checking that anotherEmptyMap is indeed empty
    
      // Test assignment operator
    Map m3;
    assert(m3.empty());
    assert(m3.insert("bottas", 30.41));
    
    m3 = m;                                                      // assign m to m3
    assert(!m3.contains("bottas")
           && m3.contains("sainz") && m3.contains("norris"));    // check that previous values of m3 have been deleted and deallocated, and that it has been assigned m's key-value pairs
    assert(m3.erase("norris"));                                  // erase "norris" node from m3
    assert(!m3.contains("norris") && m.contains("norris"));      // check that "norris" was removed from m3, but not from m (then assignment has occurred properly)
    
      // Test assignment operator with empty Map
    Map emptyM;                                                  // default constructor creates an empty Map
    assert(emptyM.empty());                                      // reconfirming emptyM is empty
    Map thisShouldBeEmpty = emptyM;                              // assigning emptyM to thisShouldBeEmpty
    assert(thisShouldBeEmpty.empty());                           // checking that thisShouldBeEmpty is indeed empty
    
    
    
    
    
    
    //////////////////////////////////////////////////////
    // Test combine function
    //////////////////////////////////////////////////////
    // in these tests, m = { "sainz" : 29.4, "norris" : 20.2}
    //   and m2 = { "hamilton" : 35.04, "ricciardo" : 30.57, "verstappen" : 22.32, "vettel" : 32.56}
    
      // Test normal functionality
    Map m12;                                                            // creating empty Map
    assert(m12.empty());
    assert(combine(m, m2, m12));                                        // combining m & m2; will return true as no duplicate keys with mistmatched values
    assert(m12.size() == 6);                                            // checking that m12 has 6 key-value pairs; 2 from m and 4 from m2
    assert(m12.contains("sainz") && m12.contains("norris")
           && m12.contains("hamilton") && m12.contains("ricciardo")
           && m12.contains("verstappen") && m12.contains("vettel"));    // checking that m12 contains all of the keys from m and m2
    for (int i = 0; i < 6; i++) {                                       // use for loop and switch statement to check all combined keys have correct values
        KeyType driver;
        ValueType age;
        assert(m12.get(i, driver, age));
        switch (i) {
            case 0:
                assert(driver == "sainz" && age == 29.4);        // i == 0
                break;
            case 1:
                assert(driver == "norris" && age == 20.2);        // i == 1
                break;
            case 2:
                assert(driver == "hamilton" && age == 35.04);     // i == 2
                break;
            case 3:
                assert(driver == "ricciardo" && age == 30.57);    // i == 3
                break;
            case 4:
                assert(driver == "verstappen" && age == 22.32);   // i == 4
                break;
            case 5:
                assert(driver == "vettel" && age == 32.56);       // i == 5
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
            // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
        }
    }
    
      // Test functionality when given duplicate keys with matched values (returns true in this case)
    Map m9;                                                             // creating an empty Map
    assert(m9.empty());
    assert(m9.insert("norris", 20.2) && m9.insert("bottas", 30.41)
           && m9.insert("raikkonen", 40.27));                           // adding items to m9
    Map m19;                                                            // creating another empty Map to store combine result
    assert(combine(m, m9, m19));                                        // combining m & m9; will return true as although duplicate keys present, values are identical
    assert(m19.size() == 4);                                            // checking that m19 has all keys from m and m9, but hasn't made a new "norris" key
    assert(m19.contains("sainz") && m19.contains("norris")
           && m19.contains("bottas") && m19.contains("raikkonen"));     // checking that m19 contains all of the keys from m and m9
    for (int i = 0; i < 4; i++) {                                       // use for loop and switch statement to check all combined keys have correct values
        KeyType driver;
        ValueType age;
        assert(m19.get(i, driver, age));
        switch (i) {
            case 0:
                assert(driver == "sainz" && age == 29.4);        // i == 0
                break;
            case 1:
                assert(driver == "norris" && age == 20.2);       // i == 1
                break;
            case 2:
                assert(driver == "bottas" && age == 30.41);      // i == 2
                break;
            case 3:
                assert(driver == "raikkonen" && age == 40.27);   // i == 3
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
            // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
        }
    }
    
      // Test functionality when given duplicate keys with mismatched values (returns false in this case)
    Map m4;                                                                         // creating an empty map
    assert(m4.insert("hamilton", 29.33) && m4.insert("ricciardo", 30.57)
           && m4.insert("verstappen", 22.32) && m4.insert("vettel", 32.56));        // m4 differs from m2 for the "hamilton" key, which has a different value than the same key does in m2
    Map m24;                                                                        // creating another empty Map to store combine result
    assert(!combine(m2, m4, m24));                                                  // combining m2 & m4; will return false as duplicate keys with mismatched values present
    assert(m24.size() == 3);                                                        // size of m24 will be 3, because the "hamilton" key will be removed
    assert(!m24.contains("hamilton") && m24.contains("ricciardo")
           && m24.contains("verstappen") && m24.contains("vettel"));                // checking that m24 contains the 3 other keys, in addition to not having the "hamilton" key
    for (int i = 0; i < 3; i++) {                                                   // use for loop and switch statement to check all combined keys have correct values
        KeyType driver;
        ValueType age;
        assert(m24.get(i, driver, age));
        switch (i) {
            case 0:
                assert(driver == "ricciardo" && age == 30.57);    // i == 0
                break;
            case 1:
                assert(driver == "verstappen" && age == 22.32);   // i == 1
                break;
            case 2:
                assert(driver == "vettel" && age == 32.56);       // i == 2
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
            // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
        }
    }
    
      // Test aliasing solution; combine is passed the same Map for all three parameters
    // In this case, the result will be identical to the Map that was passed, and combine will return true (as the duplicate keys with identical values are put into the result Map)
    assert(combine(m2, m2, m2));                                        // combine returns true, because m2 & m2 have technically been combined
                                                                        //          (the result is just identical to m2; in fact, due to this fact, the Maps haven't been processed at all)
    assert(m2.contains("hamilton") && m2.contains("ricciardo")
           && m2.contains("verstappen") && m2.contains("vettel"));      // check that m2 still contains keys of "hamilton", "ricciardo", "verstappen" and "vettel"
    
    for (int i = 0; i < 4; i++) {                                       // use for loop and switch statement to check all keys still have correct values
        KeyType driver;
        ValueType age;
        assert(m2.get(i, driver, age));
        switch (i) {
            case 0:
                assert(driver == "hamilton" && age == 35.04);       // i == 0
                break;
            case 1:
                assert(driver == "ricciardo" && age == 30.57);      // i == 1
                break;
            case 2:
                assert(driver == "verstappen" && age == 22.32);     // i == 2
                break;
            case 3:
                assert(driver == "vettel" && age == 32.56);         // i == 3
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
            // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
        }
    }
    
      // Test aliasing solution; the first two parameters of combine are passed the same Map
    // In this case, the result will be identical to the Map that was passed
    Map m22;                                                            // creating new Map to store combine result
    assert(combine(m2, m2, m22));                                       // combine returns true, because m2 & m2 have technically been combined (the result is just identical to m2)
    assert(m22.contains("hamilton") && m22.contains("ricciardo")
           && m22.contains("verstappen") && m22.contains("vettel"));    // check that m2 still contains keys of "hamilton", "ricciardo", "verstappen" and "vettel"
    
    for (int i = 0; i < 4; i++) {                                       // use for loop and switch statement to check all keys still have correct values
        KeyType driver;
        ValueType age;
        assert(m22.get(i, driver, age));
        switch (i) {
            case 0:
                assert(driver == "hamilton" && age == 35.04);       // i == 0
                break;
            case 1:
                assert(driver == "ricciardo" && age == 30.57);      // i == 1
                break;
            case 2:
                assert(driver == "verstappen" && age == 22.32);     // i == 2
                break;
            case 3:
                assert(driver == "vettel" && age == 32.56);         // i == 3
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
            // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
        }
    }
    
      // Test aliasing solution; the first and third parameters, or second and third parameters, of combine are passed the same Map
    // In this case, the function acts as normal; the result is correctly stored in the duplicate Map passed
    assert(m.size() == 2);                                              // we see that before calling combine, m has size of 2
    assert(combine(m, m2, m));                                          // combine will return true, as there are no duplicate mismatched values
    assert(m.size() == 6);                                              // we see that after calling combine, m has size of 6
    assert(m.contains("sainz") && m.contains("norris")
           && m.contains("hamilton") && m.contains("ricciardo")
           && m.contains("verstappen") && m.contains("vettel"));        // checking that m contains all of the keys from m and m2
    for (int i = 0; i < 6; i++) {                                       // use for loop and switch statement to check all combined keys have correct values
        KeyType driver;
        ValueType age;
        assert(m.get(i, driver, age));
        switch (i) {
            case 0:
                assert(driver == "sainz" && age == 29.4);        // i == 0
                break;
            case 1:
                assert(driver == "norris" && age == 20.2);        // i == 1
                break;
            case 2:
                assert(driver == "hamilton" && age == 35.04);     // i == 2
                break;
            case 3:
                assert(driver == "ricciardo" && age == 30.57);    // i == 3
                break;
            case 4:
                assert(driver == "verstappen" && age == 22.32);   // i == 4
                break;
            case 5:
                assert(driver == "vettel" && age == 32.56);       // i == 5
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
                // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
        }
    }
    
    assert(m9.size() == 3);                                                 // before calling combine, m9 has size of 3
    assert(m9.insert("hamilton", 27.98));                                   // we'll insert a "hamilton" key in m9
                                                                            // (with the value mismatched to "hamilton" in m) to show that this value will still be removed in combine
    assert(m9.contains("norris") && m9.contains("bottas")
           && m9.contains("raikkonen") && m9.contains("hamilton")
           && !m9.contains("sainz") &&!m9.contains("ricciardo")
           && !m9.contains("verstappen") && !m9.contains("vettel"));        // m9 currently only contains "norris", "bottas", "raikkonen" and "hamilton"
    assert(!combine(m, m9, m9));                                            // combine will return false, as there is one mismatched key-value pair
    assert(m9.size() == 7);                                                 // checking m9 now has size 6
    assert(m9.contains("norris") && m9.contains("bottas")
           && m9.contains("raikkonen") && !m9.contains("hamilton")
           && m9.contains("sainz") &&m9.contains("ricciardo")
           && m9.contains("verstappen") && m9.contains("vettel"));          // m9 will now contain "norris", "bottas", "raikkonen", "ricciardo", "verstappen" and "vettel";
                                                                            // it will not contain "hamilton" due to mismatched values
    for (int i = 0; i < 7; i++) {                                           // use for loop and switch statement to check all combined keys have correct values
        KeyType driver;
        ValueType age;
        assert(m9.get(i, driver, age));
        switch (i) {
            case 0:
                assert(driver == "sainz" && age == 29.4);
                break;                                            // i == 0
            case 1:
                assert(driver == "norris" && age == 20.2);        // i == 1
                break;
            case 2:
                assert(driver == "ricciardo" && age == 30.57);    // i == 2
                break;
            case 3:
                assert(driver == "verstappen" && age == 22.32);   // i == 3
                break;
            case 4:
                assert(driver == "vettel" && age == 32.56);       // i == 4
                break;
            case 5:
                assert(driver == "bottas" && age == 30.41);       // i == 5
                break;
            case 6:
                assert(driver == "raikkonen" && age == 40.27);    // i == 6
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
                // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function, and the algorithm of combine
        }
    }
    
    //////////////////////////////////////////////////////
    // Test reassign function
    //////////////////////////////////////////////////////
    // in these tests, we'll redefine m and m2 from previous tests for the purpose of clarity
    //      m = { "hamilton" : 35.04, "ricciardo" : 30.57, "verstappen" : 22.32, "vettel" : 32.56 }
    //    & m2 = { "norris" : 20.2, "sainz" : 29.4, "bottas" : 30.41 }
    Map emptyMap;
    m = emptyMap;
    m2 = emptyMap;
    assert(m.empty() && m2.empty());                                            // emptying m & m2 so we can redefine them
    assert(m.insert("hamilton", 35.04) && m.insert("ricciardo", 30.57)
           && m.insert("verstappen", 22.32) && m.insert("vettel", 32.56));      // insert our items
    assert(m2.insert("norris", 20.2) && m2.insert("sainz", 29.4)
           && m2.insert("bottas", 30.41));                                      // insert our items
    
      // Testing normal functionality of reassign
    Map newM;
    reassign(m, newM);                                                          // reassign the values of the items in a 4 node linked list
    for (int i = 0; i < 4; i++) {                                               // use for loop and switch statement to check that the values have been reassigned to different keys
        KeyType driver;
        ValueType newAge;
        assert(newM.get(i, driver, newAge));
        switch (i) {
            case 0:
                assert(driver == "hamilton" && newAge == 30.57);    // i == 0
                break;
            case 1:
                assert(driver == "ricciardo" && newAge == 35.04);   // i == 1
                break;
            case 2:
                assert(driver == "verstappen" && newAge == 32.56);  // i == 2
                break;
            case 3:
                assert(driver == "vettel" && newAge == 22.32);      // i == 3
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
                // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
                // we also know where each value was reassigned to due to the algorithm of reassign
        }
    }
    
    Map newM2;
    reassign(m2, newM2);                                         // reassign the values of the items in a 3 node linked list
    for (int i = 0; i < 3; i++) {                                // use for loop and switch statement to check that the values have been reassigned to different keys
        KeyType driver;
        ValueType newAge;
        assert(newM2.get(i, driver, newAge));
        switch (i) {
            case 0:
                assert(driver == "norris" && newAge == 30.41);  // i == 0
                break;
            case 1:
                assert(driver == "sainz" && newAge == 20.2);    // i == 1
                break;
            case 2:
                assert(driver == "bottas" && newAge == 29.4);   // i == 2
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
                // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
                // we also know where each value was reassigned to due to the algorithm of reassign
        }
    }
    
      // Test if the Map passed to reassign as 'result' was not empty, would it follow spec rules
    Map notEmptyMap(m2);                                    // creating a new Map, copied from m2 so that there are values in it
    reassign(m, m2);
    assert(m2.size() == 4);                                 // there should be only 4 nodes in this map
    for (int i = 0; i < 4; i++) {                           // use for loop and switch statement to check that it is the correct key-value pairs in the Map,
                                                            // and that they've been reassigned properly
        KeyType driver;
        ValueType newAge;
        assert(newM.get(i, driver, newAge));
        switch (i) {
            case 0:
                assert(driver == "hamilton" && newAge == 30.57);    // i == 0
                break;
            case 1:
                assert(driver == "ricciardo" && newAge == 35.04);   // i == 1
                break;
            case 2:
                assert(driver == "verstappen" && newAge == 32.56);  // i == 2
                break;
            case 3:
                assert(driver == "vettel" && newAge == 22.32);      // i == 3
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
                // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
                // we also know where each value was reassigned to due to the algorithm of reassign
        }
    }
    
      // Test aliasing solution; if reassign is passed the same Map twice, we reassign the Map and store it back into the same Map
    reassign(m, m);
    for (int i = 0; i < 4; i++) {                 // use for loop and switch statement to check that the values have been reassigned properly despite the aliasing issue
        KeyType driver;
        ValueType newAge;
        assert(newM.get(i, driver, newAge));
        switch (i) {
            case 0:
                assert(driver == "hamilton" && newAge == 30.57);    // i == 0
                break;
            case 1:
                assert(driver == "ricciardo" && newAge == 35.04);   // i == 1
                break;
            case 2:
                assert(driver == "verstappen" && newAge == 32.56);  // i == 2
                break;
            case 3:
                assert(driver == "vettel" && newAge == 22.32);      // i == 3
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
                // note that each value of i is known to correspond to each key-value pair due to the implementation of the Map::insert function
                // we also know where each value was reassigned to due to the algorithm of reassign
        }
    }
    
    cerr << "Passed all tests!" << endl;
}


/* TESTING INT TO STD:: STRING *//*
int main() {
    
    Map m;      // default constructor; maps ints to std::strings
    assert(m.empty());                                                  // Map should by default be empty
    assert(m.size() == 0);                                              // Map should have no interesting nodes
    KeyType hmanNum = 44;                                               // testing KeyType is int
    ValueType champ = "hamilton";                                       // testing ValueType is std::string
    assert(m.insert(hmanNum, champ) && m.insert(3, "ricciardo"));       // inserting with KeyType == int and ValueType == std::string
    assert(m.size() == 2);                                              // size should be 2
    
    assert(m.insert(33, "norris"));                                     // inserting a key for updating
    assert(m.update(33, "verstappen"));                                 // updating key
    assert(!m.update(77, "bottas"));                                    // trying to update non-existent key --> returns false
    
    assert(m.insertOrUpdate(5, "raikkonen"));                           // inserting a new key using insertOrUpdate
    assert(m.size() == 4);                                              // size == 4 now that an insertion has happened
    assert(m.insertOrUpdate(5, "vettel"));                              // updating a new key using insertOrUpdate
    
    assert(m.contains(33) && m.contains(3) && m.contains(33)            // checking contain works
           && m.contains(5));

    assert(m.insertOrUpdate(27, "hulkenberg"));                         // inserting new key-value pair for erasing
    assert(m.contains(27));                                             // checking that it is present
    assert(m.size() == 5);                                              // so size == 5
    assert(m.erase(27));                                                // erasing the key-value pair
    assert(!m.contains(27));                                            // Map no longer contains key 27
    assert(m.size() == 4);                                              // so size == 4
    
    ValueType MV33;
    assert(m.get(33, MV33) && MV33 == "verstappen");                    // testing get function returns appropriate value
    assert(!m.get(27, MV33) && MV33 == "verstappen");                   // testing get function does not update MV33 if key 27 cannot be found
    
    for (int i = 0; i < 4; i++) {                                       // using for loop and switch statement to test three parameter get function
        KeyType carNum;
        ValueType driver;
        assert(m.get(i, carNum, driver));
        switch (i) {
            case 0:
                assert(carNum == 44 && driver == "hamilton");
                break;
            case 1:
                assert(carNum == 3 && driver == "ricciardo");
                break;
            case 2:
                assert(carNum == 33 && driver == "verstappen");
                break;
            case 3:
                assert(carNum == 5 && driver == "vettel");
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
        }
    }
    
    Map m2;                                                             // creating new Map for swapping test
    assert(m2.insert(4, "norris") && m2.insert(55, "sainz"));
    assert(m2.size() == 2);
    
    m.swap(m2);                                                         // swapping Maps
    
    assert(m.contains(4) && m.contains(55));                            // m now has m2's values
    assert(m.size() == 2);                                              // m has correct size
    assert(m2.contains(44) && m2.contains(3)
           && m2.contains(33) && m2.contains(5));                       // m2 now has m's values
    assert(m2.size() == 4);                                             // m2 has appropriate size
}
*/
    
/* DEVELOPMENT TESTING */
int main2() {
    Map m;  // maps strings to doubles
    assert(m.empty());
    m.dump();
    
    KeyType champ = "hamilton";
    ValueType carNum = 44.0;
    
    assert(m.insert(champ, carNum));
    assert(m.insert("ricciardo", 3));
    assert(!m.insert("ricciardo", 821.321));
    assert(m.size() == 2);
    
    assert(m.insert("verstappen", 3));
    assert(m.update("verstappen", 33));
    assert(!m.update("vettel", 5));
    assert(m.size() == 3);
    
    assert(m.insertOrUpdate("vettel", 1));
    assert(m.size() == 4);
    assert(m.insertOrUpdate("vettel", 5));
    assert(m.size() == 4);
    assert(m.insert("hulkenberg", 27));
    
    m.dump();
    
    assert(m.erase("hulkenberg"));
    assert(!m.erase("ocon"));
    assert(m.size() == 4);
    
    assert(!m.contains("hulkenberg"));
    assert(m.contains("vettel"));
    
    m.dump();
    
    double danniRicNum = -99.321;
    assert(m.get("ricciardo", danniRicNum));
    assert(danniRicNum == 3);
    assert(!m.get("hulkenberg", danniRicNum));
    assert(danniRicNum == 3);
    
    assert(!m.get(-1, champ, carNum));
    assert(champ == "hamilton" && carNum == 44.0);
    assert(!m.get(5, champ, carNum));
    assert(champ == "hamilton" && carNum == 44.0);
    
    for (int i = 0; i < 4; i++) {
        KeyType driver;
        ValueType carNo;
        assert(m.get(i, driver, carNo));
        switch (i) {
            case 0:
                assert(driver == "hamilton" && carNo == 44);
                cerr << driver << ": " << carNo << endl;
                break;
            case 1:
                assert(driver == "ricciardo" && carNo == 3);
                cerr << driver << ": " << carNo << endl;
                break;
            case 2:
                assert(driver == "verstappen" && carNo == 33);
                cerr << driver << ": " << carNo << endl;
                break;
            case 3:
                assert(driver == "vettel" && carNo == 5);
                cerr << driver << ": " << carNo << endl;
                break;
            default:
                cerr << "shouldn't happen\n";
                break;
        }
    }
    
    Map m2;  // maps strings to doubles
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
    
    Map m3(m2);
    m2.erase("hamilton");
    m2.dump();
    m3.dump();
    
    Map m4;
    m4.insert("mitchell", 44);
    m4.insert("alicia", 45);
    m4.insert("hman", 40);

    m4.dump();
    
    m4 = m3;
    
    m4.dump();
    
    //////////////////////////////////////////////////////////////
    // Other function testing
    /////////////////////////////////////////////////////////////
    Map m99;
    m99.insert("sainz", 55);
    m99.insert("norris", 4);
    m99.insert("hulkenberg", 27);
    
    m2.insert("mitchell", 44);
    
    assert(combine(m, m2, m99));
    
    m99.dump();
    
    m4.dump();
    reassign(m4, m99);
    m99.dump();
    
    Map m88;
    m88.insert("bottas", 77);
    m88.insert("raikkonen", 7);
    m88.insert("giovinazzi", 99);
    
    m88.dump();
    
    reassign(m88, m99);
    
    m99.dump();
    
    // aliasing test for combine
    m4.dump();
    m.dump();
    m.insert("hamilton", 69);
    combine(m4, m, m4);
    
    m4.dump();
    
    // aliasing test for reassign
    m2.dump();
    reassign(m2, m2);
    m2.dump();
    
    m88.dump();
    reassign(m88, m88); //three-element test
    m88.dump();
    
    Map m77;
    m77.insertOrUpdate("leclerc", 16);
    m77.dump();
    reassign(m77, m77);
    m77.dump();
    
    
    
    
    cerr << "Passed all tests! Check dumps have expected values.\n";
    return 0;
}
