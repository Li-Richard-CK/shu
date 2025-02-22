/* shu_ds.h - public domain data structures - Li Richard 2025
 *
 * This is a single-header library that provides generic,
 * efficient dynamic arrays for C (/C++).
 * 
 * Documentation:
 *    man 3 shu
 *    man 3 <function full name>
 *    
 * To use this library, do:
 *    #define SHU_DS_IMPLEMENTATION
 *    #include "shu_ds.h"
 *
 * To exclude short names(without "shuds_" prefix), do:
 *    #define SHU_DS_NO_SHORT_NAMES
*/

#ifndef LIBSHU_DS_H
#define LIBSHU_DS_H
#include <stddef.h>
#include <string.h>

#ifndef SHU_DS_NO_SHORT_NAMES
#define arr_header_t shuds_arr_header_t
#define ARR SHUDS_ARR
#define arr_header shuds_arr_header
#define arr_getlen shuds_arr_getlen
#define arr_get_capacity shuds_arr_get_capacity
#define arr_resize shuds_arr_resize
#define arr_shrink_to_fit shuds_arr_shrink_to_fit
#define arr_append shuds_arr_append
#define arr_appendn shuds_arr_appendn
#define arr_insert shuds_arr_insert
#define arr_insertn shuds_arr_insertn
#define arr_pop_back shuds_arr_pop_back
#define arr_del shuds_arr_del
#define arr_deln shuds_arr_deln
#define arr_first shuds_arr_first
#define arr_last shuds_arr_last
#define arr_free shuds_arr_free
#endif // SHU_DS_NO_SHORT_NAMES

/*
 *
 *    DYNAMIC ARRAYS
 *
*/
typedef struct shuds_arr_header
{
    size_t len, capacity;
} shuds_arr_header_t;

#define SHUDS_ARR(T) T*

