#pragma once

#include <cstddef>
#include <cstdint>

class Allocator {

public:
	Allocator(const std::size_t sizeBytes, void* const start) noexcept;

	Allocator(const Allocator&) = delete;
	Allocator& operator=(Allocator&) = delete;
	Allocator(Allocator&&) noexcept;
	Allocator& operator=(Allocator&&) noexcept;

	virtual ~Allocator() noexcept = 0;

	virtual void* allocate(const std::size_t& size,
		const std::uintptr_t& alignment = sizeof(std::intptr_t)) = 0;

	virtual void free(void* const ptr) = 0;

	const std::size_t& getSize() const noexcept;
	const std::size_t& getUsed() const noexcept;
	const std::size_t& getNumAllocation() const noexcept;

	const void* getStart() const noexcept;

protected:

	std::size_t m_size;
	std::size_t m_usedBytes;
	std::size_t m_numAllocations;

	void* m_start;

};
