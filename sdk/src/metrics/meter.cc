#include "opentelemetry/sdk/metrics/meter.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                        Instrument Constructors                     //
//                                                                    //
////////////////////////////////////////////////////////////////////////

/**
   * Creates an Counter with the passed characteristics and a shared_ptr to that
   * Counter. Then adds that shared ptr to the metrics_ map before returning it.
   *
   * @param name the name of the new Counter.
   * @param description a brief description of what the Counter is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @return a shared pointer to the created Counter.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
std::shared_ptr<SynchronousInstrument<short>> Meter::NewShortCounter(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<short>>(
            new Counter<short>(name, description, unit, enabled));
  short_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<SynchronousInstrument<int>> Meter::NewIntCounter(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<int>>(
      new Counter<int>(name, description, unit, enabled));
  int_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<SynchronousInstrument<float>> Meter::NewFloatCounter(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<float>>(
      new Counter<float>(name, description, unit, enabled));
  float_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<SynchronousInstrument<double>> Meter::NewDoubleCounter(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<double>>(
      new Counter<double>(name, description, unit, enabled));
  double_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

/**
   * Creates an UpDownCounter with the passed characteristics and a shared_ptr to that
   * UpDownCounter. Then adds that shared ptr to the metrics_ map before returning it.
   *
   * @param name the name of the new UpDownCounter.
   * @param description a brief description of what the UpDownCounter is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @return a shared pointer to the created UpDownCounter.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
std::shared_ptr<SynchronousInstrument<short>> Meter::NewShortUpDownCounter(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<short>>(
      new UpDownCounter<short>(name, description, unit, enabled));
  short_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<SynchronousInstrument<int>> Meter::NewIntUpDownCounter(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<int>>(
      new UpDownCounter<int>(name, description, unit, enabled));
  int_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<SynchronousInstrument<float>> Meter::NewFloatUpDownCounter(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<float>>(
      new UpDownCounter<float>(name, description, unit, enabled));
  float_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<SynchronousInstrument<double>> Meter::NewDoubleUpDownCounter(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<double>>(
      new UpDownCounter<double>(name, description, unit, enabled));
  double_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

/**
   * Creates a ValueRecorder with the passed characteristics and a shared_ptr to that
   * ValueRecorder. Then adds that shared ptr to the metrics_ map before returning it.
   *
   * @param name the name of the new ValueRecorder.
   * @param description a brief description of what the ValueRecorder is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @return a shared pointer to the created ValueRecorder.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
std::shared_ptr<SynchronousInstrument<short>> Meter::NewShortValueRecorder(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<short>>(
      new ValueRecorder<short>(name, description, unit, enabled));
  short_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<SynchronousInstrument<int>> Meter::NewIntValueRecorder(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<int>>(
      new ValueRecorder<int>(name, description, unit, enabled));
  int_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<SynchronousInstrument<float>> Meter::NewFloatValueRecorder(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<float>>(
      new ValueRecorder<float>(name, description, unit, enabled));
  float_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<SynchronousInstrument<double>> Meter::NewDoubleValueRecorder(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled)
{
  auto ptr = std::shared_ptr<SynchronousInstrument<double>>(
      new ValueRecorder<double>(name, description, unit, enabled));
  double_metrics_.insert(std::make_pair(name, ptr));
  return ptr;
}

/**
   * Creates a DoubleSumObserver with the passed characteristics and a shared_ptr to that
   * SumObserver. Then adds that shared ptr to the observers_ map before returning it.
   *
   * @param name the name of the new SumObserver.
   * @param description a brief description of what the SumObserver is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @return a shared pointer to the created SumObserver.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
std::shared_ptr<AsynchronousInstrument<short>> Meter::NewShortSumObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<short>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<short>>(
      new SumObserver<short>(name, description, unit, enabled, callback));
  short_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<AsynchronousInstrument<int>> Meter::NewIntSumObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<int>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<int>>(
      new SumObserver<int>(name, description, unit, enabled, callback));
  int_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<AsynchronousInstrument<float>> Meter::NewFloatSumObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<float>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<float>>(
      new SumObserver<float>(name, description, unit, enabled, callback));
  float_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<AsynchronousInstrument<double>> Meter::NewDoubleSumObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<double>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<double>>(
      new SumObserver<double>(name, description, unit, enabled, callback));
  double_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

/**
   * Creates an UpDownSumObserver with the passed characteristics and a shared_ptr to that
   * eUpDownSumObserver. Then adds that shared ptr to the observers_ map before returning
   * it.
   *
   * @param name the name of the new UpDownSumObserver.
   * @param description a brief description of what the UpDownSumObserver is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @return a shared pointer to the created UpDownSumObserver.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
std::shared_ptr<AsynchronousInstrument<short>> Meter::NewShortUpDownSumObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<short>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<short>>(
      new UpDownSumObserver<short>(name, description, unit, enabled, callback));
  short_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<AsynchronousInstrument<int>> Meter::NewIntUpDownSumObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<int>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<int>>(
      new UpDownSumObserver<int>(name, description, unit, enabled, callback));
  int_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<AsynchronousInstrument<float>> Meter::NewFloatUpDownSumObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<float>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<float>>(
      new UpDownSumObserver<float>(name, description, unit, enabled, callback));
  float_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<AsynchronousInstrument<double>> Meter::NewDoubleUpDownSumObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<double>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<double>>(
      new UpDownSumObserver<double>(name, description, unit, enabled, callback));
  double_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

/**
   * Creates a ValueObserver with the passed characteristics and a shared_ptr to that
   * ValueObserver. Then adds that shared ptr to the observers_ map before returning it.
   *
   * @param name the name of the new ValueObserver.
   * @param description a brief description of what the ValueObserver is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @return a shared pointer to the created ValueObserver.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
std::shared_ptr<AsynchronousInstrument<short>> Meter::NewShortValueObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<short>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<short>>(
      new ValueObserver<short>(name, description, unit, enabled, callback));
  short_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<AsynchronousInstrument<int>> Meter::NewIntValueObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<int>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<int>>(
      new ValueObserver<int>(name, description, unit, enabled, callback));
  int_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<AsynchronousInstrument<float>> Meter::NewFloatValueObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<float>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<float>>(
      new ValueObserver<float>(name, description, unit, enabled, callback));
  float_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

std::shared_ptr<AsynchronousInstrument<double>> Meter::NewDoubleValueObserver(
    nostd::string_view name,
    nostd::string_view description,
    nostd::string_view unit,
    const bool enabled,
    void (*callback)(ObserverResult<double>))
{
  auto ptr = std::shared_ptr<AsynchronousInstrument<double>>(
      new ValueObserver<double>(name, description, unit, enabled, callback));
  double_observers_.insert(std::make_pair(name, ptr));
  return ptr;
}

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                         RecordBatch Functions                      //
//                                                                    //
////////////////////////////////////////////////////////////////////////

/**
   * Utility method that allows users to atomically record measurements to a set of
   * synchronous metric instruments with a common set of labels.
   *
   * @param labels a map of strings to strings representing key-value pairs labels.
   * @param values a map of SynchronousInstruments to variant<int, double>. Each instrument in
   * the map is the instrument to record to, and the corresponding key is the value to record to
   * that instrument.
   */
