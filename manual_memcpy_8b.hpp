#pragma once

#include <cstddef>
#include <cstdint>

constexpr auto manual_memcpy_8b = [](std::byte *__restrict dst,
                                     std::byte const *__restrict src,
                                     size_t size) {
  uint64_t *dst64 = reinterpret_cast<uint64_t *>(dst);
  uint64_t const *src64 = reinterpret_cast<uint64_t const *>(src);
  for (size_t n = size >> 3; n; --n, dst64++, src64++)
    *dst64 = *src64;
  return dst;
};
