#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <concepts>
#include <memory>
#include <random>
#include <utility>

#include <unistd.h>

namespace bench {

namespace detail {
constexpr auto div_round_up(std::unsigned_integral auto x,
                            std::unsigned_integral auto y) noexcept {
  assert(0 != y);
  return (x + y - 1) / y;
}

} // namespace detail

template <typename T> class aligned_delete {
public:
  explicit aligned_delete(std::align_val_t align) : align_(align) {}

  void operator()(T *p) { ::operator delete(p, align_); }

private:
  std::align_val_t const align_;
};

template <typename T> class aligned_delete<T[]> {
public:
  explicit aligned_delete(std::align_val_t align) : align_(align) {}

  void operator()(T *p) { ::operator delete[](p, align_); }

private:
  std::align_val_t const align_;
};

inline auto make_unique_aligned_bytes(size_t align, size_t sz) {
  auto const align_val = std::align_val_t{align};
  return std::unique_ptr<std::byte, aligned_delete<std::byte[]>>{
      new (align_val) std::byte[sz], aligned_delete<std::byte[]>(align_val)};
}

inline auto make_buffer(size_t align, size_t page_size, size_t sz) {
  auto buf = make_unique_aligned_bytes(align, sz);
  /* initialize a first byte of each page to prevent page faults while
   * benchmarking */
  for (size_t i = 0, n = detail::div_round_up(sz, page_size); i < n; ++i)
    buf.get()[i * page_size] = static_cast<std::byte>(std::rand());
  return buf;
}

inline auto prepare_buffers(size_t sz) {
  auto const page_size = sysconf(_SC_PAGESIZE);
  if (page_size < 0)
    std::terminate();
  auto dst = make_buffer(page_size, page_size, sz);
  auto src = make_buffer(page_size, page_size, sz);
  return std::pair{std::move(dst), std::move(src)};
}

} // namespace bench
