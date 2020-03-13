# CSCI 389 HW3: Testy cache
Mason Koch and Sebastian Simmons

## Usage instructions
Make the project using make. This will take a while. To run the tests, append \_GITHUB_USERNAME with \_GITHUB_USERNAME in ["\_enderquestral", "\_kai_pinckard", "\_zhengyaogu"] to your pick of

./test_cache_lib
./test_fifo
./test_lru

We didn't have to include this, but we did so anyway.

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
|test_get|tests the retrieval of a stored object in cache|pass|
|test_del|tests deleting an object from the cache|pass|
|test_space_used|tests that the space used returns the proper value when objects are added to cache|FAIL|
|test_reset|tests that reset properly resets the cache|FAIL|
|test_fifo_evictor|tests the FIFO evictor for proper deletion order|pass|
|test_lru_evictor_basic|tests the LRU evictor for deletion correctness|FAIL|

We had a compilation issue because their object file was output as lib_cache.o and our Makefile was looking for cache_lib.cc to make cache_lib.o. In their evictor headers we had to change the include to be "../evictor.hh", our version of the evictor header, so that the compiler didn't complain about the same object being defined in two different places. They also included evictor.hh in their lru_evictor.cc file so we had to remove that.

In space_used, the very first line is requiring that it uses no space. It returned 78, which is not desired behavior. They might have a bug in reset because

Reset also fails. That one adds three items to the cache, resets, and asserts the space used is 0. This again fails.

In test_lru_evictor_basic, one of our tests was to have two keys in our cache (we called them "key1" and "key2") and then to set "key1" to a different value. We asserted that the space used was equal to the size of key2's value and the size of key1's new value. Their space_used returned the size of both key1 and key2's old values plus the size of the new value. I talked to Eitan about this in lab and he said "that sounds like a bug".

## Part 2 - Albert + Yao
|Name|Description|Status|
|----|-----------|------|
|test_get|tests the retrieval of a stored object in cache|pass|
|test_del|tests deleting an object from the cache|pass|
|test_space_used|tests that the space used returns the proper value when objects are added to cache|FAIL|
|test_reset|tests that reset properly resets the cache|pass|
|test_fifo_evictor|tests the FIFO evictor for proper deletion order|pass|
|test_lru_evictor_basic|tests the LRU evictor for deletion correctness|FAIL|

We had to change the include of evictor.hh to use our version of the file because otherwise the compiler complained about the same object being defined in two different header files. 
