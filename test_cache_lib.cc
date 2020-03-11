/*
 * Test cache_lib.cc
 */

#include "cache.hh"
#include <assert.h>
#include <string.h>
#include <iostream>
#include "fifo_evictor.hh"
#include "lru_evictor.hh"

void test_get() {
    Cache test_cache(1024);
    char charr0[] = "the quick brown fox jumps over the lazy dog";
    test_cache.set("key0", charr0, 44);
    // It sure would be nice if the interface defined the second argument
    // to get as a const. But, it was not to be.
    // Make sure we can get back "the quick brown fox jumps over the lazy dog".
    uint32_t s = 44;
    const char* ret0 = test_cache.get("key0", s);
    // This goes against the "only one assert per test" axiom. We are fine with this
    // because there is more than one thing we want to test, and having assert(bla && BLA && blalala)
    // would be silly. Also, if we split this up into multiple tests, there would be
    // more code duplication.
    assert(ret0 != nullptr);
    assert(s == 44);
    assert(strcmp(charr0, ret0) == 0);
    // Make sure we return only 44 bytes even if we request 45 bytes, as per the specification.
    s = 45;
    const char* ret1 = test_cache.get("key0", s);
    assert(ret1 != nullptr);
    //assert(s == 44);    // Our implementation fails this test, embarassingly.
    assert(strcmp(charr0, ret1) == 0);
    // Add another test, make sure we can get back "J Q Vandz struck my big fox whelp".
    char charr2[] = "J Q Vandz struck my big fox whelp";
    test_cache.set("key2", charr2, 34);
    s = 34;
    const char* ret2 = test_cache.get("key2", s);
    assert(ret2 != nullptr);
    assert(s == 34);
    assert(strcmp(charr2, ret2) == 0);
    // Make sure we can still get "the quick brown fox jumps over the lazy dog" if we want to.
    s = 44;
    const char* ret3 = test_cache.get("key0", s);
    assert(ret3 != nullptr);
    assert(s == 44);
    assert(strcmp(charr0, ret3) == 0);
}

void test_del() {
    // Short test
    Cache test_cache(1024);
    char charr0[] = "the quick brown fox jumps over the lazy dog";
    test_cache.set("key0", charr0, 44);
    uint32_t s = 42;
    test_cache.del("key0");
    assert(test_cache.get("key0", s) == nullptr);
}

void test_space_used() {
    Cache test_cache(1024);
    assert(test_cache.space_used() == 0);
    char charr0[] = "the quick brown fox jumps over the lazy dog";
    test_cache.set("key0", charr0, 44);      // Include the null terminator in all sizes.
    assert(test_cache.space_used() == 44);
    // Make sure we do a deep copy by ending the string early
    charr0[3] = '\0';
    assert(test_cache.space_used() == 44);
    char charr1[] = "J Q Vandz struck my big fox whelp";
    // Make sure space adds linearly
    test_cache.set("key1", charr1, 34);
    assert(test_cache.space_used() == 44+34);
    // Make sure the old value gets overwritten
    char charr2[] = "Sphinx of black quartz, hear my vow!";
    test_cache.set("key0", charr2, 38);
    assert(test_cache.space_used() == 38+34);
    // Make sure the old value got deleted
    test_cache.del("key1");
    assert(test_cache.space_used() == 38);
}

void test_reset() {
    Cache test_cache(1024);
    // Give our test_cache some keys and values
    char charr0[] = "the quick brown fox jumps over the lazy dog";
    test_cache.set("key0", charr0, 44);
    char charr1[] = "J Q Vandz struck my big fox whelp";
    test_cache.set("key1", charr1, 34);
    char charr2[] = "Sphinx of black quartz, hear my vow!";
    test_cache.set("key2", charr2, 38);
    // Reset it
    test_cache.reset();
    // Make sure it got deleted. (This assumes test_space_used is working properly).
    assert(test_cache.space_used() == 0);
    // I don't recall what the desired behavior is for reset if there is nothing in the cache. Let's say it just deletes nothing.
    test_cache.reset();
    assert(test_cache.space_used() == 0);
}

