#pragma once

#include <memory>
#include "opentelemetry/sdk/metrics/instrument.h"
#include "opentelemetry/sdk/metrics/observer_result.h"


// namespace metrics_api = opentelemetry::metrics;

// OPENTELEMETRY_BEGIN_NAMESPACE
// namespace sdk 
// {
// namespace metrics
// {

// class IntValueObserver : public AsynchronousInstrument
// {

// public:
//   IntValueObserver() = default;

//   IntValueObserver(nostd::string_view name,
//                    nostd::string_view description,
//                    nostd::string_view unit,
//                    bool enabled,
//                    void (*callback)(ObserverResult)):
//                    AsynchronousInstrument(name,description,unit,enabled,callback, metrics_api::BoundInstrumentKind::BoundIntValueRecorder)
//   {}

//   /*
//    * Updates the instruments aggregator with the new value. The labels should
//    * contain the keys and values to be associated with this value.
//    *
//    * @param value is the numerical representation of the metric being captured
//    * @param labels the set of labels, as key-value pairs
//    */
//   virtual void observe(int value, const std::map<std::string, std::string> &labels) override {
//       std::string labelset = mapToString(labels); // COULD CUSTOM HASH THIS INSTEAD FOR PERFORMANCE
//       if (boundAggregators_.find(labelset) == boundAggregators_.end())
//       {
//         auto sp1 = std::shared_ptr<MinMaxSumCountAggregator>(new MinMaxSumCountAggregator(kind_));
//         boundAggregators_[labelset]=sp1;  // perhaps use emplace
//         sp1->update(value);
//       }
//       else
//       {
//         boundAggregators_[labelset]->update(value);
//       }
//   }

//   std::unordered_map<std::string, std::shared_ptr<Aggregator>> boundAggregators_;
// };

// }
// }
// OPENTELEMETRY_END_NAMESPACE

