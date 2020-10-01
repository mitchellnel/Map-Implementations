# Map-Implementations
This repository contains two implementations of a Map data structure: one as a dynamically allocated array, and the other as a linked list.
### Concepts:
* Maps
* Dynamically allocated arrays
* Linked Lists
* Type aliases
* Copy constructors and the assignment operator

This project involves defining and implementing my own version of the abstract data type Map (in this case from std::string to double). The strings are the "keys" and the doubles the "values", with each key mapping to a value in a "key-value pair".

No two keys in the map are allowed to be the same, although two keys can map to the same value.

## Map implemented as a Dynamically Allocated Array
__(This actually occurs in newMap.h and newMap.cpp; map.h and map.cpp are implemented very basically using a static array of a pre-determined size)__
Various member functions were defined and implemented for this abstrat Map data type, and these function definitions (and a description of what they do) can be found in the [newMap.h](https://github.com/mitchellnel/Map-Implementations/blob/master/Map%20(as%20Dynamic%20Array)/Map/Map/newMap.h).

Additionally, since in this case, the compiler-generated destructor, copy constructor and did not do the correct things, I also implemented my own version of these to do the correct thing (i.e. prevent memory leaks, actually create a new map in the case of the copy constructor, and create a separate map in the case of the assignment operator)
