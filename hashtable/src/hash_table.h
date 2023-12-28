// #ifdef HASH_TABLE_H
// #define HASH_TABLE_H

#define HT_PRIME_1 11
#define HT_PRIME_2 13
#define HT_INITIAL_BASE_SIZE 53

typedef struct {
    char* key;
    char* value;
} ht_item;

typedef struct {
    int size;
    int count;
    ht_item** items; // 数组
} ht_hash_table;

static ht_hash_table* ht_new_sized(const int base_size);
void ht_delete(ht_hash_table* ht, const char* key);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
static int ht_get_hash(const char* s, const int num_buckets, const int attempt);
static int ht_hash(const char* s, const int a, const int m);
void ht_del_hash_table(ht_hash_table* ht);
static void ht_del_item(ht_item* i);
ht_hash_table* ht_new();
static ht_item* ht_new_item(const char* k, const char* v);
static void ht_resize(ht_hash_table* ht, const int base_size);

// #endif