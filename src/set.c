#include "../inc/set.h"
#include <sys/types.h>

void init_set(Set *set, uint8_t set_size) {
    (*set).idx = 0;
    while ((*set).idx < SET_CAPACITY && (*set).idx < set_size) {
        (*set).container[(*set).idx] = (*set).idx;
        (*set).idx++;
    }
    (*set).idx--;
    (*set).set_size = set_size;
}

bool set_contains(Set *set, uint8_t nb) {
    for (int i = 0; i <= (*set).idx; i++) {
        if ((*set).container[i] == nb)
            return true;
    }
    return false;
}

void set_remove(Set *set, uint8_t nb) {
    if (!set_contains(set, nb)) {
        return;
    }
    else {
        size_t idx = 0;
        while ((*set).container[idx] != nb) {
            idx++;
        }
        while (idx < (*set).set_size - 1) {
            (*set).container[idx] = (*set).container[idx+1];
            idx++;
        }
        (*set).container[idx] = 0;
        (*set).idx--;
    }
}

void set_insert(Set *set, uint8_t nb) {
    if ((*set).idx < (*set).set_size - 1) {
        (*set).idx++;
        (*set).container[(*set).idx] = nb;
    }
}

void set_update_size(Set *set, uint8_t size) {
    if (size > SET_CAPACITY) {
        size = SET_CAPACITY;
    }
        (*set).set_size = size;
}

