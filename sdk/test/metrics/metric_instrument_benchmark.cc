#include "opentelemetry/sdk/metrics/sync_instruments.h"
#include "opentelemetry/sdk/metrics/async_instruments.h"

#include <cstring>
#include <string>
#include <map>
#include <thread>
#include <memory>
#include <iostream>
#include <benchmark/benchmark.h>
#include <cstdint>


OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

void BindRefCount(benchmark::State &state){
    for (auto _ : state) {
        
        
        Counter<int> alpha("test", "none", "unitless", true);
        
        std::map<std::string, std::string> labels = {{"key", "value"}};
        std::map<std::string, std::string> labels1 = {{"key1", "value1"}};
        std::map<std::string, std::string> labels2 = {{"key2", "value2"}, {"key3", "value3"}};
        std::map<std::string, std::string> labels3 = {{"key3", "value3"}, {"key2", "value2"}};
        
        
        auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};
        auto labelkv1 = trace::KeyValueIterableView<decltype(labels1)>{labels1};
        auto labelkv2 = trace::KeyValueIterableView<decltype(labels2)>{labels2};
        auto labelkv3 = trace::KeyValueIterableView<decltype(labels3)>{labels3};
        
        auto beta = alpha.bindCounter(labelkv);
        auto gamma = alpha.bindCounter(labelkv1);
        auto delta = alpha.bindCounter(labelkv1);
        auto epsilon = alpha.bindCounter(labelkv1);
        auto zeta = alpha.bindCounter(labelkv2);
        auto eta = alpha.bindCounter(labelkv3);
        
        beta->get_ref();
        gamma->get_ref();
        eta->get_ref();
        
        delta->unbind();
        gamma->unbind();
        epsilon->unbind();
        
        alpha.boundInstruments_[KvToString(labelkv1)]->get_ref();
        alpha.boundInstruments_.size();
    }
}
BENCHMARK(BindRefCount);

} //namespace metrics
} //namespace sdk
OPENTELEMETRY_END_NAMESPACE

BENCHMARK_MAIN();
