c-hashtable
===========

Simple hash table in C

Note: This is not intended for production use.


Details
-------

This [hash table](http://en.wikipedia.org/wiki/Hash_table) implementation allows you to specify how many "buckets" it will use. Each bucket is a linked list for simplicity. This could be extended to point to an array, which might provide a little better performance. Keys and values added are not copied, so it's up to the caller to manage those pointers.

Operations:  

- create - with specified number of buckets
- destroy - frees all allocated memory
- add/set a key/value
- remove a key/value
- retrieve value for a key


Demo
----

Compile and execute the binary to run the demo use case in main.c:

	gcc *.c
	./a.out
	
You should see:

	Adding 'hello'=>'world', 'color'=>'blue' and printing:
	-----
	hello -> world
	color -> blue
	
	
	Changing 'hello' value to 'goodbye', then printing:
	-----
	hello -> goodbye
	color -> blue
	
	
	Removing 'hello' and printing:
	-----
	color -> blue
	
	
	Removing 'color' and printing:
	-----
