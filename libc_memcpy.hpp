#pragma once

#include <cstddef>
#include <cstring>

constexpr auto libc_memcpy = [](std::byte *__restrict dst,
                                std::byte const *__restrict src,
                                size_t sz) { std::memcpy(dst, src, sz); };
