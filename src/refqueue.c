#include "refqueue.h"

enum {ERR=-1, OK=0};

int ref_q_construct(
    struct RefQueue* ref_q,
    size_t capacity,
    const MemoryAllocate mem_alloc)
{
    void** tmp = 
        mem_alloc(
            capacity == 0 
            ? 1 * sizeof(void*)
            : capacity * sizeof(void*)        
        );
    if (NULL == tmp) {
        return ERR;
    }

    ref_q->capacity = capacity;
    ref_q->head = 0;
    ref_q->tail = 0;
    ref_q->data = tmp;

    return OK;
}

void ref_q_destruct(
    struct RefQueue* ref_q)
{
    if (NULL != ref_q->data) {
        free(ref_q->data);
        ref_q->data = NULL;
    }
}

bool ref_q_full(
    const struct RefQueue* ref_q)
{
    return ref_q->count == ref_q->capacity;
}

bool ref_q_empty(
    const struct RefQueue* ref_q)
{
    return ref_q->count == 0;
}

static void incrOrLoopBack(
    size_t* i,
    const size_t max)
{
    size_t tmp = *i + 1;
    if (tmp >= max)
        tmp = 0;
    *i = tmp;
}

int ref_q_enqueue(
    struct RefQueue* ref_q,
    void* value)
{
    if (ref_q_full(ref_q))
        return ERR;
    
    const ptrdiff_t i = ref_q->tail;
    ref_q->data[i] = value;
    incrOrLoopBack(
        &ref_q->tail,
        ref_q->capacity
    );
    ref_q->count++;
    return OK;
}

int ref_q_dequeue(
    struct RefQueue* ref_q,
    void** value)
{
    if (ref_q_empty(ref_q)) {
        return ERR;
    }
    
    const ptrdiff_t i = ref_q->head;
    *value = ref_q->data[i];
    incrOrLoopBack(
        &ref_q->head,
        ref_q->capacity
    );
    ref_q->count--;
    return OK;
}

void* ref_q_dequeue_ref(
    struct RefQueue* ref_q)
{
    void* value = NULL;
    switch (ref_q_dequeue(ref_q, &value)) {
        case OK: return value;
        default: return NULL;
    }
}

size_t ref_q_count(
    const struct RefQueue* queue)
{
    return queue->count;
}

size_t ref_q_capacity(
    const struct RefQueue* queue)
{
    return queue->capacity;
}