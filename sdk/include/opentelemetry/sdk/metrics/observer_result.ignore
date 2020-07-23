#pragma once

#include "opentelemetry/sdk/metrics/instrument.h"
#include "opentelemetry/metrics/observer_result.h"


 namespace metrics_api = opentelemetry::metrics;

 OPENTELEMETRY_BEGIN_NAMESPACE
 namespace sdk
 {
 namespace metrics
 {

 /**
  * ObserverResult class is used in the callback recording  of asynchronous
  * instruments.  Callback functions for asynchronous instruments are designed to
  * accept a single ObserverResult object and update using its pointer to the
  * instrument itself.
  */
 template <class T>
 class ObserverResult : virtual public metrics_api::ObserverResult<T>
 {

 public:
   ObserverResult() = default;

   ObserverResult(AsynchronousInstrument<T> & instrument): instrument_(instrument) {}

   void observe(T value, const std::map<std::string, std::string> &labels)
   {
       instrument_.observe(value, labels);
   }
     
     virtual void observe(T value, const trace::KeyValueIterable &labels) {
         //noop for now
     }

 private:
     AsynchronousInstrument<T> & instrument_;

 };

 } // namespace sdk
 }  // namespace metrics
 OPENTELEMETRY_END_NAMESPACE
