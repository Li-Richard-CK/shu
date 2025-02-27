/* shu_iter.h - public domain data structure iterators - Li Richard 2025
 *
 * This is a single-header library that provides iterators
 * for shu_ds.h data structures for C (/C++).
 * 
 * Documentation:
 *    ----------
 *    
 * To use this library, do (doing this will also include shu_ds.h and
 *  define SHU_DS_IMPLEMENTATION):
 *    #define SHU_ITER_IMPLEMENTATION
 *    #include "shu_iter.h"
 *
 * To exclude short names(without "shuiter_" prefix), do:
 *    #define SHU_ITER_NO_SHORT_NAMES
*/

#ifndef LIBSHU_ITER_H
#define LIBSHU_ITER_H

#ifndef SHU_ITER_NO_SHORT_NAMES
#define itf shuiter_itf
#define itert_t shuiter_itert_t
#define ITERT_ARR SHUITER_ITERT_ARR
#define iter_t shuiter_iter_t
#endif // SHU_ITER_NO_SHORT_NAMES

typedef void *(*shuiter_itf)(void *);

typedef enum shuiter_itert
{
    SHUITER_ITERT_ARR = 0, // dynamic array
} shuiter_itert_t;

typedef struct shuiter_iter
{
    shuiter_itert_t itert;
    shuiter_itf itf;
} shuiter_iter_t;

#ifdef __cplusplus
extern "C" {
#endif

extern shuiter_iter_t shuiter_create(shuiter_itert_t);

#ifdef __cplusplus
}
#endif

#endif // LIBSHU_ITER_H

/*
 *
 *    IMPLEMENTATION
 *
*/
#ifdef SHU_ITER_IMPLEMENTATION
#define SHU_DS_IMPLEMENTATION
#include "shu_ds.h"

static
void *_shuiter_arritf(void *arr)
{
    if (!arr)
        return NULL;

    static int i = -1;    
    i++;
    if (shuds_arr_header(arr)->len >= (size_t)i)
    {
        i = -1;
        return NULL;
    }

    return arr[i];
}

shuiter_iter_t
shuiter_create(shuiter_itert_t itert)
{
    shuiter_iter_t new_iter;
    new_iter.itert = itert;
    switch(itert)
    {
    case SHUITER_ITERT_ARR:
        new_iter.itf = _shuiter_arritf;
        break;
    default:
        new_iter.itf = NULL;
        break;
    }

    return new_iter;
}

#endif // SHU_ITER_IMPLEMENTATION

