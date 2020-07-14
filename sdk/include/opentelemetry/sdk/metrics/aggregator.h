#pragma once

#include "opentelemetry/version.h"
#include "opentelemetry/metrics/instrument.h"

#include <variant>
#include <vector>
#include <mutex>
#include <memory>

namespace metrics_api = opentelemetry::metrics;

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

/*
 * Performs calculations necessary to combine updates from instruments into an insightful value.
 * Also stores current instrument values and checkpoints collected at intervals governing the
 * entire pipeline.
 */
class Aggregator
{

public:

  Aggregator() = default;

    
  /**
   * A custom copy constructor is needed because the mutex field cannot be transferred
   * between an Aggregator and its copies.
   * 
   * This may need to be overriden for aggregators that store additional information.
   */
  Aggregator(const Aggregator &cp) {
    values_ = cp.values_; 
    checkpoint_ = cp.checkpoint_;
    kind_ = cp.kind_; 
    // use default initialized mutex
  } 

  /**
   * Recieves a captured value from the instrument and applies it to the current aggregator value.
   *
   * @param val, the raw value used in aggregation
   * @return none
   */
  virtual void update(int val) = 0;

  /**
   * Checkpoints the current value.  This function will overwrite the current checkpoint with the
   * current value.
   *
   * @param none
   * @return none
   */
  virtual void checkpoint() = 0;

  /**
   * Merges the values of two aggregators in a semantically accurate manner.
   * Merging will occur differently for different aggregators depending on the
   * way values are tracked.
   *
   * @param other, the aggregator with merge with
   * @return none
   */
  void merge(std::shared_ptr<Aggregator> other);

  /**
   * Returns the checkpointed value
   *
   * @param none
   * @return the value of the checkpoint
   */
  virtual std::vector<int> get_checkpoint() = 0;

  /**
   * Returns the current values stored in the aggregator
   *
   * @param none
   * @return the values vector
   */
  virtual std::vector<int> get_values() = 0;


  /**
   * Returns the instrument kind which spawned this Aggregator instance. Since
   * only bound instrument can have aggregators, the return type is a 
   * BoundInstrumentKind.
   * 
   * @param none
   * @return BoundInstrumentKind associated with this Aggregator
   */
  virtual opentelemetry::metrics::BoundInstrumentKind get_kind(){
    return kind_;
  }


protected:
    std::vector<int> values_;
    std::vector<int> checkpoint_;
    opentelemetry::metrics::BoundInstrumentKind kind_;
    std::mutex mu_;

};

class CounterAggregator final : public Aggregator
{

public:
  
  CounterAggregator(metrics_api::BoundInstrumentKind kind);

  /**
   * Recieves a captured value from the instrument and applies it to the current aggregator value.
   *
   * @param val, the raw value used in aggregation
   * @return none
   */
  virtual void update(int val) override;

  /**
   * Checkpoints the current value.  This function will overwrite the current checkpoint with the
   * current value.
   *
   * @param none
   * @return none
   */

  virtual void checkpoint() override;

  /**
   * Merging two counter aggregators simply sums the values stored within them.
   *
   * @param other, the aggregator with merge with
   * @return none
   */
  void merge(CounterAggregator other);

  /**
   * Returns the checkpointed value
   *
   * @param none
   * @return the value of the checkpoint
   */
  virtual std::vector<int> get_checkpoint() override;

  /**
   * Returns the current values stored in the aggregator
   *
   * @param none
   * @return the values vector
   */
  virtual std::vector<int> get_values() override;

  virtual opentelemetry::metrics::BoundInstrumentKind get_kind() override;

};

class HistogramAggregator final: public Aggregator
{

public:
 
 /**
  * HistogramAggregator expects a SORTED vector of boundaries in its constructor.  Buckets are assigned
  * through a linear search and thus an unsorted vector will yield a meaningless histogram.
  * 
  * The sum of values is stored in values_[0] and the count in vales_[1].
  */
 HistogramAggregator(metrics_api::BoundInstrumentKind kind, std::vector<int> boundaries);

 /**
  * Recieves a captured value from the instrument and inserts it into the
  * current histogram counts.
  *
  * @param val, the raw value used in aggregation
  * @return none
  */
 virtual void update(int val) override;  

 /**
  * Checkpoints the current value.  This function will overwrite the current checkpoint with the
  * current value.
  *
  * @param none
  * @return none
  */
 virtual void checkpoint() override;

 /**
   * A Histogram Aggregator can be merged with another instance if the boundaries passed in at
   * creation are identical.  
   * 
   * Merging two histogram aggregators first sums the count of values recieved and the two
   * individual sums held by each aggregator.  Bucket counts for each bucket are then summed togther.
   *
   * @param other, the aggregator with merge with
   * @return none
   */
 void merge(HistogramAggregator other);

 /**
  * Returns the checkpointed value
  *
  * @param none
  * @return the value of the checkpoint
  */
 virtual std::vector<int> get_checkpoint() override;

/**
   * Returns the current values stored in the aggregator
   *
   * @param none
   * @return the values vector: sum stored in index 0, count stored in index 1
   */
virtual std::vector<int> get_values() override;

/**
   * Returns the boundaries the delimit the buckets of the histogram.
   *
   * @param none
   * @return the boundaries_ vector
   */
 std::vector<int> get_boundaries();

/**
   * Returns the bucket counts in vector format.  This vector will be one element larger 
   * in size than the boundaries associated with this histogram and default to 0.
   *
   * @param none
   * @return the bucketCounts_ vector
   */
 std::vector<int> get_counts();

private:
 std::vector<int> boundaries_;
 std::vector<int> bucketCounts_;
};

class MinMaxSumCountAggregator final: public Aggregator
{
public:
  explicit MinMaxSumCountAggregator(metrics_api::BoundInstrumentKind kind);

  /**
   * Receives a captured value from the instrument and applies it to the current aggregator value.
   *
   * @param val, the raw value used in aggregation
   */
  virtual void update(int val) override;

  /**
   * Checkpoints the current value.  This function will overwrite the current checkpoint with the
   * current value.
   *
   */

  virtual void checkpoint() override;

  void merge(const MinMaxSumCountAggregator &other);

  /**
   * Returns the checkpointed value
   *
   * @return the value of the checkpoint
   */
  virtual std::vector<int> get_checkpoint() override;

  virtual std::vector<int> get_values() override;

};

class SketchAggregator : public Aggregator
{
public:
  explicit SketchAggregator(metrics_api::BoundInstrumentKind kind);

  /**
   * Receives a captured value from the instrument and applies it to the current aggregator value.
   *
   * @param val, the raw value used in aggregation
   * @return none
   */
  void update(int val) override;

  /**
   * Checkpoints the current value.  This function will overwrite the current checkpoint with the
   * current value.
   *
   * @param none
   * @return none
   */

  void checkpoint() override;

  void merge(SketchAggregator other);

  /**
   * Returns the checkpointed value
   *
   * @param none
   * @return the value of the checkpoint
   */
  std::vector<int> get_checkpoint() override;

  std::vector<int> get_values() override;

private:

};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
