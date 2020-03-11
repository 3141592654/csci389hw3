# CSCI 389 HW3: Testy cache
Mason Koch and Sebastian Simmons

## Usage instructions
Make the project using make.

./test_cache_lib tests everything (not just cache_lib).

## Tests
We did not write tests that test the hasher or max_load_factor constructor parameters as that would test the internal structure of the cache object.

|Name|Description|Status|
|----|-----------|------|
|test_set|tests the retrieval of a stored object in cache|pass|
|test_del|tests deleting an object from the cache|pass|
|test_space_used|tests that the space used returns the proper value when objects are added to cache|pass|
|test_reset|tests that reset properly resets the cache|pass|
|test_fifo_evictor|tests the FIFO evictor for proper deletion order|pass|
|test_lru_evictor_basic|tests the LRU evictor for deletion correctness|pass
