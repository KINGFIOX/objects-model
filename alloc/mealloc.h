#ifndef MEALLOC_H
#define MEALLOC_H

// 这里放头文件的内容
#include <pthread.h>
#include <string.h>
#include <unistd.h>

typedef char ALIGN[16]; // using ARIGN = char[16]

union header {
    struct {
        size_t size;
        unsigned is_free;
        union header* next;
    } s;
    ALIGN stub; // 这样，这个header就与16字节对齐了
};
typedef union header header_t; // using header_t = union header

header_t* get_free_block(size_t size);
void* malloc(size_t size);
void free(void* block);
void* calloc(size_t num, size_t nsize);
void* realloc(void* block, size_t size);

#endif // MEALLOC_H