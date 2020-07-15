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

// TEST(IntCounter, InstrumentFunctions)
// {
//   IntCounter alpha("enabled", "no description", "unitless", true);
//   IntCounter beta("not enabled", "some description", "units", false);

//   EXPECT_EQ(alpha.GetName(), "enabled");
//   EXPECT_EQ(alpha.GetDescription(), "no description");
//   EXPECT_EQ(alpha.GetUnits(), "unitless");
//   EXPECT_EQ(alpha.IsEnabled(), true);

//   EXPECT_EQ(beta.GetName(), "not enabled");
//   EXPECT_EQ(beta.GetDescription(), "some description");
//   EXPECT_EQ(beta.GetUnits(), "units");
//   EXPECT_EQ(beta.IsEnabled(), false);
// }

// TEST(IntCounter, Binding)
// {
//   IntCounter alpha("test", "none", "unitless", true);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   std::map<std::string, std::string> labels1 = {{"key1", "value1"}};
//   std::map<std::string, std::string> labels2 = {{"key2", "value2"}, {"key3", "value3"}};
//   std::map<std::string, std::string> labels3 = {{"key3", "value3"}, {"key2", "value2"}};

//   auto beta = alpha.bind(labels);
//   auto gamma = alpha.bind(labels1);
//   auto delta = alpha.bind(labels1);
//   auto epsilon = alpha.bind(labels1);
//   auto zeta = alpha.bind(labels2);
//   auto eta = alpha.bind(labels3);

//   EXPECT_EQ (beta->get_ref(), 1);
//   EXPECT_EQ(gamma->get_ref(),3);
//   EXPECT_EQ(eta->get_ref(),2);

//   delta->unbind();
//   gamma->unbind();
//   epsilon->unbind();

//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_ref(), 0);
//   EXPECT_EQ(alpha.boundInstruments_.size(), 3);
// }

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

// void IntCallback(ObserverResult result)
// {
//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   result.observe(1, labels);
//   result.observe(-1, labels);
// }

// TEST (IntValueObserver, InstrumentFunctions){
//   std::shared_ptr<IntValueObserver> alpha(new IntValueObserver("test", "none", "unitless", true, &IntCallback));
//   //ObserverResult beta(alpha);
// }

// TEST(IntUpDownCounter, InstrumentFunctions)
// {
//   IntUpDownCounter alpha("enabled", "no description", "unitless", true);
//   IntUpDownCounter beta("not enabled", "some description", "units", false);

//   EXPECT_EQ(alpha.GetName(), "enabled");
//   EXPECT_EQ(alpha.GetDescription(), "no description");
//   EXPECT_EQ(alpha.GetUnits(), "unitless");
//   EXPECT_EQ(alpha.IsEnabled(), true);

//   EXPECT_EQ(beta.GetName(), "not enabled");
//   EXPECT_EQ(beta.GetDescription(), "some description");
//   EXPECT_EQ(beta.GetUnits(), "units");
//   EXPECT_EQ(beta.IsEnabled(), false);
// }

// TEST(IntUpDownCounter, Binding)
// {
//   IntUpDownCounter alpha("test", "none", "unitless", true);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   std::map<std::string, std::string> labels1 = {{"key1", "value1"}};
//   std::map<std::string, std::string> labels2 = {{"key2", "value2"}, {"key3", "value3"}};
//   std::map<std::string, std::string> labels3 = {{"key3", "value3"}, {"key2", "value2"}};

//   auto beta = alpha.bind(labels);
//   auto gamma = alpha.bind(labels1);
//   auto delta = alpha.bind(labels1);
//   auto epsilon = alpha.bind(labels1);
//   auto zeta = alpha.bind(labels2);
//   auto eta = alpha.bind(labels3);

//   EXPECT_EQ (beta->get_ref(), 1);
//   EXPECT_EQ(gamma->get_ref(),3);
//   EXPECT_EQ(eta->get_ref(),2);

//   delta->unbind();
//   gamma->unbind();
//   epsilon->unbind();

//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_ref(), 0);
//   EXPECT_EQ(alpha.boundInstruments_.size(), 3);
// }

// void upDownCounterCallback(IntUpDownCounter & in, int freq, std::map<std::string, std::string> labels){
//   for (int i=0; i<freq; i++){
//     in.add(1, labels);
//   }
  
// }

// void negUpDownCounterCounterCallback(IntUpDownCounter & in, int freq, std::map<std::string, std::string> labels){
//   for (int i=0; i<freq; i++){
//     in.add(-1, labels);
//   }
  
// }

