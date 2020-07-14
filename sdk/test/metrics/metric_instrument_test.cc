#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "opentelemetry/sdk/metrics/sync_instruments.h"
#include "opentelemetry/sdk/metrics/async_instruments.h"
#include <map>
#include <thread>

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

TEST(IntCounter, InstrumentFunctions)
{
  IntCounter alpha("enabled", "no description", "unitless", true);
  IntCounter beta("not enabled", "some description", "units", false);

  EXPECT_EQ(alpha.GetName(), "enabled");
  EXPECT_EQ(alpha.GetDescription(), "no description");
  EXPECT_EQ(alpha.GetUnits(), "unitless");
  EXPECT_EQ(alpha.IsEnabled(), true);

  EXPECT_EQ(beta.GetName(), "not enabled");
  EXPECT_EQ(beta.GetDescription(), "some description");
  EXPECT_EQ(beta.GetUnits(), "units");
  EXPECT_EQ(beta.IsEnabled(), false);
}

TEST(IntCounter, Binding)
{
  IntCounter alpha("test", "none", "unitless", true);

  std::map<std::string, std::string> labels = {{"key", "value"}};
  std::map<std::string, std::string> labels1 = {{"key1", "value1"}};
  std::map<std::string, std::string> labels2 = {{"key2", "value2"}, {"key3", "value3"}};
  std::map<std::string, std::string> labels3 = {{"key3", "value3"}, {"key2", "value2"}};

  auto beta = alpha.bind(labels);
  auto gamma = alpha.bind(labels1);
  auto delta = alpha.bind(labels1);
  auto epsilon = alpha.bind(labels1);
  auto zeta = alpha.bind(labels2);
  auto eta = alpha.bind(labels3);

  EXPECT_EQ (beta->get_ref(), 1);
  EXPECT_EQ(gamma->get_ref(),3);
  EXPECT_EQ(eta->get_ref(),2);

  delta->unbind();
  gamma->unbind();
  epsilon->unbind();

  EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_ref(), 0);
  EXPECT_EQ(alpha.boundInstruments_.size(), 3);
}

void counterCallback(IntCounter & in, int freq, std::map<std::string, std::string> labels){
  for (int i=0; i<freq; i++){
    in.add(1, labels);
  }
  
}

TEST(IntCounter, StressAdd){
  IntCounter alpha("test", "none", "unitless", true);

  std::map<std::string, std::string> labels = {{"key", "value"}};
  std::map<std::string, std::string> labels1 = {{"key1", "value1"}};

  std::thread first (counterCallback, std::ref(alpha), 1234, labels);     // spawn new threads that call the callback
  std::thread second (counterCallback, std::ref(alpha), 1234, labels);
  std::thread third (counterCallback, std::ref(alpha), 5678, labels1);

  first.join();                
  second.join();               
  third.join();

  // where is the checkpoint being called?? THIS SHOULDNT WORK

  EXPECT_EQ(alpha.boundInstruments_[mapToString(labels)]->get_aggregator()->get_values()[0], 1234*2);
  EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_aggregator()->get_values()[0], 5678);
}

// TEST(UpDownCounter, DefaultConstruction)
// {
//   NoopIntUpDownCounter alpha("test", "none", "unitless", true);
//   NoopDoubleUpDownCounter beta("other", "none", "unitless", true);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};

//   alpha.bind(labelkv);

//   auto gamma = alpha.bind(labelkv);
//   auto delta = beta.bind(labelkv);

//   gamma->unbind();
//   delta->unbind();
// }

// TEST(UpDownCounter, Add)
// {
//   NoopIntUpDownCounter alpha("test", "none", "unitless", true);
//   NoopDoubleUpDownCounter beta("other", "none", "unitless", true);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};

//   alpha.add(1, labelkv);
//   beta.add(1.0, labelkv);

//   auto gamma = alpha.bind(labelkv);
//   auto delta = beta.bind(labelkv);

//   gamma->add(1);
//   delta->add(1.0);
//   gamma->add(-1);
//   delta->add(-1.0);

//   gamma->unbind();
//   delta->unbind();
// }

// TEST(ValueRecorder, DefaultConstruction)
// {
//   NoopIntValueRecorder alpha("test", "none", "unitless", true);
//   NoopDoubleValueRecorder beta("other", "none", "unitless", true);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};

//   alpha.bind(labelkv);

//   auto gamma = alpha.bind(labelkv);
//   auto delta = beta.bind(labelkv);

//   gamma->unbind();
//   delta->unbind();
// }

// TEST(ValueRecorder, Record)
// {
//   NoopIntValueRecorder alpha("test", "none", "unitless", true);
//   NoopDoubleValueRecorder beta("other", "none", "unitless", true);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};

//   alpha.record(1, labelkv);
//   beta.record(1.0, labelkv);

//   auto gamma = alpha.bind(labelkv);
//   auto delta = beta.bind(labelkv);

//   gamma->record(1);
//   delta->record(1.0);

//   gamma->unbind();
//   delta->unbind();
// }

// void noopIntCallback(ObserverResult result)
// {
//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};
//   result.observe(1, labelkv);
//   result.observe(-1, labelkv);
// }

// void noopDoubleCallback(ObserverResult result)
// {
//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};
//   result.observe(1.0, labelkv);
//   result.observe(-1.0, labelkv);
// }

// TEST(ValueObserver, Observe)
// {
//   NoopIntValueObserver alpha("test", "none", "unitless", true, &noopIntCallback);

//   NoopDoubleValueObserver beta("test", "none", "unitless", true, &noopDoubleCallback);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};

//   alpha.observe(1, labelkv);
//   beta.observe(1.0, labelkv);
// }

// TEST(SumObserver, DefaultConstruction)
// {
//   NoopIntSumObserver alpha("test", "none", "unitless", true, &noopIntCallback);

//   NoopDoubleSumObserver beta("test", "none", "unitless", true, &noopDoubleCallback);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};

//   alpha.observe(1, labelkv);
//   beta.observe(1.0, labelkv);
// }

// TEST(UpDownSumObserver, DefaultConstruction)
// {
//   NoopIntUpDownSumObserver alpha("test", "none", "unitless", true, &noopIntCallback);

//   NoopDoubleUpDownSumObserver beta("test", "none", "unitless", true, &noopDoubleCallback);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   auto labelkv = trace::KeyValueIterableView<decltype(labels)>{labels};

//   alpha.observe(1, labelkv);
//   beta.observe(1.0, labelkv);
//   alpha.observe(-1, labelkv);
//   beta.observe(-1.0, labelkv);
// }

} //namespace sdk
}  // namespace metrics
OPENTELEMETRY_END_NAMESPACE