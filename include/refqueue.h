#ifndef _REF_QUEUE_H
#define _REF_QUEUE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef void* (*MemoryAllocate)(size_t size);

struct RefQueue
{
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity;
    void** data;
};



int ref_q_construct(
    struct RefQueue* ref_q,
    const size_t capacity,
    const MemoryAllocate memAlloc
);

void ref_q_destruct(
    struct RefQueue* ref_q
);
bool ref_q_full(
    const struct RefQueue* ref_q
);

bool ref_q_empty(
    const struct RefQueue* ref_q
);

int ref_q_enqueue(
    struct RefQueue* ref_q,
    void* value
);

int ref_q_dequeue(
    struct RefQueue* ref_q,
    void** value
);

void* ref_q_dequeue_ref(
    struct RefQueue* ref_q
);


size_t ref_q_count(
    const struct RefQueue* queue
);


size_t ref_q_capacity(
    const struct RefQueue* queue
);

#endif