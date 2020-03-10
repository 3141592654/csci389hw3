/*
 * Implementation for Cache class and various other things
 */

#include <functional>
#include <memory>
#include <iostream>
#include "cache.hh"

class Cache::Impl {
  public:
    Impl(Cache::size_type maxmem,
        float max_load_factor = 0.75, 
        Evictor* evictor = nullptr,
        Cache::hash_func hasher = std::hash<key_type>()): maxmem_(maxmem), max_load_factor_(max_load_factor), evictor_(evictor), hasher_(hasher), space_used_(0) {
        map_.max_load_factor(max_load_factor);
        size_map_.max_load_factor(max_load_factor);
    }
    ~Impl() {
        // Do nothing
    }
    void set(key_type key, Cache::val_type val, Cache::size_type size) {
        // Check for impossible requests
        if (size > maxmem_) {
            std::cerr << "The size of the array you have requested for '" 
                      << key << "', which is of " << size
                      << ", is greater than this cache's maxmimum memory. "
                      << "Such an array cannot be allocated.\n";
            return;
        }
        // See if we need to evict things from the cache
        if (size + space_used_ > maxmem_) {
            // EVICT THINGS FROM CACHE
            // Except we haven't implemented that yet, so
            return;
        }
        // Deep copy size objects starting at 0xval to somewhere on the heap
        std::shared_ptr<char[]> newValue(new char[size]);
        for(int i = 0; i < size; i++) {
            // Leave it up to the user to make sure this is legal.
            newValue[i] = val[i];
        }
        space_used_ += size;
        if (map_.count(key) == 1) {
            // Remove the space allocated to whatever used to be there
            space_used_ -= size_map_[key];
        }
        // Take pointer to val and hash key to said pointer
        map_[key] = newValue;
        size_map_[key] = size;
    }
    Cache::val_type get(key_type key, Cache::size_type& val_size) const {
        // Very short function eh?
        if (map_.count(key) == 0) {
            return nullptr;
        } else {
            return map_.at(key).get();
        }
    }
    bool del(key_type key) {
        if (map_.count(key) == 0) {
            return false;
        } else {
            space_used_ -= size_map_.at(key);
            size_map_.erase(key);
            return map_.erase(key);
        }
    }
    Cache::size_type space_used() const {
        return space_used_;
    }
    void reset() {
        map_.clear();
        size_map_.clear();
        space_used_ = 0;
    }
  private:
    Cache::size_type maxmem_;
    float max_load_factor_;
    Evictor* evictor_;
    Cache::hash_func hasher_;
    std::unordered_map<key_type, std::shared_ptr<char[]>> map_;
    std::unordered_map<key_type, Cache::size_type> size_map_;  // We hoped to have an unordered map to a cache_record struct. However, it was not to be.
    Cache::size_type space_used_;
};


// Ape the given Fridge example
Cache::Cache(size_type maxmem, float max_load_factor, Evictor* evictor, Cache::hash_func hasher) : pImpl_(new Impl(maxmem, max_load_factor, evictor, hasher)) {}

Cache::~Cache() {}

// Hmm. Maybe we don't actually want to pass it the arguments:
void Cache::set(key_type key, val_type val, Cache::size_type size){
    pImpl_->set(key, val, size);
}

Cache::val_type Cache::get(key_type key, Cache::size_type& val_size) const {
    return pImpl_->get(key, val_size);
}

bool Cache::del(key_type key) {
    return pImpl_->del(key);
}

Cache::size_type Cache::space_used() const {
    return pImpl_->space_used();
}

void Cache::reset() {
    pImpl_->reset();
}

