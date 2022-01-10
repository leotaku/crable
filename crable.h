#include <stddef.h>
#include <stdint.h>

typedef struct crable crable;

size_t crable_capacity(size_t memsize);

size_t crable_memsize(size_t capacity);

crable *crable_make(void *memory, size_t memsize);

size_t crable_put(crable *tbl, size_t full_hash, size_t value);

size_t crable_get(crable *tbl, size_t full_hash);
