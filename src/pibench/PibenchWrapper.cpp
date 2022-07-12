//
// Created by Lukas Vogel on 10.03.2021.
//

#include "PibenchWrapper.h"

extern "C" tree_api* create_tree(const tree_options_t& opt) {
    return new PibenchWrapper();
}

bool PibenchWrapper::remove(const char *key, size_t key_sz) {
	return kv.remove(string_view(key, key_sz)) == status::OK;
}

bool PibenchWrapper::find(const char *key, size_t key_sz, char *value_out) {
	return kv.get(string_view(key, key_sz), reinterpret_cast<std::string*>(value_out)) == status::OK;
}

bool PibenchWrapper::insert(const char *key, size_t key_sz, const char *value, size_t value_sz) {
	return kv.put(string_view(key, key_sz), string_view(value, value_sz)) == status::OK;
}

bool PibenchWrapper::update(const char *key, size_t key_sz, const char *value, size_t value_sz) {
    return insert(key, key_sz, value, value_sz);
}

int PibenchWrapper::scan(const char *key, size_t key_sz, int scan_sz, char *&values_out) {
    return 0;
}

long PibenchWrapper::get_size() {
}