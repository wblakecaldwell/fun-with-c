//
//  MyHashTable.c
//  Simple C Hash Table
//
//  Created by Blake Caldwell on 12/15/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "hashtable.h"

// build the hash code for the input string
int hashCode(char *str)
{
    int hc;
    
    hc = 0;
    while('\0' != *str)
    {
        // for each character, multiply the current hashcode by 31 and add the character's ascii value
        // multiply by 31 is the same as left shift by 5 and subtract value
        hc = hc << 5;
        hc = hc - hc + *str;
        
        str++;
    }
    return(hc);
}

// create a hashtable - return 0 on failure
int createHashTable(unsigned int size, struct hashTable **hashTable)
{
    struct hashTable *ht;
    struct hLinkedList **lists;
    
    if(size <= 0)
    {
        // bad input
        return(0);
    }
    
    // create the hashtable
    if(!(ht = (struct hashTable*)malloc(sizeof(struct hashTable))))
    {
        *hashTable = NULL;
        return(0);
    }
    
    // create the linked lists
    if(!(lists = (struct hLinkedList**)malloc(sizeof(struct hLinkedList *) * size)))
    {
        free(ht);
        *hashTable = NULL;
        return(0);
    }
    
    ht->size = size;
    ht->lists = lists;
    
    *hashTable = ht;
    return(1);
}

// destroy a hashtable - return 0 on failure
int destroyHashTable(struct hashTable **ht)
{
    struct hashTable *hashTable;
    struct hLinkedList *list;
    struct hLinkedList *tempList;
    
    hashTable = *ht;
    if(NULL == hashTable)
    {
        return(1);
    }
    
    for(int i=0; i<hashTable->size; i++)
    {
        list = *(hashTable->lists + i);
        while(list)
        {
            // keep track of this list
            tempList = list;
            
            // advance for looping
            list = list->next;
            
            // clean
            free(tempList);
        }
    }
    free(hashTable->lists);
    free(hashTable);
    *ht = NULL;
    return(1);
}

// add a string to the hashtable - return 0 on failure
int addToHashTable(struct hashTable *hashTable, char *key, char *value)
{
    int hc;
    int offset;
    struct hLinkedList *list, *prev;
    
    // create hashcode
    hc = hashCode(key);
    
    // pick the linked list
    offset = hc % hashTable->size;
    list = *(hashTable->lists + offset);
    
    if(!list)
    {
        // this list doesn't exist yet - create it
        if(!(list = (struct hLinkedList *)malloc(sizeof(struct hLinkedList))))
        {
            // couldn't get the memory
            return(0);
        }
        *(hashTable->lists + offset) = list;
        
        list->key = key;
        list->value = value;
        list->next = NULL;
        return(1);
    }
    
    // walk the list
    prev = list;
    while(list)
    {
        if(0 == strcmp(list->key, key))
        {
            // already exists in the list - update the value
            list->value = value;
            return(1);
        }
        
        prev = list;
        list = list->next;
    }
    
    // string doesn't yet exist in hashtable - add it. prev is at the end
    if(!(list = (struct hLinkedList *)malloc(sizeof(struct hLinkedList))))
    {
        // couldn't get the memory
        return(0);
    }
    list->key = key;
    list->value = value;
    list->next = NULL;
    prev->next = list;
    
    return(1);
}

// remove a string to the hashtable - return 0 on failure
int removeFromHashTable(struct hashTable *hashTable, char *key)
{
    int hc;
    int offset;
    struct hLinkedList *list, *prev;
    
    if(!hashTable)
    {
        // invalid input
        return(0);
    }
    
    hc = hashCode(key);
    offset = hc % hashTable->size;
    
    if(!(list = *(hashTable->lists + offset)))
    {
        // string isn't in the hashtable, but who cares?
        return(1);
    }
    
    prev = NULL;
    while(list)
    {
        if(0 == strcmp(key, list->key))
        {
            // found it
            if(!prev)
            {
                // the string was the first in the list
                *(hashTable->lists + offset) = list->next;
            }
            else
            {
                // the string was found somewhere in the middle
                prev->next = list->next;
            }
            free(list);
            return(1);
        }
        prev = list;
        list = list->next;
    }
    return(1);
}

// return whether we found the key
int valueForKeyInHashTable(struct hashTable *hashTable, char *key, char **value)
{
    int hc;
    int offset;
    struct hLinkedList *list, *prev;
    
    // create hashcode
    hc = hashCode(key);
    
    // pick the linked list
    offset = hc % hashTable->size;
    list = *(hashTable->lists + offset);
    
    // walk the list
    prev = list;
    while(list)
    {
        if(0 == strcmp(list->key, key))
        {
            // found it!
            *value = list->value;
            return(1);
        }
        
        prev = list;
        list = list->next;
    }

    *value = NULL;
    return(0);
}

// print all keys and values in a hashtable
int printAllKeysAndValues(struct hashTable *hashTable)
{
    struct hLinkedList *list;
    
    if(NULL == hashTable)
    {
        return(0);
    }
    
    for(int i=0; i<hashTable->size; i++)
    {
        list = *(hashTable->lists + i);
        while(list)
        {
            printf("%s -> %s\n", list->key, list->value);
            list = list->next;
        }
    }
    
    return(1);
}
