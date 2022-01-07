#include "alloca.h"
#include "assert.h"
#include "crable.h"

void naive_OverfullIsFull() {
    size_t memsize = crable_memsize(5);
    crable *tbl = crable_make(alloca(memsize), memsize);

    // Overfill table
    crable_put(tbl, 1, 1);
    crable_put(tbl, 2, 2);
    crable_put(tbl, 3, 3);
    crable_put(tbl, 4, 4);
    crable_put(tbl, 5, 5);
    crable_put(tbl, 6, 6);
    crable_put(tbl, 7, 7);
    crable_put(tbl, 8, 8);

    // Compute number of hits
    int hits = 0;
    hits += (crable_get(tbl, 1) == 1);
    hits += (crable_get(tbl, 2) == 2);
    hits += (crable_get(tbl, 3) == 3);
    hits += (crable_get(tbl, 4) == 4);
    hits += (crable_get(tbl, 5) == 5);
    hits += (crable_get(tbl, 6) == 6);
    hits += (crable_get(tbl, 7) == 7);
    hits += (crable_get(tbl, 8) == 8);
    assert(hits == 5);
}

int main() { naive_OverfullIsFull(); }
