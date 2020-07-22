#include <gtest/gtest.h>
#include "opentelemetry/sdk/metrics/meter.h"
#include "opentelemetry/trace/key_value_iterable_view.h"
#include <variant>

using namespace opentelemetry::sdk::metrics;
namespace metrics_api = opentelemetry::metrics;

TEST(Meter, InstrumentConstructors)
{
  // Test all NewInstrument functions
  // Check that you can't create two instruments with same name

  auto m = std::unique_ptr<Meter>(new Meter("Test"));

  m->NewShortCounter("Name", "Description", "unit", true);
  m->NewIntCounter("Name", "Description", "unit", true);
  m->NewFloatCounter("Name", "Description", "unit", true);
  m->NewDoubleCounter("Name", "Description", "unit", true);

}

TEST(Meter, Collect)
{
  // Test that a collect call produces the correct output.

  auto m = std::unique_ptr<Meter>(new Meter("Test"));

  auto short_counter = m->NewShortCounter("Name", "Description", "unit", true);
  auto int_counter = m->NewIntCounter("Name", "Description", "unit", true);

  std::map<std::string, std::string> labels = {{"key", "value"}};
  auto labelkv = opentelemetry::trace::KeyValueIterableView<decltype(labels)>{labels};

    // DOESNT WORK WITH API STUFF YET LOL SORRY, BUT WORKS WITH ACTUAL MAPS :)
  short_counter->update(5, labels);
  int_counter->update(10, labels);

  auto ans = m->Collect();

    ASSERT_EQ(short_counter->GetBoundInstruments().begin()->second->GetAggregator()->get_values()[0], 5);
    ASSERT_EQ(int_counter->GetBoundInstruments().begin()->second->GetAggregator()->get_values()[0], 10);
}
//
//TEST(Meter, RemoveInactiveInstruments)
//{
//  // Create a metric instrument then bind that instrument but don't capture the return pointer.
//  // Then call collect, afterwards the bound instrument should be removed from the instruments
//  // bound_instruments map.
//}
//
//TEST(Meter, RecordBatch)
//{
//  // Test that RecordBatch applies the labels and values to the instruments passed to the
//  // function as parameters.
//
//}
