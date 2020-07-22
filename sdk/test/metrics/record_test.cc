#include <gtest/gtest.h>

#include "opentelemetry/sdk/metrics/record.h"

using namespace opentelemetry::sdk::metrics;

namespace metrics = opentelemetry::metrics;

TEST(Record, UseRecord)
{
  std::vector<int> tmp{1, 2, 3};
  Record r("Name", "Description", metrics::BoundInstrumentKind::BoundIntCounter,
           AggregatorKind::Counter, "la: bels", tmp, std::chrono::system_clock::now());
  ASSERT_STREQ(r.GetName().c_str(), "Name");
  ASSERT_STREQ(r.GetDescription().c_str(), "Description");
  ASSERT_EQ(r.GetInstrumentKind(), metrics::BoundInstrumentKind::BoundIntCounter);
  ASSERT_EQ(r.GetAggregatorKind(), AggregatorKind::Counter);
  ASSERT_STREQ(r.GetLabels().c_str(), "la: bels");
  std::vector<int> ans = opentelemetry::nostd::get<1>(r.GetValue());
  std::vector<int> correct{1, 2, 3};
  ASSERT_EQ(ans, correct);
}
