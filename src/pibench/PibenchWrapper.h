//
// Created by Lukas Vogel on 10.03.2021.
//

#ifndef LSM_PIBENCHWRAPPER_H
#define LSM_PIBENCHWRAPPER_H


#include "tree_api.h"
#include <../../src/libpmemkv.hpp>

using namespace pmem::kv;

class PibenchWrapper : public tree_api {

public:
    inline bool find(const char* key, size_t key_sz, char* value_out) override;
    inline bool insert(const char* key, size_t key_sz, const char* value, size_t value_sz) override;
    inline bool update(const char* key, size_t key_sz, const char* value, size_t value_sz) override;
    inline bool remove(const char* key, size_t key_sz) override;
    inline int scan(const char* key, size_t key_sz, int scan_sz, char*& values_out) override;
    virtual long get_size() override;

    const uint64_t SIZE = 200UL * 1024UL * 1024UL * 1024UL;


    PibenchWrapper() {
	    config cfg;
	    cfg.put_path("/mnt/pmem0/vogel/pmemkv");
	    cfg.put_size(SIZE);
	    cfg.put_create_if_missing(true);
	    kv.open("cmap", std::move(cfg));

    }
private:
	db kv;
};


#endif //LSM_PIBENCHWRAPPER_H