void Meter::RecordShortBatch(
    const trace::KeyValueIterable &labels,
    nostd::span<const nostd::shared_ptr<metrics_api::SynchronousInstrument<short>>> instruments,
    nostd::span<const short> values) noexcept
{
  for (int i = 0; i < instruments.size(); ++i)
  {
    instruments[i]->update(values[i], labels);
  }
}

void Meter::RecordIntBatch(
    const trace::KeyValueIterable &labels,
    nostd::span<const std::pair<nostd::shared_ptr<metrics_api::SynchronousInstrument<int>>, int>> values) noexcept
{

}

void Meter::RecordFloatBatch(
    const trace::KeyValueIterable &labels,
    nostd::span<const std::pair<nostd::shared_ptr<metrics_api::SynchronousInstrument<float>>, float>> values) noexcept
{

}

void Meter::RecordDoubleBatch(
    const trace::KeyValueIterable &labels,
    nostd::span<const std::pair<nostd::shared_ptr<metrics_api::SynchronousInstrument<double>>, double>> values) noexcept
{

}

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                           Collect Functions                        //
//                                                                    //
////////////////////////////////////////////////////////////////////////

/**
   * Creates {@code Record}s from all metric instruments stored in this {@code meter}
   * object.
   *
   * Calls CollectMetrics and CollectObservers
   *
   * Note: In order to capture the value of each instrument, that instrument's aggregator's
   * Checkpoint() function will be called, thus resetting the value held by the aggregator.
   */
