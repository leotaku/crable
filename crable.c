#include <inttypes.h>
#include <stddef.h>

typedef struct crable_entry {
    uint_fast64_t full_hash;
    size_t value;
} crable_entry;

typedef struct crable {
    size_t capacity;
    size_t unoccupied;
    crable_entry entries[];
} crable;

size_t crable_capacity(size_t memsize) {
    return (memsize - sizeof(crable)) / sizeof(crable_entry);
}

size_t crable_memsize(size_t capacity) {
    return sizeof(crable) + sizeof(crable_entry) * capacity;
}

crable *crable_make(void *memory, size_t memsize) {
    crable *tbl = memory;
    tbl->capacity = crable_capacity(memsize);
    tbl->unoccupied = tbl->capacity;
    for (size_t n = 0; n < tbl->capacity; n++) {
        tbl->entries[n] = (crable_entry){.full_hash = 0, .value = 0};
    }

    return tbl;
}

size_t crable_put(crable *tbl, uint_fast64_t full_hash, size_t value) {
    size_t distance = 0;
    tbl->unoccupied--;
    do {
        size_t realpos = (full_hash % tbl->capacity + distance) % tbl->capacity;
        crable_entry competitor_copy = tbl->entries[realpos];
        size_t competing_distance =
            (realpos - (competitor_copy.full_hash % tbl->capacity)) % tbl->capacity;

        if (competitor_copy.full_hash == full_hash) {
            tbl->entries[realpos].value = value;
            if (value == 0 && full_hash != 0) {
                tbl->unoccupied += 2;
            }
            return tbl->unoccupied;
        }

        // Swap if we have a higher lookup distance than our competitor
        if (competing_distance < distance || competitor_copy.value == 0) {
            if (value == 0) {
                // Absence value optimization
                return tbl->unoccupied;
            }
            crable_entry tmp = {.full_hash = full_hash, .value = value};
            value = tbl->entries[realpos].value;
            full_hash = tbl->entries[realpos].full_hash;
            distance = competing_distance;
            tbl->entries[realpos] = tmp;
        }

        ;
    } while (++distance < tbl->capacity);

    return 1;
}

size_t crable_get(crable *tbl, uint_fast64_t full_hash) {
    size_t distance = 0;
    for (;;) {
        size_t realpos = (full_hash + distance) % tbl->capacity;
        crable_entry competitor_copy = tbl->entries[realpos];
        size_t competing_distance = realpos - (competitor_copy.full_hash % tbl->capacity);

        if (competitor_copy.full_hash == full_hash) {
            return competitor_copy.value;
        } else if (competitor_copy.value == 0) {
            return 0;
        } else if (competing_distance < distance) {
            return 0;
        } else {
            distance++;
        }
    }
}
