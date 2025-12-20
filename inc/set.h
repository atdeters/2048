#ifndef SET_H
# define SET_H

# include <stdint.h>
# include <stdbool.h>

# define SET_CAPACITY 25

typedef struct s_set {
    uint8_t container[SET_CAPACITY];
    uint8_t set_size;
    uint8_t idx;
} Set;

void init_set(Set *set, uint8_t set_size);
bool set_contains(Set *set, uint8_t nb);
void set_remove(Set *set, uint8_t nb);
void set_insert(Set *set, uint8_t nb);
void set_update_size(Set *set, uint8_t size);
void set_clear(Set *set);
void display_set(Set *set);

#endif // !SET_C

