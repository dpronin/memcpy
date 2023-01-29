#include <cstddef>
#include <cstdint>

#include <benchmark/benchmark.h>

#include "common.hpp"

using namespace bench;

namespace {

void *memcpy_8b(std::byte *__restrict dst, std::byte const *__restrict src,
                size_t size) {
  uint64_t *dst64 = reinterpret_cast<uint64_t *>(dst);
  uint64_t const *src64 = reinterpret_cast<uint64_t const *>(src);
  for (size_t n = size >> 3; n; --n, dst64++, src64++)
    *dst64 = *src64;
  return dst;
}

void manual_memcpy_8b(benchmark::State &state) {
  auto [dst, src] = prepare_buffers(state.range(0));
  for (auto _ : state) {
    memcpy_8b(dst.get(), src.get(), state.range(0));
    benchmark::ClobberMemory();
  }
}

} // anonymous namespace

/* clang-format off */

BENCHMARK(manual_memcpy_8b)
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

/* clang-format on */
