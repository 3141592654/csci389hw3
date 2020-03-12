# CSCI 389 HW3: Testy cache
Mason Koch and Sebastian Simmons

## Usage instructions
Make the project using make.

./test_cache_lib  
./test_fifo  
./test_lru_evictor  
## Part 1 - Tests - Our Cache
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

When testing the lru_evictor, we had used Lru_evictor where as they used LRU_Evictor for their class name. This created a compilation issue when creating an lru_evcitor object. 

## Part 2 - Kai+Max
|Name|Description|Status|
|----|-----------|------|
|test_get|tests the retrieval of a stored object in cache|null|
|test_del|tests deleting an object from the cache|null|
|test_space_used|tests that the space used returns the proper value when objects are added to cache|null|
|test_reset|tests that reset properly resets the cache|null|
|test_fifo_evictor|tests the FIFO evictor for proper deletion order|null|
|test_lru_evictor_basic|tests the LRU evictor for deletion correctness|null|

We had a compilation issue because their object file was output as lib_cache.o and our Makefile was looking for cache_lib.cc to make cache_lib.o. We changed the include of 

## Part 2 - Albert + Yao
|Name|Description|Status|
|----|-----------|------|
|test_get|tests the retrieval of a stored object in cache|null|
|test_del|tests deleting an object from the cache|null|
|test_space_used|tests that the space used returns the proper value when objects are added to cache|null|
|test_reset|tests that reset properly resets the cache|null|
|test_fifo_evictor|tests the FIFO evictor for proper deletion order|null|
|test_lru_evictor_basic|tests the LRU evictor for deletion correctness|null|

We had to change the include of evictor.hh to use our version of the file because otherwise the compiler complained about the same object being defined in two different header files. 
