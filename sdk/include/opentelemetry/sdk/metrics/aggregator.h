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

  virtual std::vector<int> get_values() = 0;

  virtual opentelemetry::metrics::BoundInstrumentKind get_kind(){
    return kind_;
  }

  Aggregator(const Aggregator &cp) {
    values_ = cp.values_; 
    checkpoint_ = cp.checkpoint_;
    kind_ = cp.kind_; 
    // use default initialized mutex
  } 


protected:
    std::vector<int> values_;
    std::vector<int> checkpoint_;
    opentelemetry::metrics::BoundInstrumentKind kind_;
    std::mutex mu_;

};

class CounterAggregator : public Aggregator
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

  void merge(CounterAggregator other);

  /**
   * Returns the checkpointed value
   *
   * @param none
   * @return the value of the checkpoint
   */
  std::vector<int> get_checkpoint() override;

  virtual std::vector<int> get_values() override;

  virtual opentelemetry::metrics::BoundInstrumentKind get_kind() override;

};

class HistogramAggregator : public Aggregator
{

public:
 // boundaries MUST be sorted to create a meaningful histogram
 // should we check sorting? or sort ourselves? don't think we need to
 HistogramAggregator(metrics_api::BoundInstrumentKind kind, std::vector<int> boundaries);

 /**
  * Recieves a captured value from the instrument and inserts it into the
  * current histogram counts.
  *
  * @param val, the raw value used in aggregation
  * @return none
  */
 virtual void update(int val) override;  // have to decide what to lock and what is protected by atomic...

 /**
  * Checkpoints the current value.  This function will overwrite the current checkpoint with the
  * current value.
  *
  * @param none
  * @return none
  */

 virtual void checkpoint() override;

 void merge(HistogramAggregator other);

 /**
  * Returns the checkpointed value
  *
  * @param none
  * @return the value of the checkpoint
  */
 virtual std::vector<int> get_checkpoint() override;

virtual std::vector<int> get_values() override;

 std::vector<int> get_boundaries();

 std::vector<int> get_counts();

 

private:
 std::vector<int> boundaries_;
 std::vector<int> bucketCounts_;
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE