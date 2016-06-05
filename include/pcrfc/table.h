

#ifndef _LIBPCRFC_TABLE_H_
#define _LIBPCRFC_TABLE_H_

#include <stdint.h>
#include <stddef.h>


#define CONCAT(a, b) a ## b
#define CONCAT_T(a, b) CONCAT(a, b)

#define TABLE_TYPE_PREFIX t_table_
#define TABLE_SIZE_TYPE size_t

#define TABLE_TYPE(type) \
	typedef struct { type *data; TABLE_SIZE_TYPE size; } \
		CONCAT_T(TABLE_TYPE_PREFIX, type)

TABLE_TYPE(uint32_t);


#endif //_LIBPCRFC_TABLE_H_
