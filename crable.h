#include <stddef.h>
#include <stdint.h>

typedef enum crable_error {
    crable_ok = 0,
    crable_full = 1,
} crable_error;

typedef struct crable_entry {
    uint_fast64_t full_hash;
    size_t value;
} crable_entry;

typedef struct crable {
    size_t capacity;
    crable_entry entries[];
} crable;

crable *crable_malloc(size_t capacity);
crable_error crable_put(crable *tbl, size_t full_hash, size_t value);
size_t crable_get(crable *tbl, size_t full_hash);
