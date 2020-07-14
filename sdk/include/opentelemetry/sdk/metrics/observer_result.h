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
 * ObserverResult class is necessary for the callback recording asynchronous
 * instrument use.  Callback functions asynchronous instruments are designed to
 * accept a single ObserverResult object and update using its pointer to the
 * instrument itself.
 */
class ObserverResult
{

public:
  ObserverResult() = default;

  ObserverResult(std::shared_ptr<AsynchronousInstrument> instrument): instrument_(instrument) {}

  virtual void observe(int value, const std::map<std::string, std::string> &labels)
  {
    instrument_->observe(value, labels);
  }

private:
    std::shared_ptr<AsynchronousInstrument> instrument_;

};

} // namespace sdk
}  // namespace metrics
OPENTELEMETRY_END_NAMESPACE