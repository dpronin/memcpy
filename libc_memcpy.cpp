#include <cstring>

#include <benchmark/benchmark.h>

#include "common.hpp"

using namespace bench;

namespace {

void libc_memcpy(benchmark::State &state) {
  auto [dst, src] = prepare_buffers(state.range(0));
  for (auto _ : state) {
    std::memcpy(dst.get(), src.get(), state.range(0));
    benchmark::ClobberMemory();
  }
}

} // namespace

/* clang-format off */

BENCHMARK(libc_memcpy)
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

/* clang-format on */
