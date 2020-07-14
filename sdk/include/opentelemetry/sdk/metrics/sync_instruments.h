#pragma once

#include "opentelemetry/sdk/metrics/instrument.h"
#include <stdexcept>
#include <map>
#include <sstream>

namespace metrics_api = opentelemetry::metrics;

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics 
{

std::string mapToString(const std::map<std::string,std::string> & conv){
  std::stringstream ss;
  for (auto i:conv){
    ss <<i.first <<':' <<i.second <<',';
  }
  return ss.str();
}

class BoundIntCounter final: public BoundSynchronousInstrument{

public:
    BoundIntCounter() = default;

    BoundIntCounter(nostd::string_view name,
                    nostd::string_view description,
                    nostd::string_view unit,
                    bool enabled)
                    : BoundSynchronousInstrument(name, description, unit, enabled, std::shared_ptr<Aggregator>(new CounterAggregator(metrics_api::BoundInstrumentKind::BoundIntCounter))) // Aggregator is chosen here
    {}

    /*
     * Add adds the value to the counter's sum. The labels are already linked   * to the instrument
     * and are not specified.
     *
     * @param value the numerical representation of the metric being captured
     * @param labels the set of labels, as key-value pairs
     */
    void add(int value) { 
      if (value < 0){
        throw std::invalid_argument("Counter instrument updates must be non-negative.");
      } else {
        update(value); 
      }
      
    }
  };

  class IntCounter final : public SynchronousInstrument
  {

  public:
    IntCounter() = default;

    IntCounter(nostd::string_view name,
               nostd::string_view description,
               nostd::string_view unit,
               bool enabled)
        : SynchronousInstrument(name, description, unit, enabled, metrics_api::InstrumentKind::IntCounter)
    {}

    /*
     * Bind creates a bound instrument for this counter. The labels are
     * associated with values recorded via subsequent calls to Record.
     *
     * @param labels the set of labels, as key-value pairs.
     * @return a BoundIntCounter tied to the specified labels
     */
    std::shared_ptr<BoundIntCounter> bind(const std::map<std::string, std::string> &labels)
    {
      std::string labelset = mapToString(labels); // COULD CUSTOM HASH THIS INSTEAD FOR PERFORMANCE
      if (boundInstruments_.find(labelset) == boundInstruments_.end())
      {
        auto sp1 = std::make_shared<BoundIntCounter>(name_, description_, unit_, enabled_);
        boundInstruments_[labelset]=sp1;  // perhaps use emplace
        return sp1;
      }
      else
      {
        boundInstruments_[labelset]->inc_ref();
        return boundInstruments_[labelset];
      }
    }

    /*
     * Add adds the value to the counter's sum. The labels should contain
     * the keys and values to be associated with this value.  Counters only     * accept positive
     * valued updates.
     *
     * @param value the numerical representation of the metric being captured
     * @param labels the set of labels, as key-value pairs
     */
    void add(int value, const std::map<std::string, std::string> &labels) 
    {
      auto sp = bind(labels);
      sp->update(value);
      sp->unbind();
    }
    
    // Data structures -- this is private so the meter can access it, would rather use a friend declaration of some type instead
    std::unordered_map<std::string, std::shared_ptr<BoundIntCounter>> boundInstruments_;
  };

class BoundIntUpDownCounter final: public BoundSynchronousInstrument{

public:
    BoundIntUpDownCounter() = default;

    BoundIntUpDownCounter(nostd::string_view name,
                    nostd::string_view description,
                    nostd::string_view unit,
                    bool enabled)
                    : BoundSynchronousInstrument(name, description, unit, enabled, std::shared_ptr<Aggregator>(new CounterAggregator(metrics_api::BoundInstrumentKind::BoundIntUpDownCounter))) // Aggregator is chosen here
    {}

    /*
     * Add adds the value to the counter's sum. The labels are already linked   * to the instrument
     * and are not specified.
     *
     * @param value the numerical representation of the metric being captured
     * @param labels the set of labels, as key-value pairs
     */
    void add(int value) { 
      update(value);
      
    }
  };

  class IntUpDownCounter final : public SynchronousInstrument
  {

  public:
    IntUpDownCounter() = default;

    IntUpDownCounter(nostd::string_view name,
               nostd::string_view description,
               nostd::string_view unit,
               bool enabled)
        : SynchronousInstrument(name, description, unit, enabled, metrics_api::InstrumentKind::IntUpDownCounter)
    {}

    /*
     * Bind creates a bound instrument for this counter. The labels are
     * associated with values recorded via subsequent calls to Record.
     *
     * @param labels the set of labels, as key-value pairs.
     * @return a BoundIntCounter tied to the specified labels
     */
    std::shared_ptr<BoundIntUpDownCounter> bind(const std::map<std::string, std::string> &labels)
    {
      std::string labelset = mapToString(labels); // COULD CUSTOM HASH THIS INSTEAD FOR PERFORMANCE
      if (boundInstruments_.find(labelset) == boundInstruments_.end())
      {
        auto sp1 = std::make_shared<BoundIntUpDownCounter>(name_, description_, unit_, enabled_);
        boundInstruments_[labelset]=sp1;  // perhaps use emplace
        return sp1;
      }
      else
      {
        boundInstruments_[labelset]->inc_ref();
        return boundInstruments_[labelset];
      }
    }

    /*
     * Add adds the value to the counter's sum. The labels should contain
     * the keys and values to be associated with this value.  Counters only     * accept positive
     * valued updates.
     *
     * @param value the numerical representation of the metric being captured
     * @param labels the set of labels, as key-value pairs
     */
    void add(int value, const std::map<std::string, std::string> &labels) 
    {
      auto sp = bind(labels);
      sp->update(value);
      sp->unbind();
    }
    
    // Data structures -- this is private so the meter can access it, would rather use a friend declaration of some type instead
    std::unordered_map<std::string, std::shared_ptr<BoundIntUpDownCounter>> boundInstruments_;
  };

class BoundIntValueRecorder final: public BoundSynchronousInstrument{

public:
    BoundIntValueRecorder() = default;

    BoundIntValueRecorder(nostd::string_view name,
                    nostd::string_view description,
                    nostd::string_view unit,
                    bool enabled)
                    : BoundSynchronousInstrument(name, description, unit, enabled, std::shared_ptr<Aggregator>(new MinMaxSumCountAggregator(metrics_api::BoundInstrumentKind::BoundIntValueRecorder))) // Aggregator is chosen here
    {}

    /*
     * Add adds the value to the counter's sum. The labels are already linked   * to the instrument
     * and are not specified.
     *
     * @param value the numerical representation of the metric being captured
     * @param labels the set of labels, as key-value pairs
     */
    void record(int value) { 
      update(value);
      
    }
  };

  class IntValueRecorder final : public SynchronousInstrument
  {

  public:
    IntValueRecorder() = default;

    IntValueRecorder(nostd::string_view name,
               nostd::string_view description,
               nostd::string_view unit,
               bool enabled)
        : SynchronousInstrument(name, description, unit, enabled, metrics_api::InstrumentKind::IntValueRecorder)
    {}

    /*
     * Bind creates a bound instrument for this counter. The labels are
     * associated with values recorded via subsequent calls to Record.
     *
     * @param labels the set of labels, as key-value pairs.
     * @return a BoundIntCounter tied to the specified labels
     */
    std::shared_ptr<BoundIntValueRecorder> bind(const std::map<std::string, std::string> &labels)
    {
      std::string labelset = mapToString(labels); // COULD CUSTOM HASH THIS INSTEAD FOR PERFORMANCE
      if (boundInstruments_.find(labelset) == boundInstruments_.end())
      {
        auto sp1 = std::make_shared<BoundIntValueRecorder>(name_, description_, unit_, enabled_);
        boundInstruments_[labelset]=sp1;  // perhaps use emplace
        return sp1;
      }
      else
      {
        boundInstruments_[labelset]->inc_ref();
        return boundInstruments_[labelset];
      }
    }

    /*
     * Add adds the value to the counter's sum. The labels should contain
     * the keys and values to be associated with this value.  Counters only     * accept positive
     * valued updates.
     *
     * @param value the numerical representation of the metric being captured
     * @param labels the set of labels, as key-value pairs
     */
    void record(int value, const std::map<std::string, std::string> &labels) 
    {
      auto sp = bind(labels);
      sp->update(value);
      sp->unbind();
    }
    
    // Data structures -- this is private so the meter can access it, would rather use a friend declaration of some type instead
    std::unordered_map<std::string, std::shared_ptr<BoundIntValueRecorder>> boundInstruments_;
  };

}
}
OPENTELEMETRY_END_NAMESPACE