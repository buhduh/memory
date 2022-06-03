#pragma once

#include "allocator.hpp"

class LinearAllocator : public Allocator
{
public:
	LinearAllocator(const std::size_t sizeBytes,
					void* const start) noexcept;
	~LinearAllocator() noexcept;
	LinearAllocator(const LinearAllocator&) = delete;
	LinearAllocator& operator=(const LinearAllocator&)
		= delete;
	LinearAllocator(LinearAllocator&&) noexcept;
	LinearAllocator& operator=(LinearAllocator&&) noexcept;

	virtual void* allocate(const std::size_t& size,
						   const std::uintptr_t& alignment
						       = sizeof(std::intptr_t)) override;

	virtual void free(void* const ptr) noexcept override final;

	void* getCurrent() const noexcept;

	virtual void rewind(void* const mark) noexcept;
	void clear() noexcept;

protected:
	void* m_current;
};
