# CSCI 389 HW2: Hash It Out
Mason Koch and Sebastian Simmons

## Usage instructions

Make the project using make.

./test_cache_lib tests everything (not just cache_lib).

## Style note

The header files used an indenation of 2 spaces. We used an indentation of 4. 

The cache compiles with an unused parameter warning in cache.get(). This is because our implementation does not need the val_size argument from the header file. We compiled without -Werror because the function otherwise does what it is supposed to do.

## Cache Design
We used two unordered maps, one for the hash table of pointers to the stored values and another to track the memory used by each item added to the cache. We used unordered_maps because they handle collisions, dynamic resizing based on a load factor and constant time access for us.

The unordered_map of values hashes keys to a shared_pointer to the value. This allows map.clear() to automatically handle the memory requested by the cache since a shared pointer will deallocate memory once no more pointers point to that object. The original idea was that if the end user kept a pointer to the value they had around and that pointer was deleted from the cache, it wouldn't change on them. Sadly this didn't happen.

Another unordered_map hashes the key the size of the stored value. This allows us to keep track of memory as items are added or deleted.

For set(), we check if the user's data is bigger than our cache's maxmem and tell them to jump in a lake if it is. Otherwise, we run a while loop that will evict until enough memory is free to add the new item. If there is no evictor object given, the cache does not accept new values.

## FIFO Evictor Design
We used a queue of keys to store which items were first in. 

touch_key(key) only changes the queue when an existing key is used to chance the value in the cache.

evict() pops and returns the oldest item in the queue.

## LRU Evictor Design

We implemented the LRU evictor using a linked list and hash map that maps keys to nodes in the linked list. This gives us constant time access into the linked list. Touch moves a node to the back of the linked list.

This LRU evictor uses a large number of runtime assertions to make sure it is working properly.
