#include <array>
#include <chrono>
#include <list>
#include <thread>
#include <vector>

#include <benchmark/benchmark.h>

void initialize(uint8_t& x)
{
    x = 0xaa;
}

template <size_t N>
void initialize(std::array<uint8_t, N>& x)
{
    for (auto& y : x) {
        initialize(y);
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
        static_cast<double>(item_size),
        benchmark::Counter::kAvgThreads,
        benchmark::Counter::kIs1024);
    ;
    state.counters["working_set_size"] = benchmark::Counter(
        static_cast<double>(item_size * container.size()),
        benchmark::Counter::kAvgThreads,
        benchmark::Counter::kIs1024);

    for (auto _ : state) {
        Container copy;
        copy = container;
    }

    state.SetBytesProcessed(
        int64_t(state.iterations()) * int64_t(state.range(0)) * item_size);
}

BENCHMARK_TEMPLATE(BM_Copy, std::vector<uint8_t>)
    ->RangeMultiplier(2)
    ->ThreadRange(1, std::thread::hardware_concurrency())
    ->UseRealTime()
    ->Range(1 << 10, 1 << 27);

BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 1>>)
    ->RangeMultiplier(4)
    ->ThreadRange(1, std::thread::hardware_concurrency())
    ->UseRealTime()
    ->Range(1 << 10, 1 << 22);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 16>>)
    ->RangeMultiplier(4)
    ->ThreadRange(1, std::thread::hardware_concurrency())
    ->UseRealTime()
    ->Range(1 << 6, 1 << 18);
BENCHMARK_TEMPLATE(BM_Copy, std::list<std::array<uint8_t, 256>>)
    ->RangeMultiplier(4)
    ->ThreadRange(1, std::thread::hardware_concurrency())
    ->UseRealTime()
    ->Range(1 << 2, 1 << 14);
