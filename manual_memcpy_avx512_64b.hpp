#include <cstddef>

namespace detail {

inline void memcpy_avx512_64b(std::byte *__restrict dst,
                              std::byte const *__restrict src) {
  asm("vmovdqa64  %0,%%zmm0" : : "m"(src[0]));
  asm("vmovntdq %%zmm0,%0" : "=m"(dst[0]));
}

} // namespace detail

constexpr auto manual_memcpy_avx512_64b = [](std::byte *__restrict dst,
                                             std::byte const *__restrict src,
                                             size_t size) {
  for (size_t n = size >> 6, i = 0; i < n;
       ++i, dst += 1u << 6, src += 1u << 6) {

    /* prefetch each cache-line in 64B ahead from current source
     * position with 1KiB start offset */
    __builtin_prefetch(src + (1u << 10));

    detail::memcpy_avx512_64b(dst, src);
  }
  return dst;
};
