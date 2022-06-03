#pragma once

inline std::size_t align_forward_adjustment
(const void* const ptr, const std::size_t & alignment) noexcept
{
	const auto iptr = reinterpret_cast<std::uintptr_t>(ptr);
	const auto aligned = (iptr - 1u + alignment) & -alignment;
	return aligned - iptr;
}

inline void* ptr_add(const void* const p, const std::uintptr_t& amount) noexcept
{
	return reinterpret_cast<void*>
		(reinterpret_cast<std::uintptr_t>(p) + amount);
}
