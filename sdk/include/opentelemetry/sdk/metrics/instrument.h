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
    std::mutex mu_;
};

template <class T>
class BoundSynchronousInstrument : public Instrument {
    
public:
    BoundSynchronousInstrument() = default;
    
    BoundSynchronousInstrument(nostd::string_view name,
                               nostd::string_view description,
                               nostd::string_view unit,
                               bool enabled,
                               std::shared_ptr<Aggregator> agg)
                               :Instrument(name, description, unit, enabled), agg_(agg)
    { this->inc_ref(); }
    
    /**
     * Frees the resources associated with this Bound Instrument.
     * The Metric from which this instrument was created is not impacted.
     *
     * @param none
     * @return void
     */
    virtual void unbind() final { ref_ -= 1; }
    
    virtual void inc_ref() final { ref_ += 1; }
    
    virtual int get_ref() final { return ref_; }
    
    virtual void update(T value) final { 
        this->mu_.lock();
        agg_->update(value); 
        this->mu_.unlock();
    }
    
    virtual std::shared_ptr<Aggregator> get_aggregator() final{ return agg_; }
    
private:
    std::shared_ptr<Aggregator> agg_;
    int ref_;
};

template <class T>
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
    
    //std::shared_ptr<BoundSynchronousInstrument> bind(const nostd::string_view &labels);
    
    // virtual void update(nostd::variant<int, double> value, const nostd::string_view &labels);
    
    metrics_api::InstrumentKind get_kind(){
        return kind_;
    }
    
private:
    metrics_api::InstrumentKind kind_;
};

// class ObserverResult;

// class AsynchronousInstrument : public Instrument
// {

// public:
//   AsynchronousInstrument() = default;

//   AsynchronousInstrument(nostd::string_view name,
//                          nostd::string_view description,
//                          nostd::string_view unit,
//                          bool enabled,
//                          void(*callback)(ObserverResult),
//                          metrics_api::BoundInstrumentKind kind):
//                          Instrument(name, description, unit, enabled), callback_(callback), kind_(kind) {}

//   /**
//    * Captures data by activating the callback function associated with the
//    * instrument and storing its return value.  Callbacks for asychronous
//    * instruments are defined during construction.
//    *
//    * @param value is the numerical representation of the metric being captured
//    * @return none
//    */
//   virtual void observe(int value, const std::map<std::string, std::string> &labels) = 0;



// protected:
//   // Callback function which takes a pointer to an Asynchronous instrument (this) type which is
//   // stored in an observer result type and returns nothing.  This function calls the instrument's
//   // observe.
//   void (*callback_)(ObserverResult);
//   metrics_api::BoundInstrumentKind kind_;

// };

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
