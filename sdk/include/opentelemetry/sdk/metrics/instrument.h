#pragma once

#include "opentelemetry/metrics/instrument.h"
#include "opentelemetry/sdk/metrics/aggregator.h"
#include "opentelemetry/version.h"

#include <memory>
#include <unordered_map>

namespace metrics_api = opentelemetry::metrics;
namespace trace_api = opentelemetry::trace;

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics 
{


class Instrument : metrics_api::Instrument {

public:
  Instrument() = default;

  Instrument(nostd::string_view name,
             nostd::string_view description,
             nostd::string_view unit,
             bool enabled): name_(name), description_(description), unit_(unit), enabled_(enabled) {}

        // Returns true if the instrument is enabled and collecting data
  virtual bool IsEnabled() override {
    return enabled_;
  }

  // Return the instrument name
  virtual nostd::string_view GetName() override { return name_; }

  // Return the instrument description
  virtual nostd::string_view GetDescription() override { return description_; }

  // Return the insrument's units of measurement
  virtual nostd::string_view GetUnits() override { return unit_; }

protected:
  std::string name_;
  std::string description_;
  std::string unit_;
  bool enabled_;

};

class BoundSynchronousInstrument : public Instrument {

public:
  BoundSynchronousInstrument() = default;

  BoundSynchronousInstrument(nostd::string_view name,
                             nostd::string_view description,
                             nostd::string_view unit,
                             bool enabled,
                             std::shared_ptr<Aggregator> agg)
      : Instrument(name, description, unit, enabled), agg_(agg)
  {
    this->inc_ref();
  }

  /**
   * Frees the resources associated with this Bound Instrument.
   * The Metric from which this instrument was created is not impacted.
   *
   * @param none
   * @return void
   */
  virtual void unbind() final {
    ref_ -= 1;
  }

  virtual void inc_ref() final {
    ref_ += 1;
  }

  virtual int get_ref() final {
    return ref_;
  }

  /**
   * Records a single synchronous metric event; a call to the aggregator
   * Since this is a bound synchronous instrument, labels are not required in  * metric capture
   * calls.
   *
   * @param value is the numerical representation of the metric being captured
   * @return void
   */
  virtual void update(int value) final { 
    agg_->update(value); 
  }

  virtual std::shared_ptr<Aggregator> get_aggregator(){
    return agg_;
  }

private:
  std::shared_ptr<Aggregator> agg_;
  int ref_;
};

class SynchronousInstrument : public Instrument {

public:
  SynchronousInstrument() = default;

  SynchronousInstrument(nostd::string_view name,
                        nostd::string_view description,
                        nostd::string_view unit,
                        bool enabled,
                        metrics_api::InstrumentKind kind)
      : Instrument(name, description, unit, enabled), kind_(kind)
  {}

  /**
   * Returns a Bound Instrument associated with the specified labels.         * Multiples requests
   * with the same set of labels may return the same Bound Instrument instance.
   *
   * It is recommended that callers keep a reference to the Bound Instrument
   * instead of repeatedly calling this operation.
   *
   * @param labels the set of labels, as key-value pairs
   * @return a Bound Instrument
   */
  std::shared_ptr<BoundSynchronousInstrument> bind(const nostd::string_view &labels)
  {
    return std::shared_ptr<BoundSynchronousInstrument>(new BoundSynchronousInstrument());
  }


  // THINK THIS FUNCTION NEEDS TO GO
  /**
   * Records a single synchronous metric event.
   * Since this is an unbound synchronous instrument, labels are required in  * metric capture
   * calls.
   *
   * update can be used in instruments with both add or record since it simply
   * activated the aggregator
   *
   * @param labels the set of labels, as key-value pairs
   * @param value is the numerical representation of the metric being captured
   * @return void
   */
  // virtual void update(nostd::variant<int, double> value, const nostd::string_view &labels)
  // {
  //   auto sp = bind(labels);
  //   sp->update(value);
  //   sp->unbind();
  // }

  metrics_api::InstrumentKind get_kind(){
    return kind_;
  }

private:
  metrics_api::InstrumentKind kind_;
};

class ObserverResult;

class AsynchronousInstrument : public Instrument
{

public:
  AsynchronousInstrument() = default;

  AsynchronousInstrument(nostd::string_view name,
                         nostd::string_view description,
                         nostd::string_view unit,
                         bool enabled,
                         void(*callback)(ObserverResult),
                         metrics_api::BoundInstrumentKind kind):
                         Instrument(name, description, unit, enabled), callback_(callback), kind_(kind) {}

  /**
   * Captures data by activating the callback function associated with the
   * instrument and storing its return value.  Callbacks for asychronous
   * instruments are defined during construction.
   *
   * @param value is the numerical representation of the metric being captured
   * @return none
   */
  virtual void observe(int value, const std::map<std::string, std::string> &labels) = 0;

  

protected:
  // Callback function which takes a pointer to an Asynchronous instrument (this) type which is
  // stored in an observer result type and returns nothing.  This function calls the instrument's
  // observe.
  void (*callback_)(ObserverResult);
  metrics_api::BoundInstrumentKind kind_;

};

std::string mapToString(const std::map<std::string,std::string> & conv){
  std::stringstream ss;
  for (auto i:conv){
    ss <<i.first <<':' <<i.second <<',';
  }
  return ss.str();
}
  
} // namespace metrics
} // namespace sdk
OPENTELEMETRY_END_NAMESPACE