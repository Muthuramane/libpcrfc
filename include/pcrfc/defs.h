
#ifndef _LIBPCRFC_DEFS_H_
#define _LIBPCRFC_DEFS_H_

#include <stdio.h>
#include <stdlib.h>

#define _libmalloc(size) malloc(size)
#define _libfree(ptr) free(ptr)

#ifndef FAKE_MALLOC
	#define libmalloc(size) _libmalloc(size)
	#define libfree(ptr) _libfree(ptr)
#else
	int __null_malloc;
	#define libmalloc(size) ((__null_malloc) ? NULL : _libmalloc(size))
	#define libfree(ptr) _libfree(ptr)
#endif

#define print_err(args, ...) fprintf(stderr, "<ERROR %s:%d> " args "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)


#endif //_LIBPCRFC_DEFS_H_
