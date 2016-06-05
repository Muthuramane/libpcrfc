
#include <errno.h>
#include <stdlib.h>
#include <pcrfc/defs.h>
#include <pcrfc/bitfield.h>


t_bitfield* bf_create(void)
{
	t_bitfield* bf;

	//try to allocate new bitfield
	if ((bf = (t_bitfield*)libmalloc(sizeof(t_bitfield))) == NULL)
	{
		print_err("%s", "libmalloc returned NULL");
		errno = ENOMEM;
		return NULL;
	}

	//init inner values
	bf->data = bf->last = NULL;
	bf->size_bits = 0;
	return bf;
}

t_bitfield_item* bf_add_new_item(t_bitfield *bf)
{
	t_bitfield_item *new_node;

	//try to allocate a new node
	if ((new_node = (t_bitfield_item*)libmalloc(sizeof(t_bitfield_item))) == NULL)
	{
		print_err("%s", "libmalloc returned NULL");
		errno = ENOMEM;
		return NULL;
	}

	//initialize inner values
	new_node->next = NULL;
	new_node->data = 0;

	//append allocated node to the last node of list
	if (bf->last == NULL)
	{
		bf->last->next = new_node;
		bf->last = new_node;
	}
	else
	{
		bf->data = bf->last = new_node;
	}

	return new_node;
}

void bf_remove_last_item(t_bitfield *bf)
{
	if (bf->data == NULL) return;

	//only one node is allocated
	if (bf->data == bf->last)
	{
		libfree(bf->data);
		bf->data = bf->last = NULL;
		return;
	}

	//get last node ptr
	t_bitfield_item *last = bf->last;

	//find previous node of last node
	t_bitfield_item *prev = NULL;
	for(prev = bf->data; prev->next != last; prev = prev->next);

	//free last node
	libfree(prev->next);
	prev->next = NULL;
	bf->last = prev;
	return;
}

void bf_free(t_bitfield *bf)
{
	//free items
	while (bf->data != NULL)
	{
		t_bitfield_item *next = bf->data->next;
		libfree(bf->data);
		bf->data = next;
	}

	libfree(bf);
	return;
}

t_bitfield_item* bf_find_item(t_bitfield* bf, size_t index)
{
	size_t item_index = index / BF_TYPE_SIZE;
	t_bitfield_item* item = NULL;

	if (bf->data == NULL) return NULL;

	int found = 0;
	item = bf->data;

	for(size_t i = 0; item != NULL; item = item->next, i++)
	{
		if (item_index == i)
		{
			found = 1;
			break;
		}
	}

	return (found) ? item : NULL;
}

static inline t_item_offset bf_calc_item_offset(size_t index)
{
	return (index % BF_TYPE_SIZE);
}

void bf_clear_bit(t_bitfield *bf, size_t index)
{
	t_item_offset item_offset = bf_calc_item_offset(index);
	t_bitfield_item *item = bf_find_item(bf, index);

	if (item == NULL)
	{
		print_err("Index not found (%zu)", index);
		return;
	}

	BF_TYPE mask = ~(1 << item_offset);
	item->data &= mask;

	return;
}

void bf_set_bit(t_bitfield *bf, size_t index)
{
	t_item_offset item_offset = bf_calc_item_offset(index);
	t_bitfield_item *item = bf_find_item(bf, index);

	if (item == NULL)
	{
		print_err("Index not found (%zu)", index);
		return;
	}

	BF_TYPE mask = (1 << item_offset);
	item->data |= mask;

	return;
}

void bf_toogle_bit(t_bitfield *bf, size_t index)
{
	t_item_offset item_offset = bf_calc_item_offset(index);
	t_bitfield_item *item = bf_find_item(bf, index);

	if (item == NULL)
	{
		print_err("Index not found (%zu)", index);
		return;
	}

	BF_TYPE mask = (1 << item_offset);
	item->data ^= mask;

	return;
}

int bf_get_bit(t_bitfield *bf, size_t index)
{
	t_item_offset item_offset = bf_calc_item_offset(index);
	t_bitfield_item *item = bf_find_item(bf, index);

	if (item == NULL)
	{
		print_err("Index not found (%zu)", index);
		return -1;
	}

	return ((item->data >> item_offset) & 0x1);
}

void bf_write_bit(t_bitfield *bf, size_t index, unsigned value)
{
	if (value) bf_set_bit(bf, index);
	else bf_clear_bit(bf, index);
}


