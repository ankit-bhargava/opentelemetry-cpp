#pragma once

#include "opentelemetry/metrics/meter.h"
#include "opentelemetry/nostd/shared_ptr.h"
#include "opentelemetry/nostd/string_view.h"
#include "opentelemetry/sdk/metrics/record.h"
#include "opentelemetry/sdk/metrics/async_instruments.h"
#include "opentelemetry/sdk/metrics/instrument.h"
#include "opentelemetry/sdk/metrics/sync_instruments.h"
#include "opentelemetry/version.h"

#include <map>
#include <mutex>
#include <vector>

OPENTELEMETRY_BEGIN_NAMESPACE

namespace metrics_api = opentelemetry::metrics;

namespace sdk
{
namespace metrics
{
class Meter : public metrics_api::Meter
{
public:
  /**
   * The Meter class constructor.
   * @param library_name the name of the instrumented library
   * @param library_version optional, the version of the instrumented library
   */
  Meter(nostd::string_view library_name, nostd::string_view library_version = "") noexcept :
                 library_name_(library_name), library_version_(library_version) {}

  /**
   * Creates a Counter with the passed characteristics and a shared_ptr to that Counter.
   * Then adds that shared ptr to the metrics_ map before returning it.
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
  std::shared_ptr<SynchronousInstrument<short>> NewShortCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

  std::shared_ptr<SynchronousInstrument<int>> NewIntCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

  std::shared_ptr<SynchronousInstrument<float>> NewFloatCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

  std::shared_ptr<SynchronousInstrument<double>> NewDoubleCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

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
  std::shared_ptr<SynchronousInstrument<short>> NewShortUpDownCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

  std::shared_ptr<SynchronousInstrument<int>> NewIntUpDownCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

  std::shared_ptr<SynchronousInstrument<float>> NewFloatUpDownCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

  std::shared_ptr<SynchronousInstrument<double>> NewDoubleUpDownCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

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
  std::shared_ptr<SynchronousInstrument<short>> NewShortValueRecorder(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

  std::shared_ptr<SynchronousInstrument<int>> NewIntValueRecorder(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

  std::shared_ptr<SynchronousInstrument<float>> NewFloatValueRecorder(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

  std::shared_ptr<SynchronousInstrument<double>> NewDoubleValueRecorder(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled);

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
  std::shared_ptr<AsynchronousInstrument<short>> NewShortSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<short>));

  std::shared_ptr<AsynchronousInstrument<int>> NewIntSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<int>));

  std::shared_ptr<AsynchronousInstrument<float>> NewFloatSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<float>));

  std::shared_ptr<AsynchronousInstrument<double>> NewDoubleSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<double>));

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
  std::shared_ptr<AsynchronousInstrument<short>> NewShortUpDownSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<short>));

  std::shared_ptr<AsynchronousInstrument<int>> NewIntUpDownSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<int>));

  std::shared_ptr<AsynchronousInstrument<float>> NewFloatUpDownSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<float>));

  std::shared_ptr<AsynchronousInstrument<double>> NewDoubleUpDownSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<double>));

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
  std::shared_ptr<AsynchronousInstrument<short>> NewShortValueObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<short>));

  std::shared_ptr<AsynchronousInstrument<int>> NewIntValueObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<int>));

  std::shared_ptr<AsynchronousInstrument<float>> NewFloatValueObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<float>));

  std::shared_ptr<AsynchronousInstrument<double>> NewDoubleValueObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
      void (*callback)(ObserverResult<double>));

  /**
   * Utility method that allows users to atomically record measurements to a set of
   * synchronous metric instruments with a common set of labels.
   *
   * @param labels a map of strings to strings representing key-value pairs labels.
   * @param values a map of SynchronousInstruments to variant<int, double>. Each instrument in
   * the map is the instrument to record to, and the corresponding key is the value to record to
   * that instrument.
   */
  void RecordShortBatch(
      const trace::KeyValueIterable &labels,
      nostd::span<const nostd::shared_ptr<metrics_api::SynchronousInstrument<short>>> instruments,
      nostd::span<const short> values) noexcept;

  void RecordIntBatch(
      const trace::KeyValueIterable &labels,
      nostd::span<const std::pair<nostd::shared_ptr<metrics_api::SynchronousInstrument<int>>, int>> values) noexcept;

  void RecordFloatBatch(
      const trace::KeyValueIterable &labels,
      nostd::span<const std::pair<nostd::shared_ptr<metrics_api::SynchronousInstrument<float>>, float>> values) noexcept;

  void RecordDoubleBatch(
      const trace::KeyValueIterable &labels,
      nostd::span<const std::pair<nostd::shared_ptr<metrics_api::SynchronousInstrument<double>>, double>> values) noexcept;

    // now u can have versions which take a map, idk what yohannes will say but whatever
//    void RecordShortBatch(
//        const trace::KeyValueIterable &labels,
//        nostd::span<const nostd::shared_ptr<metrics_api::SynchronousInstrument<short>>> instruments,
//        nostd::span<const short> values) noexcept override;
//
//    void RecordIntBatch(
//        const trace::KeyValueIterable &labels,
//        nostd::span<const std::pair<nostd::shared_ptr<metrics_api::SynchronousInstrument<int>>, int>> values) noexcept override;
//
//    void RecordFloatBatch(
//        const trace::KeyValueIterable &labels,
//        nostd::span<const std::pair<nostd::shared_ptr<metrics_api::SynchronousInstrument<float>>, float>> values) noexcept override;
//
//    void RecordDoubleBatch(
//        const trace::KeyValueIterable &labels,
//        nostd::span<const std::pair<nostd::shared_ptr<metrics_api::SynchronousInstrument<double>>, double>> values) noexcept override;


  /**
   * Creates {@code Record}s from all metric instruments stored in this {@code meter}
   * object.
   *
   * Calls CollectMetrics and CollectObservers
   *
   * Note: In order to capture the value of each instrument, that instrument's aggregator's
   * Checkpoint() function will be called, thus resetting the value held by the aggregator.
   */
  std::vector<Record> Collect() noexcept;

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
  void CollectMetrics(std::vector<Record> &records) noexcept;

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
  void CollectObservers(std::vector<Record> &records) noexcept;

private:
std::map<std::string, std::shared_ptr<SynchronousInstrument<short>>> short_metrics_;
std::map<std::string, std::shared_ptr<SynchronousInstrument<int>>> int_metrics_;
std::map<std::string, std::shared_ptr<SynchronousInstrument<float>>> float_metrics_;
std::map<std::string, std::shared_ptr<SynchronousInstrument<double>>> double_metrics_;

std::map<std::string, std::shared_ptr<AsynchronousInstrument<short>>> short_observers_;
std::map<std::string, std::shared_ptr<AsynchronousInstrument<int>>> int_observers_;
std::map<std::string, std::shared_ptr<AsynchronousInstrument<float>>> float_observers_;
std::map<std::string, std::shared_ptr<AsynchronousInstrument<double>>> double_observers_;

std::string library_name_;
std::string library_version_;

std::mutex metrics_lock_;
std::mutex observers_lock_;
};

}  // namespace meter
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