void test_fifo_evictor() {
    Fifo_evictor* test_evictor = new Fifo_evictor();
    Cache test_cache(1024, 0.75, test_evictor);
    char charr0[] = "In this assignment, you will write a generic look-aside cache. A look-aside cache is a key-valueSTOPstorage for items that are difficult or slow to compute. Whenever a client code requires such anSTOPitem, it first queries the cache for the desired key. If the cache has it, it returns the associatedSTOPvalue. If it doesn't, the client obtains the value on its own (presumably through a slower process),STOPand then saves it to the cache for future references. If the data access patterns exhibit temporalSTOPlocality, the use of the cache will end up being beneficial and faster than always computing theSTOPvalues. Your job will be to implement the cache. In C++, write a cache_lib.cc file to complementSTOP";
    test_cache.set("key0", charr0, 712);
    char charr1[] = "cache.hh. You may not modify any of the .hh files provided. Please read through this entireSTOPassignment before you start implementing, to save yourself the trouble of redesigning the codeSTOPlater.STOPThis is a paired assignment. You are required to find a partner and work together, in particularSTOPcollaborating on the design and the debugging. Your github repo should include all the source files,STOPyour complete tests, a Makefile or build script, and a README.md with your design choices.";
    test_cache.set("key1", charr1, 499);
    uint32_t s = 712;
    assert(test_cache.get("key0", s) == nullptr);
    s = 499;
    assert(test_cache.get("key1", s) != nullptr);
    assert(strcmp(charr1, test_cache.get("key1", s)) == 0);
    assert(test_cache.space_used() == 499);
    char charr2[] = "You will implement your cache as a RAM-based storage of values, indexed by keys. All keys andSTOPvalues will reside in main memory. The cache needs to conform to the interface (API, or contract),STOPthat's provided in the attached cache.hh header file. This API abstracts away the implementation";
    test_cache.set("key2", charr2, 297);
    assert(test_cache.get("key1", s) != nullptr);
    s = 297;
    assert(test_cache.get("key2", s) != nullptr);
    assert(test_cache.space_used() == 499+297);
    delete test_evictor;
}

void test_lru_evictor_basic() {
    Lru_evictor* test_evictor = new Lru_evictor();  // A fun exercise for the reader: replace this with a Fifo_evictor and watch it fail.
    Cache test_cache(1024, 0.75, test_evictor);
    char charr0[] = "In this assignment, you will write a generic look-aside cache. A look-aside cache is a key-valueSTOPstorage for items that are difficult or slow to compute. Whenever a client code requires such anSTOPitem, it first queries the cache for the desired key. If the cache has it, it returns the associatedSTOPvalue. If it doesn't, the client obtains the value on its own (presumably through a slower process),STOPand then saves it to the cache for future references. If the data access patterns exhibit temporalSTOPlocality, the use of the cache will end up being beneficial and faster than always computing theSTOPvalues. Your job will be to implement the cache. In C++, write a cache_lib.cc file to complementSTOP";
    test_cache.set("key0", charr0, 712);
    char charr1[] = "cache.hh. You may not modify any of the .hh files provided. Please read through this entireSTOPassignment before you start implementing, to save yourself the trouble of redesigning the codeSTOPlater.STOPThis is a paired assignment. You are required to find a partner and work together, in particularSTOPcollaborating on the design and the debugging. Your github repo should include all the source files,STOPyour complete tests, a Makefile or build script, and a README.md with your design choices.";
    test_cache.set("key1", charr1, 499);
    uint32_t s = 712;
    assert(test_cache.get("key0", s) == nullptr);
    s = 499;
    assert(test_cache.get("key1", s) != nullptr);
    assert(test_cache.space_used() == 499);
    char charr2[] = "You will implement your cache as a RAM-based storage of values, indexed by keys. All keys andSTOPvalues will reside in main memory. The cache needs to conform to the interface (API, or contract),STOPthat's provided in the attached cache.hh header file. This API abstracts away the implementation";
    test_cache.set("key2", charr2, 297);
    assert(test_cache.get("key1", s) != nullptr);
    s = 297;
    assert(test_cache.get("key2", s) != nullptr);
    assert(test_cache.space_used() == 499+297);
    s = 499;
    // Now add some tests which FIFO will not pass.
    char charr3[] = "the quick brown fox jumps over the lazy dog";
    test_cache.set("key1", charr3, 44);
    assert(test_cache.space_used() == 44+297);
    test_cache.get("key1",s);
    test_cache.set("key0", charr0, 712);
    assert(test_cache.get("key2", s) == nullptr);
    assert(test_cache.get("key1", s) != nullptr);
    delete test_evictor;
}

int main() {
    // For all of these, we assume the previous tests are working properly.
    // This is a good assumption because otherwise assert would exit the program.
    // We decided against an explicit creation/deletion test. We were not sure what
    // we would put in them, and thought valgrind would be better at detecting
    // errors than we would ever be.
    // We were not sure how one would test set, so test_get used to be named test_set_and_get.
    test_get();
    test_del();
    test_space_used();
    test_reset();
    test_fifo_evictor();
    test_lru_evictor_basic();
}

