#include <cstddef>

#include <benchmark/benchmark.h>

#include "common.hpp"

using namespace bench;

namespace {

void memcpy_sse_256b(std::byte *__restrict dst,
                     std::byte const *__restrict src) {
  asm volatile("movdqa  %0,%%xmm0" : : "m"(src[0]));
  asm volatile("movdqa  %0,%%xmm1" : : "m"(src[16]));
  asm volatile("movdqa  %0,%%xmm2" : : "m"(src[32]));
  asm volatile("movdqa  %0,%%xmm3" : : "m"(src[48]));
  asm volatile("movdqa  %0,%%xmm4" : : "m"(src[64]));
  asm volatile("movdqa  %0,%%xmm5" : : "m"(src[80]));
  asm volatile("movdqa  %0,%%xmm6" : : "m"(src[96]));
  asm volatile("movdqa  %0,%%xmm7" : : "m"(src[112]));
  asm volatile("movdqa  %0,%%xmm8" : : "m"(src[128]));
  asm volatile("movdqa  %0,%%xmm9" : : "m"(src[144]));
  asm volatile("movdqa  %0,%%xmm10" : : "m"(src[160]));
  asm volatile("movdqa  %0,%%xmm11" : : "m"(src[176]));
  asm volatile("movdqa  %0,%%xmm12" : : "m"(src[192]));
  asm volatile("movdqa  %0,%%xmm13" : : "m"(src[208]));
  asm volatile("movdqa  %0,%%xmm14" : : "m"(src[224]));
  asm volatile("movdqa  %0,%%xmm15" : : "m"(src[240]));
  asm volatile("movntdq %%xmm0,%0" : "=m"(dst[0]));
  asm volatile("movntdq %%xmm1,%0" : "=m"(dst[16]));
  asm volatile("movntdq %%xmm2,%0" : "=m"(dst[32]));
  asm volatile("movntdq %%xmm3,%0" : "=m"(dst[48]));
  asm volatile("movntdq %%xmm4,%0" : "=m"(dst[64]));
  asm volatile("movntdq %%xmm5,%0" : "=m"(dst[80]));
  asm volatile("movntdq %%xmm6,%0" : "=m"(dst[96]));
  asm volatile("movntdq %%xmm7,%0" : "=m"(dst[112]));
  asm volatile("movntdq %%xmm8,%0" : "=m"(dst[128]));
  asm volatile("movntdq %%xmm9,%0" : "=m"(dst[144]));
  asm volatile("movntdq %%xmm10,%0" : "=m"(dst[160]));
  asm volatile("movntdq %%xmm11,%0" : "=m"(dst[176]));
  asm volatile("movntdq %%xmm12,%0" : "=m"(dst[192]));
  asm volatile("movntdq %%xmm13,%0" : "=m"(dst[208]));
  asm volatile("movntdq %%xmm14,%0" : "=m"(dst[224]));
  asm volatile("movntdq %%xmm15,%0" : "=m"(dst[240]));
}

void *memcpy_sse_256b(std::byte *__restrict dst,
                      std::byte const *__restrict src, size_t size) {
  for (size_t n = size >> 8, i = 0; i < n;
       ++i, dst += 1u << 8, src += 1u << 8) {

    /* prefetch each 256 bytes ahead from current source position */
    for (size_t i = 0; i < (1 << 2); ++i)
      __builtin_prefetch(src + ((1u << 8) + (i << 6)));

    memcpy_sse_256b(dst, src);
  }
  return dst;
}

void manual_memcpy_sse_256b(benchmark::State &state) {
  auto [dst, src] = prepare_buffers(state.range(0));
  for (auto _ : state) {
    memcpy_sse_256b(dst.get(), src.get(), state.range(0));
    benchmark::ClobberMemory();
  }
}

} // anonymous namespace

/* clang-format off */

BENCHMARK(manual_memcpy_sse_256b)
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

/* clang-format on */
