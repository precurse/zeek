#include "Aligner.h"

#include <cstdint>
#include "util.h"

static bool is_power_of_2(uint64_t x)
	{
	return ((x-1) & x) == 0;
	}

const void* Aligner::Align(const char* ptr, unsigned int size)
	{
	if ( ! size )
		return ptr;

	ASSERT(is_power_of_2(size));

	unsigned int mask = size - 1;	// Assume size is a power of 2.
	unsigned long l_ptr = reinterpret_cast<unsigned long>(ptr);
	unsigned long offset = l_ptr & mask;

	if ( offset > 0 )
		return reinterpret_cast<const void*>(ptr - offset + size);
	else
		return reinterpret_cast<const void*>(ptr);
	}

// Rounds the given pointer up to the nearest multiple of the
// given size, padding the skipped region with 0 bytes.
void* Aligner::AlignAndPad(char* ptr, unsigned int size)
	{
	if ( ! size )
		return ptr;

	ASSERT(is_power_of_2(size));

	unsigned int mask = size - 1;	// Assume size is a power of 2.
	while ( (reinterpret_cast<unsigned long>(ptr) & mask) != 0 )
		// Not aligned - zero pad.
		*ptr++ = '\0';

	return reinterpret_cast<void *>(ptr);
	}

// Returns offset+size rounded up so it can correctly align data
// of the given size.
int Aligner::SizeAlign(int offset, unsigned int size)
	{
	if ( ! size )
		return offset;

	ASSERT(is_power_of_2(size));

	unsigned int mask = size - 1;	// Assume size is a power of 2.
	if ( offset & mask )
		{
		offset &= ~mask;	// Round down.
		offset += size;		// Round up.
		}

	offset += size;		// Add in size.

	return offset;
	}