#ifdef __cplusplus
extern "C" {
#endif

extern void _shuds_arr_resize(void **, size_t, size_t);
extern void _shuds_arr_check_resize(void **, size_t, size_t);

#define shuds_arr_header(arr) \
    ((arr) ? ((shuds_arr_header_t *)((char*)(arr) - sizeof(shuds_arr_header_t))) : NULL)

#define shuds_arr_getlen(arr) \
    ((arr) ? shuds_arr_header(arr)->len : 0)

#define shuds_arr_get_capacity(arr) \
    ((arr) ? shuds_arr_header(arr)->capacity : 0)

// creates header if header doesnt exist
#define shuds_arr_resize(arr, cap)                                    \
    do                                                                \
    {                                                                 \
        _shuds_arr_resize((void **)&(arr), sizeof(*(arr)), (cap));    \
    } while (0)

#define shuds_arr_shrink_to_fit(arr)                                                                                     \
    do                                                                                                                   \
    {                                                                                                                    \
        if ((arr) && shuds_arr_header(arr)->len > 0 && shuds_arr_header(arr)->len != shuds_arr_header(arr)->capacity)    \
            _shuds_arr_resize((void **)&(arr), sizeof(*(arr)), shuds_arr_header(arr)->len);                              \
    } while (0)

// creates header if header doesnt exist
#define shuds_arr_append(arr, v)                                                                                     \
    do                                                                                                               \
    {                                                                                                                \
        _shuds_arr_check_resize((void **)&(arr), sizeof(*(arr)), (arr) ? shuds_arr_header(arr)->len + 1 : 1);        \
        (arr)[shuds_arr_header(arr)->len++] = (v);                                                                   \
    } while (0)

// creates header if header doesnt exist
#define shuds_arr_appendn(arr, va, n)                                                   								 \
    do                                                                                  								 \
    {                                                                               									 \
        if ((n) > 0 && (va))                                                            								 \
        {                                                                               							     \
            _shuds_arr_check_resize((void **)&(arr), sizeof(*(arr)), (arr) ? shuds_arr_header(arr)->len + (n) : (n));    \
            memcpy(&(arr)[shuds_arr_header(arr)->len], (va), (n) * sizeof(*(arr)));                                      \
            shuds_arr_header(arr)->len += (n);                                                                           \
        }                                                                                                                \
    } while (0)

#define shuds_arr_insert(arr, i, v)                                                                                  \
    do                                                                                                               \
    {                                                                                                                \
        if ((arr) && (i) <= shuds_arr_header(arr)->len)                                                              \
        {                                                                                                            \
            _shuds_arr_check_resize((void **)&(arr), sizeof(*(arr)), shuds_arr_header(arr)->len + 1);                \
            memmove(&(arr)[(i) + 1], &(arr)[(i)], sizeof(*(arr)) * (shuds_arr_header(arr)->len - (i)));              \
            (arr)[(i)] = (v);                                                                                        \
            shuds_arr_header(arr)->len++;                                                                            \
        }                                                                                                            \
    } while (0)

#define shuds_arr_insertn(arr, i, va, n)   														  			 \
    do                                   																	 \
    {                                                                                                        \
        if ((arr) && (i) <= shuds_arr_header(arr)->len)                                                      \
        {                                                                                                    \
            _shuds_arr_check_resize((void **)&(arr), sizeof(*(arr)), shuds_arr_header(arr)->len + (n));      \
            memmove(&(arr)[(i) + (n)], &(arr)[(i)], sizeof(*(arr)) * (shuds_arr_header(arr)->len - (i)));    \
            memcpy(&(arr)[i], (va), (n) * sizeof(*(arr)));                                                   \
            shuds_arr_header(arr)->len += (n);                                                               \
        }                                                                                                    \
    } while (0)

#define shuds_arr_pop_back(arr)                   \
    ((arr) && shuds_arr_header(arr)->len > 0 ?    \
    (shuds_arr_header(arr)->len--, (arr)[shuds_arr_header(arr)->len]) : (typeof(*(arr))){0})

#define shuds_arr_del(arr, i)                                                                              \
    do                                                                                                     \
    {                                                                                                      \
        if ((arr) && (i) < shuds_arr_header(arr)->len)                                                     \
        {                                                                                                  \
            shuds_arr_header(arr)->len--;                                                                  \
            memmove(&(arr)[(i)], &(arr)[(i) + 1], sizeof(*(arr)) * (shuds_arr_header(arr)->len - (i)));    \
        }                                                                                                  \
    } while (0)

#define shuds_arr_deln(arr, i, n)                                                                                  \
    do                                                                                                             \
    {                                                                                                              \
        if ((arr) && (i) + (n) <= shuds_arr_header(arr)->len)                                                      \
        {                                                                                                          \
            memmove(&(arr)[(i)], &(arr)[(i) + (n)], sizeof(*(arr)) * (shuds_arr_header(arr)->len - (i) - (n)));    \
            shuds_arr_header(arr)->len -= (n);                                                                     \
        }                                                                                                          \
    } while (0)

#define shuds_arr_first(arr) ((arr) && shuds_arr_header(arr)->len > 0 ? (arr)[0] : 0)

#define shuds_arr_last(arr) ((arr) && shuds_arr_header(arr)->len > 0 ? (arr)[shuds_arr_header(arr)->len - 1] : 0)

#define shuds_arr_free(arr)                       \
    do                                            \
    {                                             \
        if (arr)                                  \
        {                                         \
            SHUDS_FREE(shuds_arr_header(arr));    \
            (arr) = NULL;                         \
        }                                         \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif // LIBSHU_DS_H

/*
 *
 *    IMPLEMENTATION
 *
*/
#ifdef SHU_DS_IMPLEMENTATION
#include <stdlib.h>
#include <assert.h>

#if !defined SHUDS_REALLOC && !defined SHUDS_FREE
#define SHUDS_REALLOC realloc
#define SHUDS_FREE free
#else
#if defined SHUDS_REALLOC && defined SHUDS_FREE
#else
#error "You must define both SHUDS_REALLOC and SHUDS_FREE."
#endif
#endif

#define SHUDS_MAX_POW2 ((size_t)1 << (sizeof(size_t) * 8 - 1))

static int
_shuds_is_pow2(size_t n)
{
    return (n != 0) && ((n & (n - 1)) == 0);
}

static size_t
_shuds_next_pow2(size_t n)
{
    if (n == 0) return 1;
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    n++;
    return n;
}

#define SHUDS_ARR_DEFAULT_CAPACITY (1 << 1) // 2

// shuds_arr_resize
void
_shuds_arr_resize(void **arr, size_t elmsize, size_t new_cap)
{

    shuds_arr_header_t *header = shuds_arr_header(*arr);
    if (new_cap == 0)
    {
        if (header)
        {
            SHUDS_FREE(header);
            *arr = NULL;
        }
        return;
    }

    /* if (!header)
    {
        header = SHUDS_REALLOC(NULL, new_cap * elmsize + sizeof(shuds_arr_header_t));
        assert(header);
        header->len = 0;
    }
    else
    {
        header = SHUDS_REALLOC(header, new_cap * elmsize + sizeof(shuds_arr_header_t));
        assert(header);
    } */
    header = (shuds_arr_header_t *)SHUDS_REALLOC(header, new_cap * elmsize + sizeof(shuds_arr_header_t));
    assert(header);
    header->capacity = new_cap;
    *arr = header + 1;
}

// shuds_arr_check_resize
void
_shuds_arr_check_resize(void **arr, size_t elmsize, size_t min_cap)
{
    if (!*arr)
    {
        _shuds_arr_resize(arr, elmsize, SHUDS_ARR_DEFAULT_CAPACITY);
        shuds_arr_header(*arr)->len = 0;
        return;
    }

    shuds_arr_header_t *header = shuds_arr_header(*arr);
    if (header->capacity < min_cap)
    {
        // _shuds_arr_resize(arr, elmsize, header->capacity << (int)(min_cap / header->capacity)); // multiply by 2
        /* size_t new_cap = header->capacity;
        while (header->capacity < min_cap)
        {
            new_cap <<= 1;
            if (new_cap == 0)
            {
                new_cap = min_cap;
                break;
            }
        }
        _shuds_arr_resize(arr, elmsize, new_cap); */
        /* size_t new_cap = header->capacity * 2;
        if (new_cap < min_cap)
            new_cap = min_cap; // fallback to min_cap if not enough
        _shuds_arr_resize(arr, elmsize, new_cap); */
        if (min_cap >= SHUDS_MAX_POW2 && _shuds_is_pow2(min_cap))
            assert(min_cap < SHUDS_MAX_POW2 && "Capacity overflow");

        size_t new_cap = _shuds_next_pow2(min_cap);
        if (new_cap == 0)
            assert(0 && "Capacity overflow");
        _shuds_arr_resize(arr, elmsize, new_cap);
    }
}

#endif // SHU_DS_IMPLEMENTATION

