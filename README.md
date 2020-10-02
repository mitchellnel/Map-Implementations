# Map-Implementations
This repository contains two implementations of a Map data structure: one as a dynamically allocated array, and the other as a linked list.
### Concepts:
* Maps
* Dynamically allocated arrays
* Linked Lists
* Type aliases
* Copy constructors and the assignment operator
* Aliasing issues

This project involves defining and implementing my own version of the abstract data type Map (in this case from std::string to double). The strings are the "keys" and the doubles the "values", with each key mapping to a value in a "key-value pair".

No two keys in the map are allowed to be the same, although two keys can map to the same value.

## Map implemented as a Dynamically Allocated Array
__(This actually occurs in newMap.h and newMap.cpp; map.h and map.cpp are implemented very basically using a static array of a pre-determined size)__
Various member functions were defined and implemented for this abstrat Map data type, and these function definitions (and a description of what they do) can be found in the [newMap.h](https://github.com/mitchellnel/Map-Implementations/blob/master/Map%20(as%20Dynamic%20Array)/Map/Map/newMap.h).

Additionally, since in this case, the compiler-generated destructor, copy constructor and assignment operator did not do the correct things, I also implemented my own version of these to do the correct thing (i.e. prevent memory leaks, actually create a new map in the case of the copy constructor, and create a separate map in the case of the assignment operator)

Something I could've done was not place a limit on the number of key-value pairs in the map, instead growing the dynamic array each time I wanted to insert an element beyond the original cap. However, there would be overhead associated with ensuring that all the data is saved, deleting the original array, and then creating a new one (especially if the size growth was only in small increments).

## Map implemented as a Linked List
This variation of the abstract Map data type implements it as a circular, doubly-linked list with a dummy node.

Similary to the previous variation, the compiler-generated destructor, copy constructor and assignment operator did not do the correct things. They would only delete the dummy node that is the "start-point" for the linked list, which would cause a memory leak as we lose access to the other nodes in the linked list (only accessable via pointers from the dummy node). As such, I implemented my own version of these to do the correct thing.

There is now no limit on the number of key-value pairs that can be in the Map, as it is very easy to grow linked lists.

Two additional, non-member functions, were also implemented to interact with the Map data type, combine() and reassign().

The combine(const Map& m1, const Map& m2, Map& result) function combined two Maps together in a single Map, result. If a key appeared exactly once in one of m1 or m2, the result contained that key-value pair. If a key appeared in both m1 and m2 with the same corresponding value in both, the result contained that key-value pair __once__. If a key appeared in both m1 and m2, with different corresponding values in both, the result did not contain that key-value pair, and the function returned false.

The reassign(const Map& m, Map& result) function reassigned each key-value pair's value to another key, with each key having to have a different value once the function had been carried out. 

For example, if m consists of the four pairs (in any order):

    “Fred” : 123		“Ethel” : 456		“Lucy” : 789		“Ricky” : 321
    
then, no matter what value it had before, result must end up as a map consisting of one of the following groups of four pairs (with the pairs in result being in any order you like):

    “Fred” : 456		“Ethel” : 123		“Lucy” : 321		“Ricky” : 789
    “Fred” : 456		“Ethel” : 789		“Lucy” : 321		“Ricky” : 123
    “Fred” : 456		“Ethel” : 321		“Lucy” : 123		“Ricky” : 789
    “Fred” : 789		“Ethel” : 123		“Lucy” : 321		“Ricky” : 456
    “Fred” : 789		“Ethel” : 321		“Lucy” : 456		“Ricky” : 123
    “Fred” : 789		“Ethel” : 321		“Lucy” : 456		“Ricky” : 123
    “Fred” : 321		“Ethel” : 123		“Lucy” : 456		“Ricky” : 789
    “Fred” : 321		“Ethel” : 789		“Lucy” : 123		“Ricky” : 456
    “Fred” : 321		“Ethel” : 789		“Lucy” : 456		“Ricky” : 123
but not, say, one of these:

	  “Fred” : 456		“Ethel” : 321		“Lucy” : 789		“Ricky” : 123
    (Lucy didn’t change partners)
	  “Fred” : 456		“Ethel : 321		“Lucy” : 321		“Ricky” : 123
    (both Ethel and Lucy ended up with Ricky’s original partner)
    
### Program Design
As said, this map uses a circular, doubly-linked list with a dummy node.

Here is an example of what an empty Map looks like:

<img src="https://user-images.githubusercontent.com/56947176/94903768-db0f8900-04cc-11eb-819c-7fe685b6583d.png">

Here is an example of what a Map with 3 elements looks like:

<img src="https://user-images.githubusercontent.com/56947176/94903784-df3ba680-04cc-11eb-97b4-d9cfcee06009.png">

Each Map has its own node object, which acts as the dummy node, and has both its next and prev pointers set to point to itself when the Map is constructed. Each Map also has an int variable to keep track of the number of interesting nodes currently in the Map.

Each list node has 3 member variables: an Item object (which itself has a KeyType data member and a ValuetType data member), and two node pointers, next and prev, which point to the next and previous nodes, respectively.

The nodes are in no particular order. Their order is merely dictated by the order the nodes are added to the Map.

### Pseudocode for Non-Trivial Algorithms
#### Copy Constructor
```
if the Map to be copied is empty
  just construct the Map like normal
else
  create a meaningful node linked to the dummy node and copy the values
  then repeatedly, until all the other Map’s items have been copied
    create new node and copy values
    link nodes to Map
  then establish circular nature of Map
```

#### Map::insert()
```
repeatedly, until the dummy node is reached
  if the key is already found in the Map
    return false
  else move to the next node
dynamically allocate a new node
add the node to the back of the list
add the data of the key-value pair to the node
increment the number of meaningful nodes in the Map
return true
```

#### Map::erase()
```
if the map is empty
  we can’t erase anything, return false
repeatedly, until the dummy node is reached
  if the key we’re trying to erase is found in the Map
    link up adjacent nodes to each other
    delete the node with the key we want to erase
    decrement the number of meaningful nodes in the Map
    return true
we didn’t find the key in any of the nodes so return false
````

#### Map::swap()
```
temporarily store address of first meaningful (head) node in m1
swap next pointers of dummy nodes in m1 and m2 (using above temp pointer)
swap prev pointers of head nodes in m1 and m2 (using above temp pointer)

temporarily store address of last meaningful (tail) node in m1
swap prev pointers of dummy nodes in m1 and m2 (using above temp pointer)
swap next pointers of tail nodes in m1 and m2 (using above temp pointer)

swap data member that stores number of meaningful nodes in the Map
```

#### combine()
```
create a Map to combine our items into

traverse through the first input Map
  add each of the nodes to the combined Map

traverse through the second input Map
  if the combined Map does not already contain the key-value pair
    add that key-value pair/node to the combined Map
  else, the key-value pair already exists in the combined Map
    if their values are the same
    continue with the traversal
    else
      erase that key-value pair from the combined Map

set the result Map to be the combined Map
if any values had to be erased, return false
else return true
```

#### reassign()
```
create a Map to hold our reassigned items

if the Map to reassign only has one meaningful nodes
  we can’t reassign anything, so result is just the Map
  return

traverse through the Map to be reassigned
  keep track of every (n)th even node, and every (n+1)th odd node
  get their data
  swap their values around, adding the new key-value pairs into the reassigned Map

if the Map had an odd number of nodes
  get the reassigned value of the first node
  get the data of the last node
  swap their values around
  add the last node into the reassigned Map

set the result Map to be the reassigned Map
```
