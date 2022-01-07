#include "alloca.h"
#include "assert.h"
#include "crable.h"

void naive_ReportsFullnessCorrectly() {
    size_t memsize = crable_memsize(5);
    crable *tbl = crable_make(alloca(memsize), memsize);

    // Fill table
    assert(crable_put(tbl, 1, 1) == 4);
    assert(crable_put(tbl, 2, 2) == 3);
    assert(crable_put(tbl, 3, 3) == 2);
    assert(crable_put(tbl, 4, 4) == 1);
    assert(crable_put(tbl, 5, 5) == 0);

    // Remove one element and reinsert
    assert(crable_put(tbl, 1, 0) == 1);
    assert(crable_put(tbl, 1, 1) == 0);

    // Remove one element and insert other
    assert(crable_put(tbl, 1, 0) == 1);
    assert(crable_put(tbl, 6, 6) == 0);

    // Remove one element and insert zero element
    assert(crable_put(tbl, 2, 0) == 1);
    assert(crable_put(tbl, 0, 1) == 0);
}

int main() { naive_ReportsFullnessCorrectly(); }