// TEST(IntUpDownCounter, StressAdd){
//   IntUpDownCounter alpha("test", "none", "unitless", true);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   std::map<std::string, std::string> labels1 = {{"key1", "value1"}};

//   std::thread first (upDownCounterCallback, std::ref(alpha), 1234, labels);     // spawn new threads that call the callback
//   std::thread second (upDownCounterCallback, std::ref(alpha), 1234, labels);
//   std::thread third (upDownCounterCallback, std::ref(alpha), 5678, labels1);
//   std::thread fourth (negUpDownCounterCounterCallback, std::ref(alpha), 1234, labels1); // negative values

//   first.join();                
//   second.join();               
//   third.join();
//   fourth.join();

//   // where is the checkpoint being called?? THIS SHOULDNT WORK

//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels)]->get_aggregator()->get_values()[0], 1234*2);
//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_aggregator()->get_values()[0], 5678-1234);
// }

// TEST(IntValueRecorder, InstrumentFunctions)
// {
//   IntValueRecorder alpha("enabled", "no description", "unitless", true);
//   IntValueRecorder beta("not enabled", "some description", "units", false);

//   EXPECT_EQ(alpha.GetName(), "enabled");
//   EXPECT_EQ(alpha.GetDescription(), "no description");
//   EXPECT_EQ(alpha.GetUnits(), "unitless");
//   EXPECT_EQ(alpha.IsEnabled(), true);

//   EXPECT_EQ(beta.GetName(), "not enabled");
//   EXPECT_EQ(beta.GetDescription(), "some description");
//   EXPECT_EQ(beta.GetUnits(), "units");
//   EXPECT_EQ(beta.IsEnabled(), false);
// }

// TEST(IntValueRecorder, Binding)
// {
//   IntValueRecorder alpha("test", "none", "unitless", true);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   std::map<std::string, std::string> labels1 = {{"key1", "value1"}};
//   std::map<std::string, std::string> labels2 = {{"key2", "value2"}, {"key3", "value3"}};
//   std::map<std::string, std::string> labels3 = {{"key3", "value3"}, {"key2", "value2"}};

//   auto beta = alpha.bind(labels);
//   auto gamma = alpha.bind(labels1);
//   auto delta = alpha.bind(labels1);
//   auto epsilon = alpha.bind(labels1);
//   auto zeta = alpha.bind(labels2);
//   auto eta = alpha.bind(labels3);

//   EXPECT_EQ (beta->get_ref(), 1);
//   EXPECT_EQ(gamma->get_ref(),3);
//   EXPECT_EQ(eta->get_ref(),2);

//   delta->unbind();
//   gamma->unbind();
//   epsilon->unbind();

//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_ref(), 0);
//   EXPECT_EQ(alpha.boundInstruments_.size(), 3);
// }

// void recorderCallback(IntValueRecorder & in, int freq, std::map<std::string, std::string> labels){
//   for (int i=0; i<freq; i++){
//     in.record(i, labels);
//   }
  
// }

// void negRecorderCallback(IntValueRecorder & in, int freq, std::map<std::string, std::string> labels){
//   for (int i=0; i<freq; i++){
//     in.record(-1*i, labels);
//   }
  
// }

// TEST(IntValueRecorder, StressRecord){
//   IntValueRecorder alpha("test", "none", "unitless", true);

//   std::map<std::string, std::string> labels = {{"key", "value"}};
//   std::map<std::string, std::string> labels1 = {{"key1", "value1"}};

//   std::thread first (recorderCallback, std::ref(alpha), 25, labels);     // spawn new threads that call the callback
//   std::thread second (recorderCallback, std::ref(alpha), 50, labels);
//   std::thread third (recorderCallback, std::ref(alpha), 25, labels1);
//   std::thread fourth (negRecorderCallback, std::ref(alpha), 100, labels1); // negative values

//   first.join();                
//   second.join();               
//   third.join();
//   fourth.join();

//   // where is the checkpoint being called?? THIS SHOULDNT WORK

//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels)]->get_aggregator()->get_values()[0], 0); // min
//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels)]->get_aggregator()->get_values()[1], 49); // max
//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels)]->get_aggregator()->get_values()[2], 1525); // sum
//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels)]->get_aggregator()->get_values()[3], 75); // count

//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_aggregator()->get_values()[0], -99); // min
//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_aggregator()->get_values()[1], 24); // max
//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_aggregator()->get_values()[2], -4650); // sum
//   EXPECT_EQ(alpha.boundInstruments_[mapToString(labels1)]->get_aggregator()->get_values()[3], 125); // count
// }

} //namespace sdk
}  // namespace metrics
OPENTELEMETRY_END_NAMESPACE