std::vector<Record> Meter::Collect() noexcept
{
  std::vector<Record> records;
  CollectMetrics(records);
  CollectObservers(records);
  return records;
}

/**
 * Creates {@code Record}s from all synchronous metric instruments stored in this {@code meter}
 * object.
 *
 * Note: In order to capture the value of each instrument, that instrument's aggregator's
 * Checkpoint() function will be called, thus resetting the value held by the aggregator.
 *
 * @param records a reference to vector<Record>, passed from Collect() function. All Records
 * are stored in this vector.
 */
void Meter::CollectMetrics(std::vector<Record> &records) noexcept
{
  metrics_lock_.lock();
  for (auto pair : short_metrics_)
  {
    for (auto bound_instr : pair.second->GetBoundInstruments())
    {
        AggregatorVariant agg = bound_instr.second->GetAggregator();
      records.push_back(Record(pair.first, pair.second->GetDescription(),
                               bound_instr.first, agg));
    }
  }
  for (auto pair : int_metrics_)
  {
    for (auto bound_instr : pair.second->GetBoundInstruments())
    {
        AggregatorVariant agg = bound_instr.second->GetAggregator();
      records.push_back(Record(pair.first, pair.second->GetDescription(),
                               bound_instr.first, agg));
    }
  }
  for (auto pair : float_metrics_)
  {
    for (auto bound_instr : pair.second->GetBoundInstruments())
    {
        AggregatorVariant agg = bound_instr.second->GetAggregator();
      records.push_back(Record(pair.first, pair.second->GetDescription(),
                               bound_instr.first, agg));
    }
  }
  for (auto pair : double_metrics_)
  {
    for (auto bound_instr : pair.second->GetBoundInstruments())
    {
        AggregatorVariant agg = bound_instr.second->GetAggregator();
      records.push_back(Record(pair.first, pair.second->GetDescription(),
                               bound_instr.first, agg));
    }
  }
  metrics_lock_.unlock();
}

/**
 * Creates {@code Record}s from all asynchronous metric instruments stored in this {@code meter}
 * object.
 *
 * Note: In order to capture the value of each instrument, that instrument's aggregator's
 * Checkpoint() function will be called, thus resetting the value held by the aggregator.
 *
 * @param records a reference to vector<Record>, passed from Collect() function. All Records
 * are stored in this vector.
 */
void Meter::CollectObservers(std::vector<Record> &records) noexcept
{
  observers_lock_.lock();
  for (auto obs : short_observers_)
  {
      auto aggs = obs.second->GetBoundAggregators();
      for (const auto &aggPair : aggs){
        records.push_back(Record(obs.first, obs.second->GetDescription(),
                                 aggPair.first, aggPair.second));
      }
  }
  for (auto obs : int_observers_)
  {
    auto aggs = obs.second->GetBoundAggregators();
    for (const auto &aggPair : aggs){
      records.push_back(Record(obs.first, obs.second->GetDescription(),
                               aggPair.first, aggPair.second));
    }
  }
  for (auto obs : float_observers_)
  {
    auto aggs = obs.second->GetBoundAggregators();
    for (const auto &aggPair: aggs){
      records.push_back(Record(obs.first, obs.second->GetDescription(),
                               aggPair.first, aggPair.second));
    }
  }
  for (auto obs : double_observers_)
  {
    auto aggs = obs.second->GetBoundAggregators();
    for (const auto &aggPair: aggs){
      records.push_back(Record(obs.first, obs.second->GetDescription(),
                               aggPair.first, aggPair.second));
    }
  }
  observers_lock_.unlock();
}

}  // namespace meter
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
