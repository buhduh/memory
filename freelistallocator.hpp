#pragma once

#include "allocator.hpp"

struct FreeBlock {
	std::size_t size;
	FreeBlock* next;
};

struct AllocationHeader {
	std::size_t size;
	std::uintptr_t adjustment;
};

class FreeListAllocator : public Allocator
{
public:
	FreeListAllocator(const std::size_t sizeBytes,
					void* const start) noexcept;
	~FreeListAllocator() noexcept;
	FreeListAllocator(const FreeListAllocator&) = delete;
	FreeListAllocator& operator=(const FreeListAllocator&) = delete;
	FreeListAllocator(FreeListAllocator&&) noexcept;
	FreeListAllocator& operator=(FreeListAllocator&&) noexcept;
	virtual void* allocate(const std::size_t& size,
						   const std::uintptr_t& alignment
						       = sizeof(std::intptr_t)) override;
	virtual void free(void* const ptr) noexcept override final;

protected:
	FreeBlock* m_freeBlocks;
	std::uint32_t m_numAllocations;
	std::size_t m_usedBytes;
};
