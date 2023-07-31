#include <cstddef>

#include <concepts>

#include <benchmark/benchmark.h>

#include "common.hpp"

#include "libc_memcpy.hpp"
#include "manual_memcpy_8b.hpp"
#include "manual_memcpy_avx512_2048b.hpp"
#include "manual_memcpy_avx512_512b.hpp"
#include "manual_memcpy_avx512_64b.hpp"
#include "manual_memcpy_sse_256b.hpp"

using namespace bench;

namespace {

template <std::invocable<std::byte *, std::byte const *, size_t> F>
void memcpy_bench(benchmark::State &state) {
  auto f = F{};
  auto [dst, src] = prepare_buffers(state.range(0));
  for (auto _ : state) {
    for (auto i{0}; i < 4; ++i) {
      f(dst.get(), src.get(), state.range(0));
      benchmark::ClobberMemory();
    }
  }
}

} // namespace

/* clang-format off */

BENCHMARK_TEMPLATE(memcpy_bench, decltype(libc_memcpy))
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(memcpy_bench, decltype(manual_memcpy_8b))
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(memcpy_bench, decltype(manual_memcpy_sse_256b))
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(memcpy_bench, decltype(manual_memcpy_avx512_64b))
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(memcpy_bench, decltype(manual_memcpy_avx512_512b))
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(memcpy_bench, decltype(manual_memcpy_avx512_2048b))
    ->Arg(1u << 30)
    ->Unit(benchmark::kMillisecond);

/* clang-format on */

BENCHMARK_MAIN();
