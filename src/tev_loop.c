#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tev.h"

static tev_loop_t *default_loop = NULL;

tev_loop_t *
tev_loop_create(tev_heap_fn_t *p)
{
    tev_loop_t *loop = NULL;

    TEV_ASSERT_NOT_NULL(p);

    loop = (tev_loop_t *)p->malloc(sizeof(tev_loop_t));
    TEV_ASSERT_NOT_NULL(loop);

    /* init */
    memcpy(&loop->heap_fn, p, sizeof(tev_heap_fn_t));
    QUEUE_INIT(loop->handle_queue);
    QUEUE_INIT(loop->timer_queue);
    QUEUE_INIT(loop->idle_queue);
    loop->is_cancel = 0;

    return loop;
}

tev_loop_t *
tev_default_loop(void)
{
    if (NULL == default_loop) {
        tev_heap_fn_t fn = {
            .malloc = malloc,
            .calloc = calloc,
            .realloc = realloc,
            .free = free
        };

        default_loop = tev_loop_create(&fn);
    }

    return default_loop;
}

