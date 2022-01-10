#include "alloca.h"
#include "assert.h"
#include "crable.h"
#include "stdlib.h"

void naive_ReliableUntilFull() {
    size_t memsize = crable_memsize(5);
    crable *tbl = crable_make(alloca(memsize), memsize);

    // Fill table
    crable_put(tbl, 1, 1);
    crable_put(tbl, 2, 2);
    crable_put(tbl, 3, 3);
    crable_put(tbl, 4, 4);
    crable_put(tbl, 5, 5);
    assert(crable_get(tbl, 0) == 0);
    assert(crable_get(tbl, 1) == 1);
    assert(crable_get(tbl, 2) == 2);
    assert(crable_get(tbl, 3) == 3);
    assert(crable_get(tbl, 4) == 4);
    assert(crable_get(tbl, 5) == 5);

    // Delete element
    crable_put(tbl, 1, 0);
    assert(crable_get(tbl, 1) == 0);

    // Reinsert element
    crable_put(tbl, 1, 10);
    assert(crable_get(tbl, 1) == 10);
}

void property_ReliableUntilFull(size_t domain) {
    size_t memsize = crable_memsize(domain);
    crable *tbl = crable_make(alloca(memsize), memsize);
    int randoms[domain];
    for (size_t i = 0; i < domain; i++) {
        randoms[i] = rand();
    }

    for (size_t i = 0; i < domain; i++) {
        crable_put(tbl, randoms[i], randoms[i]);
    }
    for (size_t i = 0; i < domain; i++) {
        assert(crable_get(tbl, randoms[i]) == (uint_fast64_t)(randoms[i]));
    }
}

int main() {
    naive_ReliableUntilFull();
    property_ReliableUntilFull(rand() % 11);
    property_ReliableUntilFull(rand() % 101);
    property_ReliableUntilFull(rand() % 1001);
    property_ReliableUntilFull(rand() % 10001);
}
