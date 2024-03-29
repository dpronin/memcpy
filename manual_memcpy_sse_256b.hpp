#include <cstddef>

namespace detail {

inline void memcpy_sse_256b(std::byte *__restrict dst,
                            std::byte const *__restrict src) {
  asm("movdqa  %0,%%xmm0" : : "m"(src[0]));
  asm("movdqa  %0,%%xmm1" : : "m"(src[16]));
  asm("movdqa  %0,%%xmm2" : : "m"(src[32]));
  asm("movdqa  %0,%%xmm3" : : "m"(src[48]));
  asm("movdqa  %0,%%xmm4" : : "m"(src[64]));
  asm("movdqa  %0,%%xmm5" : : "m"(src[80]));
  asm("movdqa  %0,%%xmm6" : : "m"(src[96]));
  asm("movdqa  %0,%%xmm7" : : "m"(src[112]));
  asm("movdqa  %0,%%xmm8" : : "m"(src[128]));
  asm("movdqa  %0,%%xmm9" : : "m"(src[144]));
  asm("movdqa  %0,%%xmm10" : : "m"(src[160]));
  asm("movdqa  %0,%%xmm11" : : "m"(src[176]));
  asm("movdqa  %0,%%xmm12" : : "m"(src[192]));
  asm("movdqa  %0,%%xmm13" : : "m"(src[208]));
  asm("movdqa  %0,%%xmm14" : : "m"(src[224]));
  asm("movdqa  %0,%%xmm15" : : "m"(src[240]));
  asm("movntdq %%xmm0,%0" : "=m"(dst[0]));
  asm("movntdq %%xmm1,%0" : "=m"(dst[16]));
  asm("movntdq %%xmm2,%0" : "=m"(dst[32]));
  asm("movntdq %%xmm3,%0" : "=m"(dst[48]));
  asm("movntdq %%xmm4,%0" : "=m"(dst[64]));
  asm("movntdq %%xmm5,%0" : "=m"(dst[80]));
  asm("movntdq %%xmm6,%0" : "=m"(dst[96]));
  asm("movntdq %%xmm7,%0" : "=m"(dst[112]));
  asm("movntdq %%xmm8,%0" : "=m"(dst[128]));
  asm("movntdq %%xmm9,%0" : "=m"(dst[144]));
  asm("movntdq %%xmm10,%0" : "=m"(dst[160]));
  asm("movntdq %%xmm11,%0" : "=m"(dst[176]));
  asm("movntdq %%xmm12,%0" : "=m"(dst[192]));
  asm("movntdq %%xmm13,%0" : "=m"(dst[208]));
  asm("movntdq %%xmm14,%0" : "=m"(dst[224]));
  asm("movntdq %%xmm15,%0" : "=m"(dst[240]));
}

} // namespace detail

constexpr auto manual_memcpy_sse_256b = [](std::byte *__restrict dst,
                                           std::byte const *__restrict src,
                                           size_t size) {
  for (size_t n = size >> 8, i = 0; i < n;
       ++i, dst += 1u << 8, src += 1u << 8) {

    /* prefetch each 256B ahead from current source position with 8KiB
     * start offset */
    for (size_t i = 0; i < (1 << 2); ++i)
      __builtin_prefetch(src + (1u << 13) + (i << 6));

    detail::memcpy_sse_256b(dst, src);
  }
  return dst;
};
