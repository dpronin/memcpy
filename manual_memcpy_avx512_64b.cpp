#include <cstddef>

#include <memory>

#include <benchmark/benchmark.h>

#include "common.hpp"

using namespace bench;

namespace {

void memcpy_avx512_64b(std::byte *__restrict dst,
                       std::byte const *__restrict src) {
  asm("vmovdqa64  %0,%%zmm0" : : "m"(src[0]));
  asm("vmovntdq %%zmm0,%0" : "=m"(dst[0]));
}

void *memcpy_avx512_64b(std::byte *__restrict dst,
                        std::byte const *__restrict src, size_t size) {
  for (size_t n = size >> 6, i = 0; i < n;
       ++i, dst += 1u << 6, src += 1u << 6) {

    /* prefetch each cache-line in 64B ahead from current source
     * position with 1KiB start offset */
    __builtin_prefetch(src + (1u << 10));

    memcpy_avx512_64b(dst, src);
  }
  return dst;
}

void manual_memcpy_avx512_64b(benchmark::State &state) {
  auto [dst, src] = prepare_buffers(state.range(0));
  for (auto _ : state) {
    memcpy_avx512_64b(dst.get(), src.get(), state.range(0));
    benchmark::ClobberMemory();
  }
}

} // anonymous namespace

/* clang-format off */

BENCHMARK(manual_memcpy_avx512_64b)
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

/* clang-format on */
