/*
 * bitfield.h
 *
 *  Created on: 4. 6. 2016
 *      Author: Rosta
 */

#ifndef _LIBPCRFC_BITFIELD_H_
#define _LIBPCRFC_BITFIELD_H_

#include <stdint.h>
#include <stddef.h>

#define BF_TYPE			uint64_t
#define BF_TYPE_SIZE	64


struct s_bitfield_item
{
	BF_TYPE data;
	struct s_bitfield_item *next;
};
typedef struct s_bitfield_item t_bitfield_item;


typedef struct
{
	t_bitfield_item *data;
	t_bitfield_item *last;
	size_t size_bits;
} t_bitfield;

typedef uint32_t t_item_offset;


t_bitfield* bf_create(void);
t_bitfield_item* bf_add_new_item(t_bitfield *bf);
void bf_remove_last_item(t_bitfield *bf);
void bf_free(t_bitfield *bf);

t_bitfield_item* bf_find_item(t_bitfield *bf, size_t index);
static inline t_item_offset bf_calc_item_offset(size_t index);
void bf_clear_bit(t_bitfield *bf, size_t index);
void bf_set_bit(t_bitfield *bf, size_t index);
void bf_write_bit(t_bitfield *bf, size_t index, unsigned value);
void bf_toggle_bit(t_bitfield *bf, size_t index);
int bf_get_bit(t_bitfield *bf, size_t index);


#endif //_LIBPCRFC_BITFIELD_H_
