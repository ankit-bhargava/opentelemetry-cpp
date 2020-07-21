#pragma once

#include "opentelemetry/metrics/instrument.h"
#include "opentelemetry/sdk/metrics/aggregator/aggregator.h"
#include "opentelemetry/version.h"

#include <memory>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <map>

namespace metrics_api = opentelemetry::metrics;
namespace trace_api = opentelemetry::trace;

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics 
{


class Instrument : virtual public metrics_api::Instrument {
    
public:
    Instrument() = default;
    
    Instrument(nostd::string_view name,
               nostd::string_view description,
               nostd::string_view unit,
               bool enabled,
               metrics_api::InstrumentKind kind): name_(name), description_(description), unit_(unit), enabled_(enabled), kind_(kind) {
        std::cerr <<"called instrument constructor" <<std::endl;
    }
    
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
    
    virtual metrics_api::InstrumentKind get_kind() final { return this->kind_; }
    
protected:
    std::string name_;
    std::string description_;
    std::string unit_;
    bool enabled_;
    std::mutex mu_;
    metrics_api::InstrumentKind kind_;
};

template <class T>
class BoundSynchronousInstrument : virtual public Instrument, virtual public metrics_api::BoundSynchronousInstrument<T> {
    
public:
    
    using Instrument::Instrument;
    
    BoundSynchronousInstrument() = default;
    
    BoundSynchronousInstrument(nostd::string_view name,
                               nostd::string_view description,
                               nostd::string_view unit,
                               bool enabled,
                               metrics_api::InstrumentKind kind,
                               std::shared_ptr<Aggregator<T>> agg)
    :Instrument(name, description, unit, enabled, kind), agg_(agg)
    { this->inc_ref(); } // increase reference count when instantiated
    
    /**
     * Frees the resources associated with this Bound Instrument.
     * The Metric from which this instrument was created is not impacted.
     *
     * @param none
     * @return void
     */
    virtual void unbind() final { ref_ -= 1; }
    
    /**
     * Increments the reference count. This function is used when binding or instantiating.
     *
     * @param none
     * @return void
     */
    virtual void inc_ref() final { ref_ += 1; }
    
    /**
     * Returns the current reference count of the instrument.  This value is used to
     * later in the pipeline remove stale instruments.
     *
     * @param none
     * @return current ref count of the instrument
     */
    virtual int get_ref() final { return ref_; }
    
    /**
     * Records a single synchronous metric event; a call to the aggregator
     * Since this is a bound synchronous instrument, labels are not required in  * metric capture
     * calls.
     *
     * @param value is the numerical representation of the metric being captured
     * @return void
     */
    virtual void update(T value) final {
        this->mu_.lock();
        agg_->update(value);
        this->mu_.unlock();
    }
    
    /**
     * Returns the aggregator responsible for meaningfully combining update values.
     *
     * @param none
     * @return the aggregator assigned to this instrument
     */
    virtual std::shared_ptr<Aggregator<T>> get_aggregator() final { return agg_; }
    
private:
    std::shared_ptr<Aggregator<T>> agg_;
    int ref_ = 0;
};

template <class T>
class SynchronousInstrument : virtual public Instrument, virtual public metrics_api::SynchronousInstrument<T> {
    
public:
    
    using Instrument::Instrument;
    
    SynchronousInstrument() = default;
    
    SynchronousInstrument(nostd::string_view name,
                          nostd::string_view description,
                          nostd::string_view unit,
                          bool enabled,
                          metrics_api::InstrumentKind kind):
                          Instrument(name, description, unit, enabled,  kind)
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
    std::shared_ptr<BoundSynchronousInstrument<T>> bind(const nostd::string_view &labels);
    
    virtual void update(T value, const trace::KeyValueIterable &labels) override {
        // noop for now
    }
    
    virtual void update(T val, const std::map<std::string, std::string> &labels){
        // noop here
    }
    
    virtual std::vector<std::shared_ptr<Aggregator<T>>> getAggs() {
        return std::vector<std::shared_ptr<Aggregator<T>>>();
    }
    
};

template <class T>
class ObserverResult;


template <class T>
class AsynchronousInstrument : virtual public Instrument, virtual public metrics_api::AsynchronousInstrument<T> {

public:

    AsynchronousInstrument() = default;

    AsynchronousInstrument(nostd::string_view name,
                           nostd::string_view description,
                           nostd::string_view unit,
                           bool enabled,
                           void (*callback)(ObserverResult<T>),
                           metrics_api::InstrumentKind kind):
                           Instrument(name, description, unit, enabled, kind), callback_(callback)
    {}

    virtual void observe(T value, const std::map<std::string, std::string> &labels){
        agg_->update(value);
    }

    void (*callback_)(ObserverResult<T>);

private:
    std::shared_ptr<Aggregator<T>> agg_;


};

// Utility function which converts maps to strings for better performance
std::string mapToString(const std::map<std::string,std::string> & conv){
    std::stringstream ss;
    ss <<"{ ";
    for (auto i:conv){
        ss <<i.first <<':' <<i.second <<',';
    }
    ss <<"}";
    return ss.str();
}

} // namespace metrics
} // namespace sdk
OPENTELEMETRY_END_NAMESPACE
