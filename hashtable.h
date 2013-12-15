//
//  hashtable.h
//  Simple C Hash Table
//
//  Header
//
//  Simple Hash Table implementation with linked lists. Create a hashtable with a specified size, and:
//  - add key/value
//  - update key/value
//  - delete key
//  - print all key/values
//
//  Created by Blake Caldwell on 12/15/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#include <stdbool.h>

#ifndef Practice_MyHashTable_h
#define Practice_MyHashTable_h

// linked list
struct hLinkedList
{
    char *key;
    char *value;
    struct hLinkedList *next;
};

// hashtable
struct hashTable
{
    unsigned int size;
    struct hLinkedList **lists;
};

// create a hashtable - return 0 on failure
int createHashTable(unsigned int size, struct hashTable **hashTable);

// destroy a hashtable - return 0 on failure
int destroyHashTable(struct hashTable **ht);

// add a string to the hashtable - return 0 on failure
int addToHashTable(struct hashTable *hashTable, char *key, char *value);

// remove a string to the hashtable - return 0 on failure
int removeFromHashTable(struct hashTable *hashTable, char *key);

// return whether we found the key
int valueForKeyInHashTable(struct hashTable *hashTable, char *key, char **value);

// print all keys and values in a hashtable
int printAllKeysAndValues(struct hashTable *hashTable);

#endif
