# CSCI 389 HW3: Testy cache
Mason Koch and Sebastian Simmons

## Usage instructions
Make the project using make.

./test_cache_lib  
./test_fifo  
./test_lru_evictor  
## Tests - Our Cache
We did not write tests that test the hasher or max_load_factor constructor parameters as that would test the internal structure of the cache object. This makes it hard to test it in a meaningful way.

|Name|Description|Status|
|----|-----------|------|
|test_get|tests the retrieval of a stored object in cache|FAIL|
|test_del|tests deleting an object from the cache|pass|
|test_space_used|tests that the space used returns the proper value when objects are added to cache|pass|
|test_reset|tests that reset properly resets the cache|pass|
|test_fifo_evictor|tests the FIFO evictor for proper deletion order|pass|
|test_lru_evictor_basic|tests the LRU evictor for deletion correctness|pass|

## Part 2 - Danny + Hannah
|Name|Description|Status|
|----|-----------|------|
|test_get|tests the retrieval of a stored object in cache|pass|
|test_del|tests deleting an object from the cache|pass|
|test_space_used|tests that the space used returns the proper value when objects are added to cache|FAIL|
|test_reset|tests that reset properly resets the cache|pass|
|test_fifo_evictor|tests the FIFO evictor for proper deletion order|pass|
|test_lru_evictor_basic|tests the LRU evictor for deletion correctness|pass|
