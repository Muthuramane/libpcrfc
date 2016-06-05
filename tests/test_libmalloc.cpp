

#include <gtest/gtest.h>
#include <pcrfc/defs.h>

#ifndef FAKE_MALLOC
#define FAKE_MALLOC
#endif

TEST(fakelibmalloc, nullreturn)
{
	extern int __null_malloc;
	__null_malloc = 1;
	void *ptr = libmalloc(4);
	EXPECT_EQ(NULL, (size_t)ptr);
}

TEST(fakelibmalloc, addrreturn)
{
	extern int __null_malloc;
	__null_malloc = 0;
	void *ptr = libmalloc(4);
	EXPECT_NE(NULL, (size_t)ptr);

	libfree(ptr);
}

#undef FAKE_MALLOC

TEST(libmalloc, addrreturn)
{
	void *ptr = libmalloc(4);
	EXPECT_NE(NULL, (size_t)ptr);
}

