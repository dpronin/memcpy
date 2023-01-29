#include <cstddef>

#include <benchmark/benchmark.h>

#include "common.hpp"

using namespace bench;

namespace {

void memcpy_avx512_2048b(std::byte *__restrict dst,
                         std::byte const *__restrict src) {
  asm("vmovdqa64  %0,%%zmm0" : : "m"(src[0]));
  asm("vmovdqa64  %0,%%zmm1" : : "m"(src[64]));
  asm("vmovdqa64  %0,%%zmm2" : : "m"(src[128]));
  asm("vmovdqa64  %0,%%zmm3" : : "m"(src[192]));
  asm("vmovdqa64  %0,%%zmm4" : : "m"(src[256]));
  asm("vmovdqa64  %0,%%zmm5" : : "m"(src[320]));
  asm("vmovdqa64  %0,%%zmm6" : : "m"(src[384]));
  asm("vmovdqa64  %0,%%zmm7" : : "m"(src[448]));
  asm("vmovdqa64  %0,%%zmm8" : : "m"(src[512]));
  asm("vmovdqa64  %0,%%zmm9" : : "m"(src[576]));
  asm("vmovdqa64  %0,%%zmm10" : : "m"(src[640]));
  asm("vmovdqa64  %0,%%zmm11" : : "m"(src[704]));
  asm("vmovdqa64  %0,%%zmm12" : : "m"(src[768]));
  asm("vmovdqa64  %0,%%zmm13" : : "m"(src[832]));
  asm("vmovdqa64  %0,%%zmm14" : : "m"(src[896]));
  asm("vmovdqa64  %0,%%zmm15" : : "m"(src[960]));
  asm("vmovdqa64  %0,%%zmm16" : : "m"(src[1024]));
  asm("vmovdqa64  %0,%%zmm17" : : "m"(src[1088]));
  asm("vmovdqa64  %0,%%zmm18" : : "m"(src[1152]));
  asm("vmovdqa64  %0,%%zmm19" : : "m"(src[1216]));
  asm("vmovdqa64  %0,%%zmm20" : : "m"(src[1280]));
  asm("vmovdqa64  %0,%%zmm21" : : "m"(src[1344]));
  asm("vmovdqa64  %0,%%zmm22" : : "m"(src[1408]));
  asm("vmovdqa64  %0,%%zmm23" : : "m"(src[1472]));
  asm("vmovdqa64  %0,%%zmm24" : : "m"(src[1536]));
  asm("vmovdqa64  %0,%%zmm25" : : "m"(src[1600]));
  asm("vmovdqa64  %0,%%zmm26" : : "m"(src[1664]));
  asm("vmovdqa64  %0,%%zmm27" : : "m"(src[1728]));
  asm("vmovdqa64  %0,%%zmm28" : : "m"(src[1792]));
  asm("vmovdqa64  %0,%%zmm29" : : "m"(src[1856]));
  asm("vmovdqa64  %0,%%zmm30" : : "m"(src[1920]));
  asm("vmovdqa64  %0,%%zmm31" : : "m"(src[1984]));
  asm("vmovntdq %%zmm0,%0" : "=m"(dst[0]));
  asm("vmovntdq %%zmm1,%0" : "=m"(dst[64]));
  asm("vmovntdq %%zmm2,%0" : "=m"(dst[128]));
  asm("vmovntdq %%zmm3,%0" : "=m"(dst[192]));
  asm("vmovntdq %%zmm4,%0" : "=m"(dst[256]));
  asm("vmovntdq %%zmm5,%0" : "=m"(dst[320]));
  asm("vmovntdq %%zmm6,%0" : "=m"(dst[384]));
  asm("vmovntdq %%zmm7,%0" : "=m"(dst[448]));
  asm("vmovntdq %%zmm8,%0" : "=m"(dst[512]));
  asm("vmovntdq %%zmm9,%0" : "=m"(dst[576]));
  asm("vmovntdq %%zmm10,%0" : "=m"(dst[640]));
  asm("vmovntdq %%zmm11,%0" : "=m"(dst[704]));
  asm("vmovntdq %%zmm12,%0" : "=m"(dst[768]));
  asm("vmovntdq %%zmm13,%0" : "=m"(dst[832]));
  asm("vmovntdq %%zmm14,%0" : "=m"(dst[896]));
  asm("vmovntdq %%zmm15,%0" : "=m"(dst[960]));
  asm("vmovntdq %%zmm16,%0" : "=m"(dst[1024]));
  asm("vmovntdq %%zmm17,%0" : "=m"(dst[1088]));
  asm("vmovntdq %%zmm18,%0" : "=m"(dst[1152]));
  asm("vmovntdq %%zmm19,%0" : "=m"(dst[1216]));
  asm("vmovntdq %%zmm20,%0" : "=m"(dst[1280]));
  asm("vmovntdq %%zmm21,%0" : "=m"(dst[1344]));
  asm("vmovntdq %%zmm22,%0" : "=m"(dst[1408]));
  asm("vmovntdq %%zmm23,%0" : "=m"(dst[1472]));
  asm("vmovntdq %%zmm24,%0" : "=m"(dst[1536]));
  asm("vmovntdq %%zmm25,%0" : "=m"(dst[1600]));
  asm("vmovntdq %%zmm26,%0" : "=m"(dst[1664]));
  asm("vmovntdq %%zmm27,%0" : "=m"(dst[1728]));
  asm("vmovntdq %%zmm28,%0" : "=m"(dst[1792]));
  asm("vmovntdq %%zmm29,%0" : "=m"(dst[1856]));
  asm("vmovntdq %%zmm30,%0" : "=m"(dst[1920]));
  asm("vmovntdq %%zmm31,%0" : "=m"(dst[1984]));
}

void *memcpy_avx512_2048b(std::byte *__restrict dst,
                          std::byte const *__restrict src, size_t size) {
  for (size_t n = size >> 11; n; --n, dst += 1u << 11, src += 1u << 11) {
    /* prefetch each 2 KiB ahead from current source position */
    for (size_t i = 0; i < 32; ++i)
      __builtin_prefetch(src + ((1u << 11) + (i << 6)));
    memcpy_avx512_2048b(dst, src);
  }
  return dst;
}

void manual_memcpy_avx512_2048b(benchmark::State &state) {
  auto [dst, src] = prepare_buffers(state.range(0));
  for (auto _ : state) {
    memcpy_avx512_2048b(dst.get(), src.get(), state.range(0));
    benchmark::ClobberMemory();
  }
}

} // anonymous namespace

/* clang-format off */

BENCHMARK(manual_memcpy_avx512_2048b)
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

/* clang-format on */
