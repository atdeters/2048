#include "../inc/set.h"
#include <sys/types.h>
#include <ncurses.h>

void init_set(Set *set, uint8_t set_size) {
    (*set).idx = -1;
    for (size_t i = 0; i < SET_CAPACITY && (*set).idx < set_size; i++) {
        (*set).idx++;
        (*set).container[(*set).idx] = (*set).idx;
    }
    (*set).idx--;
    (*set).set_size = set_size;
}

bool set_contains(Set *set, uint8_t nb) {
    if ((*set).idx == -1) {
        return false;
    }
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
        int idx = 0;
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

void set_clear(Set *set) {
    (*set).idx = -1;
    for (size_t i = 0; i < SET_CAPACITY; i++) {
        (*set).container[i] = 0;
    }
}

void display_set(Set *set) {
    if ((*set).idx == -1) {
        printw("Set is empty!\n");
        return;
    }
    for (int i = 0; i <= (*set).idx; i++) {
        printw("|%d|", (*set).container[i]);
    }
    printw("\n");
}
