//
//  main.c
//  Simple C Hash Table - test routine
//
//  Test routine
//
//  Created by Blake Caldwell on 11/18/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include "hashtable.h"

int main(int argc, const char * argv[])
{
    struct hashTable *ht;
    char *value;
    
    createHashTable(10, &ht);
    
    printf("Adding 'hello'=>'world', 'color'=>'blue' and printing:\n-----\n");
    
    // add "hello" => "world", and verify
    assert(!valueForKeyInHashTable(ht, "hello", &value));
    assert(NULL == value);
    assert(addToHashTable(ht, "hello", "world"));   // do it once,
    assert(addToHashTable(ht, "hello", "world"));   // then again, for good measure
    assert(valueForKeyInHashTable(ht, "hello", &value));
    assert(0 == strcmp("world", value));
    
    // add "color" => "blue", and verify
    assert(!valueForKeyInHashTable(ht, "color", &value));
    assert(NULL == value);
    assert(addToHashTable(ht, "color", "blue"));
    assert(valueForKeyInHashTable(ht, "color", &value));
    assert(0 == strcmp("blue", value));
    
    
    // print all the values we've added
    assert(printAllKeysAndValues(ht));
    
    
    printf("\n\nChanging 'hello' value to 'goodbye', then printing:\n-----\n");
    
    // change "hello"'s value to "goodbye"
    assert(addToHashTable(ht, "hello", "goodbye"));   // do it once,
    assert(valueForKeyInHashTable(ht, "hello", &value));
    assert(0 == strcmp("goodbye", value));
    
    
    // print all the values we've added
    assert(printAllKeysAndValues(ht));
    
    // --
    // now remove and print
    
    printf("\n\nRemoving 'hello' and printing:\n-----\n");
    assert(removeFromHashTable(ht, "hello"));
    assert(printAllKeysAndValues(ht));
    
    printf("\n\nRemoving 'color' and printing:\n-----\n");
    assert(removeFromHashTable(ht, "color"));
    assert(printAllKeysAndValues(ht));
    
    
    // clean up
    destroyHashTable(&ht);
    assert(NULL == ht);
}
