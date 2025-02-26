/* shu.h - public domain single-header-file utilities - Li Richard 2025
 *
 * This is a collection of all shu libraries.
 * Will not define no short names or implementation by default.
 *
 * Documentation:
 *    ----------
 */
#ifndef LIBSHU_H
#define LIBSHU_H

#ifdef SHU_IMPLEMENTATION
#define SHU_DS_IMPLEMENTATION
#endif

#ifdef SHU_NO_SHORT_NAMES
#define SHU_DS_NO_SHORT_NAMES
#endif

#include "shu_ds.h"

#endif

