#include "mealloc.h"

header_t *head, *tail; // to keep track of a list
pthread_mutex_t global_malloc_lock; // 全局锁，多线程

/**
 * @brief 看看有没有可以用的 block
 * 
 * @param size 需要分配的字节数
 * @return header_t* 
 */
header_t* get_free_block(size_t size)
{
    header_t* curr = head;
    while (curr) {
        if (curr->s.is_free && curr->s.size >= size) {
            return curr;
        }
        curr = curr->s.next;
    }
    return NULL;
}

/**
 * @brief 
 * 
 * @param size 需要分配的 字节数
 * @return void* 
 */
void* malloc(size_t size)
{
    size_t total_size;
    void* block;
    header_t* header;
    if (!size) {
        return NULL;
    }
    pthread_mutex_lock(&global_malloc_lock); // 上一把大锁
    header = get_free_block(size); // 得到可以用的块

    if (header) {
        header->s.is_free = 0;
        pthread_mutex_unlock(&global_malloc_lock);
        return (void*)(header + 1); // 偏移一个header_t的大小
    }
    // 否则就是，需要再分配
    total_size = sizeof(header_t) + size;
    block = sbrk(total_size);

    if (block == (void*)(-1)) { // brk拓展失败
        pthread_mutex_unlock(&global_malloc_lock);
        return NULL;
    }

    header = block;
    header->s.size = size;
    header->s.is_free = 0;
    header->s.next = NULL;
    if (!head) {
        head = header;
    }
    if (tail) {
        tail->s.next = header;
    }
    tail = header;
    pthread_mutex_unlock(&global_malloc_lock);
    return (void*)(header + 1);
}

void free(void* block)
{
    header_t *header, *tmp;
    void* programbreak;

    if (!block) { // 没用的空间
        return;
    }

    pthread_mutex_lock(&global_malloc_lock);
    header = (header_t*)block - 1; // 偏移到header
    programbreak = sbrk(0); // 分配了0个字节，返回heap拓展的地址

    // 释放最后面的 block
    if ((char*)block + header->s.size == programbreak) {
        if (header == tail) {
            header = tail = NULL;
        } else {
            tmp = head;
            while (tmp) {
                if (tmp->s.next == tail) {
                    tmp->s.next = NULL;
                    tail = tmp;
                }
                tmp = tmp->s.next;
            }
        }
        sbrk(0 - sizeof(header_t) - header->s.size); // sbrk，负数就是 heap 退回
        pthread_mutex_unlock(&global_malloc_lock);
        return;
    }

    header->s.is_free = 1;
    pthread_mutex_unlock(&global_malloc_lock);
}

void* calloc(size_t num, size_t nsize)
{
    size_t size;
    void* block;
    if (!num || !nsize) {
        return NULL;
    }
    size = num * nsize;

    if (nsize != size / num) { // 检查是否出现溢出
        return NULL;
    }

    block = malloc(size);

    if (!block) {
        return NULL;
    }
    memset(block, 0, size);
    return block;
}

void* realloc(void* block, size_t size)
{
    header_t* header;
    void* ret;
    if (!block || !size) {
        return malloc(size);
    }

    // 如果当前位置就合适了，就不必再重新分配了
    header = (header_t*)block - 1;
    if (header->s.size >= size) {
        return block;
    }

    ret = malloc(size);
    if (ret) {
        memcpy(ret, block, header->s.size);
        free(block);
    }
    return ret;
}