#include "refqueue.h"

enum {OK=0,ERR=-1};


int main(void)
{
    struct RefQueue ref_q = {0};
    if (ERR == ref_q_construct(&ref_q, 100, malloc)) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 100; i++) {
        if (ERR == ref_q_enqueue(&ref_q, "hello world")) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < 100; i++) {
        char* value = NULL;
        if (ERR == ref_q_dequeue(&ref_q, (void*)&value)) {
            return EXIT_FAILURE;
        }

        int _ = printf("got value from queue: %s\n", value);


    }

    return 0;
}
