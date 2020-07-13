#include "opentelemetry/sdk/metrics/aggregator.h"

#include <algorithm>
#include <utility>

namespace metrics_api = opentelemetry::metrics;

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

// TODO: add thread-safety measures to this, decide how we want to propogate type, atomic types,
// enforce aggregator type during merging,

/*
 * Performs calculations necessary to combine updates from instruments into an * insightful value.
 * Also stores current instrument values and checkpoints collected at intervals
 * governing the entire pipeline.
 */



  CounterAggregator::CounterAggregator(metrics_api::BoundInstrumentKind kind) 
  {
    // Aggregator supports int and double, type is enforced in the instrument itself
    kind_ = kind; 
    values_     = std::vector<int>(1, 0);
    checkpoint_ = std::vector<int>(1, 0);
  }

  /**
   * Recieves a captured value from the instrument and applies it to the current aggregator value.
   *
   * @param val, the raw value used in aggregation
   * @return none
   */
  void CounterAggregator::update(int val)
  {
    mu_.lock();
    values_[0] += val;  // atomic operation
    mu_.unlock();
  }

  /**
   * Checkpoints the current value.  This function will overwrite the current checkpoint with the
   * current value.
   *
   * @param none
   * @return none
   */

  void CounterAggregator::checkpoint() { 
    checkpoint_ = values_; 
    values_[0] = 0;
  }

  void CounterAggregator::merge(CounterAggregator other)
  {
    if (this->kind_ == other.kind_){ 
      values_[0] += other.values_[0];  // atomic operation afaik
    } else {
      //AggregatorMismatch Exception
    }
  }

  /**
   * Returns the checkpointed value
   *
   * @param none
   * @return the value of the checkpoint
   */
  std::vector<int> CounterAggregator::get_checkpoint() { 
    return checkpoint_; 
  }

  std::vector<int> CounterAggregator::get_values() {
    return values_;
  }

  opentelemetry::metrics::BoundInstrumentKind CounterAggregator::get_kind() {
    return kind_;
  }




 HistogramAggregator::HistogramAggregator(metrics_api::BoundInstrumentKind kind, std::vector<int> boundaries)
 {
   kind_ = kind;
   
   boundaries_   = boundaries;
   values_     = std::vector<int>(2, 0);
   checkpoint_ = std::vector<int>(2, 0);
   bucketCounts_ = std::vector<int>(boundaries_.size() + 1, 0);

 }

 /**
  * Recieves a captured value from the instrument and inserts it into the
  * current histogram counts.
  *
  * @param val, the raw value used in aggregation
  * @return none
  */
 void HistogramAggregator::update(int val)  // have to decide what to lock and what is protected by atomic...
 {

  // Options here: linear or binary search

   int bucketID = boundaries_.size();
   for (int i = 0; i < boundaries_.size(); i++)
   {
     if (val < boundaries_[i]) // concurrent read is thread-safe
     {
       bucketID = i;
       break;
     }
   }
   
   // Alternate impl with binary search
   //auto pos = std::lower_bound (boundaries_.begin(), boundaries_.end(), val);
   //bucketCounts_[pos-boundaries_.begin()] += 1;

   // the sum of updates is stored in position zero, while the count is in position 1
   mu_.lock();
   values_[0] += val;
   values_[1] += 1;
   bucketCounts_[bucketID] += 1;
   mu_.unlock();
 }

 /**
  * Checkpoints the current value.  This function will overwrite the current checkpoint with the
  * current value.
  *
  * @param none
  * @return none
  */

 void HistogramAggregator::checkpoint() { 
   checkpoint_ = values_; 
   values_[0]=0;
   values_[1]=0;
  }

 void HistogramAggregator::merge(HistogramAggregator other)
 {
   values_[0] += other.values_[0];
   values_[1] += other.values_[1];

   for (int i = 0; i < bucketCounts_.size(); i++)
   {
     bucketCounts_[i] += other.bucketCounts_[i];
   }
 }

 /**
  * Returns the checkpointed value
  *
  * @param none
  * @return the value of the checkpoint
  */
 std::vector<int> HistogramAggregator::get_checkpoint()
 {
   return checkpoint_;  // what happens if there isn't a checkpoint?
 }

 std::vector<int> HistogramAggregator::get_boundaries(){
   return boundaries_;
 }

 std::vector<int> HistogramAggregator::get_counts(){
   return bucketCounts_;
 }

  std::vector<int> HistogramAggregator::get_values() {
    return values_;
  }

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE


// Consistent comments above functions- function descriptions
// Does checkpoint automatically return as well
// Push base class for brandon+hudson
// "expecting no more than 100 buckets for histogram" something to discuss with reiley  (do we ever hit 512+ buckets)
// Go doesn't lock on the merge -- likely don't need this but look into this
// Are shared pointers adequate for binding and unbinding
// Work with brandon to make friend class declaration
// Enforce naming convention in instrument constructors 
// Should records hold aggregators or vectors
// PR Comments about type
// CounterAgg can't drop in value
