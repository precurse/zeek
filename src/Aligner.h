#pragma once

// Utility methods for adjusting the alignment of a pointer to specific
// byte boundaries.
namespace Aligner {

	// Rounds the given pointer up to the nearest multiple of the
	// given size, if not already a multiple.
	const void* Align(const char* ptr, unsigned int size);

	// Rounds the given pointer up to the nearest multiple of the
	// given size, padding the skipped region with 0 bytes.
	void* AlignAndPad(char* ptr, unsigned int size);

	// Returns offset+size rounded up so it can correctly align data
	// of the given size.
	int SizeAlign(int offset, unsigned int size);

	template<class T>
	T* AlignAndPadType(char* ptr)
		{
		return reinterpret_cast<T*>(AlignAndPad(ptr, sizeof(T)));
		}

	template<class T>
	const T* AlignType(const char* ptr)
		{
		return reinterpret_cast<const T*>(Align(ptr, sizeof(T)));
		}

	template<class T>
	int SizeAlignType(int offset)
		{
		return SizeAlign(offset, sizeof(T));
		}
	}
