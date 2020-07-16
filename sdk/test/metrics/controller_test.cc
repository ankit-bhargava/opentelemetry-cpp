#include "opentelemetry/sdk/metrics/controller.h"

#include <gtest/gtest.h>
#include <thread>
#include <numeric>
// #include <chrono>

namespace metrics_api = opentelemetry::metrics;

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

// Test updating with a uniform set of updates
TEST(Controller, Constructor)
{
    Record r(std::vector<int>{1}, "first", "only instrument", "unitless");
    Record r1(std::vector<int>{2}, "first", "only instrument", "unitless");
    Record r2(std::vector<int>{3}, "first", "only instrument", "unitless");
    Record r3(std::vector<int>{4}, "first", "only instrument", "unitless");
    Record r4(std::vector<int>{5}, "first", "only instrument", "unitless");
    Record r5(std::vector<int>{6}, "first", "only instrument", "unitless");
    Record r6(std::vector<int>{7}, "first", "only instrument", "unitless");
    std::vector<Record> fabricated;
    fabricated.push_back(r);
    Meter m(fabricated);
    Exporter e;
    Processor p;
    
    PushController pc(m, e, p, 1, 30);
    pc.start();
    
    fabricated.push_back(r1);
    pc.meter_.collected_ = fabricated;
    sleep(1);
    fabricated.push_back(r2);
    pc.meter_.collected_ = fabricated;
    sleep(1);
    fabricated.push_back(r3);
    pc.meter_.collected_ = fabricated;
    sleep(1);
    fabricated.push_back(r4);
    pc.meter_.collected_ = fabricated;
    sleep(1);
    fabricated.push_back(r5);
    pc.meter_.collected_ = fabricated;
    sleep(1);
    fabricated.push_back(r6);
    pc.meter_.collected_ = fabricated;
    sleep(1);
    pc.stop(); //blocking
    std::cout <<"test complete" <<std::endl;
}


}  // namespace sdk
}  // namespace metrics
OPENTELEMETRY_END_NAMESPACE
