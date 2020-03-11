#include "cache.hh"
#include "evictor.hh"
#include "fifo_evictor.hh"
#include "lru_evictor.hh"
#include <iostream>
#include <assert.h> 
#include <cstring>

//CACHE TESTS
void test_set_normal_1() {

    unsigned test_size = 32; 
    Cache cache(4096, 0.75);
    cache.set("16", "hello", test_size);
    const char* test_val = cache.get("16", test_size);
    assert(test_val != nullptr); 
}

void test_set_normal_2() {

    unsigned test_size = 32; 
    Cache cache(4096, 0.75);
    cache.set("0", "hi", test_size);
    const char* set_test_val_1 = cache.get("0", test_size);
    assert(set_test_val_1 != nullptr);
}

void test_set_many() {

    unsigned test_size = 32; 
    Cache cache(4096, 0.75);
    cache.set("0", "hi", test_size);
    cache.set("1", "hi", test_size);
    cache.set("2", "hi", test_size);
    cache.set("3", "hi", test_size);
    cache.set("4", "hi", test_size);
    cache.set("5", "hi", test_size);
    cache.set("6", "hi", test_size);
    cache.set("7", "hi", test_size);
    cache.set("8", "hi", test_size);
    cache.set("9", "hi", test_size);
    cache.set("10", "hi", test_size);
    cache.set("11", "hi", test_size);
    cache.set("12", "hi", test_size);
    cache.set("13", "hi", test_size);
    cache.set("14", "hi", test_size);
    cache.set("15", "hi", test_size);
    cache.set("16", "hello", test_size);
    
    const char* test_val = cache.get("10", test_size);
    assert(strcmp(test_val,"hi") == 0);
}
void test_get_normal() {
    unsigned test_size = 32; 
    Cache cache(4096, 0.75);
    cache.set("16", "hi", test_size);
    const char* set_test_val_2 = cache.get("16", test_size);
    assert(strcmp(set_test_val_2, "hi") == 0);
}


void test_get_non_existent_key() {
    unsigned test_size = 32; 
    Cache cache(4096, 0.75);
    cache.set("16", "hi", test_size);
    const char* test_val = cache.get("17", test_size);
    assert(test_val == nullptr);
}

void test_del_normal_1() {
    unsigned test_size = 32; 
    Cache cache(4096, 0.75);
    cache.set("16", "hola", test_size);
    cache.del("16");
    const char* set_test_val_2 = cache.get("16", test_size);
    assert(set_test_val_2 == nullptr);
}

void test_del_key_that_isnt_there() {
    unsigned test_size = 32; 
    Cache cache(4096, 0.75);
    cache.set("16", "shalom", test_size);
    cache.del("15");
    const char* set_test_val_2 = cache.get("16", test_size);
    assert(strcmp(set_test_val_2,"shalom") == 0);
}
void test_get_sets_actual_size()
{
    unsigned test_size = 32;
    Cache cache(4096,0.75);
    cache.set("1", "three", test_size);
    cache.get("1", test_size);
    assert(test_size == 6);

}

//FIFO TESTS
void test_fifo_1() {
    FifoEvictor fifo_evictor;
    fifo_evictor.touch_key("0");
    key_type x = fifo_evictor.evict();
    assert(x == "0");

}

void test_fifo_2(){
    FifoEvictor fifo_evictor;
    fifo_evictor.touch_key("0");
    fifo_evictor.touch_key("1");
    fifo_evictor.touch_key("2");
    fifo_evictor.touch_key("0");
    fifo_evictor.touch_key("2");
    key_type x = fifo_evictor.evict();
    assert(x == "0");
}

void test_fifo_3(){
    FifoEvictor fifo_evictor;
    fifo_evictor.touch_key("0");
    fifo_evictor.touch_key("1");
    fifo_evictor.touch_key("2");
    fifo_evictor.touch_key("0");
    fifo_evictor.touch_key("2");
    key_type x = fifo_evictor.evict();
    key_type y = fifo_evictor.evict();
    assert(y == "1");
}

void test_fifo_4(){
    FifoEvictor fifo_evictor;
    fifo_evictor.touch_key("232");
    fifo_evictor.touch_key("111");
    fifo_evictor.touch_key("618");
    fifo_evictor.touch_key("9343");
    fifo_evictor.touch_key("21459");
    key_type x = fifo_evictor.evict();
    key_type y = fifo_evictor.evict();
    key_type z = fifo_evictor.evict();
    assert(z == "618");
}

//LRU TESTS
void test_lru_1() {
    LRUEvictor lru_evictor;
    lru_evictor.touch_key("0");
    key_type x = lru_evictor.evict();
    assert(x == "0");

}

void test_lru_2(){
    LRUEvictor lru_evictor;
    lru_evictor.touch_key("0");
    lru_evictor.touch_key("1");
    lru_evictor.touch_key("2");
    lru_evictor.touch_key("0");
    lru_evictor.touch_key("2");
    key_type x = lru_evictor.evict();
    assert(x == "1");
}

void big_test(){
    LRUEvictor lru_evictor;
    Cache cache(90, 0.75, &lru_evictor);
    unsigned test_size = 10;
    cache.set("0", "val0", test_size);
    cache.set("1", "val1", test_size);
    cache.set("2", "val2", test_size);
    cache.set("3", "val3", test_size);
    cache.set("4", "val4", test_size);
    cache.set("5", "val5", test_size);
    cache.set("6", "val6", test_size);
    cache.set("7", "val7", test_size);
    cache.set("8", "val8", test_size);
    cache.set("9", "val9", test_size);
    const char* test_val = cache.get("0", test_size);
    const char* test_val2 = cache.get("1", test_size);
    assert(test_val == nullptr);
    assert(strcmp(test_val2, "val1") == 0);
}

int main() {
    
    //set tests
    test_set_normal_1();
    test_set_normal_2();
    test_set_many();

    //get tests
    test_get_normal();
    test_get_non_existent_key();
    test_get_sets_actual_size();

    //del tests
    test_del_normal_1();
    test_del_key_that_isnt_there();

    //fifo tests
    test_fifo_1();
    test_fifo_2();
    test_fifo_3();
    test_fifo_4();

    //lru tests
    test_lru_1();
    test_lru_2();
    big_test();
    return 0;

}


