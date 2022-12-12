#include <array>
#include <chrono>
#include <list>
#include <vector>

#include <benchmark/benchmark.h>

template <size_t N>
void initialize(std::array<uint8_t, N>& x)
{
    for (auto& y : x) {
        y = 0xaa;
    }
}

template <typename Container>
static void BM_Copy(benchmark::State& state)
{
    Container container;
    container.resize(state.range(0));
    for (auto& item : container) {
        initialize(item);
    }
    auto const item_size = sizeof(container.front());
    state.counters["item_size"] = benchmark::Counter(
        static_cast<double>(item_size * container.size()),
        benchmark::Counter::kDefaults,
        benchmark::Counter::kIs1024);
    ;
    state.counters["working_set_size"] = benchmark::Counter(
        static_cast<double>(item_size * container.size()),
        benchmark::Counter::kDefaults,
        benchmark::Counter::kIs1024);

    for (auto _ : state) {
        Container copy;
        auto start = std::chrono::high_resolution_clock::now();
        copy = container;
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_seconds =
            std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        state.SetIterationTime(elapsed_seconds.count());
    }

    state.SetBytesProcessed(
        int64_t(state.iterations()) * int64_t(state.range(0)) * item_size);
}

BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 1>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 30);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 2>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 29);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 4>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 28);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 8>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 27);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 16>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 26);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 32>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 25);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 64>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 24);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 128>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 23);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 256>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 22);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 512>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 21);
BENCHMARK_TEMPLATE(BM_Copy, std::vector<std::array<uint8_t, 1024>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 20);

BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 1>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 22);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 2>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 21);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 4>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 20);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 8>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 19);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 16>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 18);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 32>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 17);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 64>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 16);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 128>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 15);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 256>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 14);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 512>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 13);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 1024>>)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 12);
