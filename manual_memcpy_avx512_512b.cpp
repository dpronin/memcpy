#include <cstddef>

#include <benchmark/benchmark.h>

#include "common.hpp"

using namespace bench;

namespace {

void memcpy_avx512_512b(std::byte *__restrict dst,
                        std::byte const *__restrict src) {
  asm("vmovdqa64  %0,%%zmm0" : : "m"(src[0]));
  asm("vmovdqa64  %0,%%zmm1" : : "m"(src[64]));
  asm("vmovdqa64  %0,%%zmm2" : : "m"(src[128]));
  asm("vmovdqa64  %0,%%zmm3" : : "m"(src[192]));
  asm("vmovdqa64  %0,%%zmm4" : : "m"(src[256]));
  asm("vmovdqa64  %0,%%zmm5" : : "m"(src[320]));
  asm("vmovdqa64  %0,%%zmm6" : : "m"(src[384]));
  asm("vmovdqa64  %0,%%zmm7" : : "m"(src[448]));
  asm("vmovntdq %%zmm0,%0" : "=m"(dst[0]));
  asm("vmovntdq %%zmm1,%0" : "=m"(dst[64]));
  asm("vmovntdq %%zmm2,%0" : "=m"(dst[128]));
  asm("vmovntdq %%zmm3,%0" : "=m"(dst[192]));
  asm("vmovntdq %%zmm4,%0" : "=m"(dst[256]));
  asm("vmovntdq %%zmm5,%0" : "=m"(dst[320]));
  asm("vmovntdq %%zmm6,%0" : "=m"(dst[384]));
  asm("vmovntdq %%zmm7,%0" : "=m"(dst[448]));
}

void *memcpy_avx512_512b(std::byte *__restrict dst,
                         std::byte const *__restrict src, size_t size) {
  for (size_t n = size >> 9, i = 0; i < n;
       ++i, dst += 1u << 9, src += 1u << 9) {

    /* prefetch each 512 bytes ahead from current source position */
    for (size_t i = 0; i < (1 << 3); ++i)
      __builtin_prefetch(src + (1u << 9) + (i << 6));

    memcpy_avx512_512b(dst, src);
  }
  return dst;
}

void manual_memcpy_avx512_512b(benchmark::State &state) {
  auto [dst, src] = prepare_buffers(state.range(0));
  for (auto _ : state) {
    memcpy_avx512_512b(dst.get(), src.get(), state.range(0));
    benchmark::ClobberMemory();
  }
}

} // anonymous namespace

/* clang-format off */

BENCHMARK(manual_memcpy_avx512_512b)
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

/* clang-format on */
