#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <intrin.h>

typedef unsigned long long bitmap_entry_t;
#define NUMBERS_TO_CALCULATE (1024*1024*1024)
#define BITMAP_ENTRY_BITS (sizeof(bitmap_entry_t)*8)

inline void bitmap_set(bitmap_entry_t *bitmap, unsigned long long index)
{
	_bittestandset64(&bitmap[index / BITMAP_ENTRY_BITS], index%BITMAP_ENTRY_BITS);
}

inline void bitmap_unset(bitmap_entry_t *bitmap, unsigned long long index)
{
	_bittestandreset64(&bitmap[index / BITMAP_ENTRY_BITS], index%BITMAP_ENTRY_BITS);
}

inline bitmap_entry_t bitmap_get(bitmap_entry_t *bitmap, unsigned long long index)
{
	return _bittest64(&bitmap[index / BITMAP_ENTRY_BITS], index%BITMAP_ENTRY_BITS);
}

int main(void)
{
	bitmap_entry_t *bitmap = malloc((1 + NUMBERS_TO_CALCULATE / BITMAP_ENTRY_BITS) * sizeof(bitmap_entry_t));
	for (int i = 0; i < (1 + NUMBERS_TO_CALCULATE / BITMAP_ENTRY_BITS); i++)
	{
		bitmap[i] = 0xFFFFFFFFFFFFFFFFLL;
	}

	for (int i = 2; i < sqrt(NUMBERS_TO_CALCULATE); i++)
	{
		if (bitmap_get(bitmap, i - 2))
		{
			for (int j = 2 * i; j < NUMBERS_TO_CALCULATE; j += i)
			{
				bitmap_unset(bitmap, j - 2);
			}
		}
	}

	for (int i = 2; i < NUMBERS_TO_CALCULATE; i++)
	{
		if (bitmap_get(bitmap, i - 2))
		{
			printf("%d ", i);
		}
	}

	getchar();
}