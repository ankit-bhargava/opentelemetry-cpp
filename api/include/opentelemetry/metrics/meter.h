#pragma once

#include "opentelemetry/metrics/async_instruments.h"
#include "opentelemetry/metrics/instrument.h"
#include "opentelemetry/metrics/sync_instruments.h"
#include "opentelemetry/metrics/noop.h"
#include "opentelemetry/nostd/shared_ptr.h"
#include "opentelemetry/nostd/span.h"
#include "opentelemetry/nostd/string_view.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace metrics
{
/**
 * Handles instrument creation and provides a facility for batch recording.
 *
 * This class provides methods to create new metric instruments, record a
 * batch of values to a specified set of instruments, and collect
 * measurements from all instruments.
 *
 */
class Meter
{
public:
  virtual ~Meter() = default;
    
    Meter() = default;

  /**
   * Creates a Counter with the passed characteristics and returns a shared_ptr to that Counter.
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
  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<short>> NewNoopShortCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                         const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<short>>();
  };

  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<int>> NewNoopIntCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                     const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<int>>();
  };

  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<float>> NewNoopFloatCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                         const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<float>>();
  };

  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<double>> NewNoopDoubleCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                           const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<double>>();
  };

  /**
   * Creates an UpDownCounter with the passed characteristics and returns a shared_ptr to that
   * UpDownCounter.
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
  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<short>> NewNoopShortUpDownCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                               const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<short>>();
  };

  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<int>> NewNoopIntUpDownCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                           const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<int>>();
  };

  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<float>> NewNoopFloatUpDownCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                               const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<float>>();
  };

  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<double>> NewNoopDoubleUpDownCounter(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                                 const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<double>>();
  };

  /**
   * Creates a ValueRecorder with the passed characteristics and returns a shared_ptr to that
   * ValueRecorder.
   *
   * @param name the name of the new ValueRecorder.
   * @param description a brief description of what the ValueRecorder is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @return a shared pointer to the created DoubleValueRecorder.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<short>> NewNoopShortValueRecorder(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                               const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<short>>();
  };

  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<int>> NewNoopIntValueRecorder(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                           const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<int>>();
  };

  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<float>> NewNoopFloatValueRecorder(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                               const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<float>>();
  };

  virtual opentelemetry::nostd::shared_ptr<SynchronousInstrument<double>> NewNoopDoubleValueRecorder(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
                                                                                                 const bool enabled) {
      return opentelemetry::nostd::shared_ptr<SynchronousInstrument<double>>();
  };

  /**
   * Creates a SumObserver with the passed characteristics and returns a shared_ptr to that
   * SumObserver.
   *
   * @param name the name of the new SumObserver.
   * @param description a brief description of what the SumObserver is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @param callback the function to be observed by the instrument.
   * @return a shared pointer to the created SumObserver.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<short>> NewNoopShortSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                              void (*callback)(ObserverResult<short>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<short>>();
  };

  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<int>> NewNoopIntSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                          void (*callback)(ObserverResult<int>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<int>>();
  };

  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<float>> NewNoopFloatSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                              void (*callback)(ObserverResult<float>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<float>>();
  };

  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<double>> NewNoopDoubleSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                                void (*callback)(ObserverResult<double>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<double>>();
  };

  /**
   * Creates an UpDownSumObserver with the passed characteristics and returns a shared_ptr to
   * that UpDowNSumObserver.
   *
   * @param name the name of the new UpDownSumObserver.
   * @param description a brief description of what the UpDownSumObserver is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @param callback the function to be observed by the instrument.
   * @return a shared pointer to the created UpDownSumObserver.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<short>> NewNoopShortUpDownSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                                    void (*callback)(ObserverResult<short>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<short>>();
  };

  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<int>> NewNoopIntUpDownSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                                void (*callback)(ObserverResult<int>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<int>>();
  };

  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<float>> NewNoopFloatUpDownSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                                    void (*callback)(ObserverResult<float>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<float>>();
  };

  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<double>> NewNoopDoubleUpDownSumObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                                      void (*callback)(ObserverResult<double>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<double>>();
  };

  /**
   * Creates a ValueObserver with the passed characteristics and returns a shared_ptr to that
   * ValueObserver.
   *
   * @param name the name of the new ValueObserver.
   * @param description a brief description of what the ValueObserver is used for.
   * @param unit the unit of metric values following https://unitsofmeasure.org/ucum.html.
   * @param enabled a boolean value that turns on or off the metric instrument.
   * @param callback the function to be observed by the instrument.
   * @return a shared pointer to the created ValueObserver.
   * @throws NullPointerException if {@code name} is null
   * @throws IllegalArgumentException if a different metric by the same name exists in this meter.
   * @throws IllegalArgumentException if the {@code name} does not match spec requirements.
   */
  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<short>> NewNoopShortValueObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                                void (*callback)(ObserverResult<short>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<short>>();
  };

  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<int>> NewNoopIntValueObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                            void (*callback)(ObserverResult<int>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<int>>();
  };

  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<float>> NewNoopFloatValueObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                                void (*callback)(ObserverResult<float>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<float>>();
  };

  virtual opentelemetry::nostd::shared_ptr<AsynchronousInstrument<double>> NewNoopDoubleValueObserver(
      nostd::string_view name,
      nostd::string_view description,
      nostd::string_view unit,
      const bool enabled,
                                                                                                  void (*callback)(ObserverResult<double>)) {
      return opentelemetry::nostd::shared_ptr<AsynchronousInstrument<double>>();
  };

  /**
   * Utility method that allows users to atomically record measurements to a set of
   * synchronous metric instruments with a common set of labels.
   *
   * @param labels the set of labels to associate with this recorder.
   * @param values a span of pairs where the first element of the pair is a metric instrument
   * to record to, and the second element is the value to update that instrument with.
   */
  virtual void RecordShortBatch(
      const trace::KeyValueIterable &labels,
      nostd::span<const nostd::shared_ptr<SynchronousInstrument<short>>> instruments,
                                nostd::span<const short> values) noexcept {};

  void RecordShortBatch(std::initializer_list<std::pair<nostd::string_view, nostd::string_view>> labels,
                        std::initializer_list<nostd::shared_ptr<SynchronousInstrument<short>>> instruments,
                        std::initializer_list<short> values)
  {
    opentelemetry::trace::KeyValueIterableView<std::initializer_list<std::pair<nostd::string_view, nostd::string_view>>> labelskv{labels};

    RecordShortBatch(labelskv,
                     nostd::span<const nostd::shared_ptr<SynchronousInstrument<short>>> {instruments.begin(), instruments.end()},
                     nostd::span<const short> {values.begin(), values.end()});
  }

  virtual void RecordIntBatch(
      const trace::KeyValueIterable &labels,
                              nostd::span<const std::pair<nostd::shared_ptr<SynchronousInstrument<int>>, int>> values) noexcept {};

  void RecordIntBatch(std::initializer_list<std::pair<nostd::string_view, nostd::string_view>> labels,
                      std::initializer_list<std::pair<nostd::shared_ptr<SynchronousInstrument<int>>, int>> values)
  {
    opentelemetry::trace::KeyValueIterableView<std::initializer_list<std::pair<nostd::string_view, nostd::string_view>>> labelskv{labels};

    RecordIntBatch(labelskv, nostd::span<const std::pair<nostd::shared_ptr<SynchronousInstrument<int>>, int>>{values.begin(), values.end()});
  }

  virtual void RecordFloatBatch(
      const trace::KeyValueIterable &labels,
                                nostd::span<const std::pair<nostd::shared_ptr<SynchronousInstrument<float>>, float>> values) noexcept {};

  void RecordFloatBatch(std::initializer_list<std::pair<nostd::string_view, nostd::string_view>> labels,
                        std::initializer_list<std::pair<nostd::shared_ptr<SynchronousInstrument<float>>, float>> values)
  {
    opentelemetry::trace::KeyValueIterableView<std::initializer_list<std::pair<nostd::string_view, nostd::string_view>>> labelskv{labels};

    RecordFloatBatch(labelskv, nostd::span<const std::pair<nostd::shared_ptr<SynchronousInstrument<float>>, float>>{values.begin(), values.end()});
  }

  virtual void RecordDoubleBatch(
      const trace::KeyValueIterable &labels,
                                 nostd::span<const std::pair<nostd::shared_ptr<SynchronousInstrument<double>>, double>> values) noexcept {};

  void RecordDoubleBatch(std::initializer_list<std::pair<nostd::string_view, nostd::string_view>> labels,
                        std::initializer_list<std::pair<nostd::shared_ptr<SynchronousInstrument<double>>, double>> values)
  {
    opentelemetry::trace::KeyValueIterableView<std::initializer_list<std::pair<nostd::string_view, nostd::string_view>>> labelskv{labels};

    RecordDoubleBatch(labelskv, nostd::span<const std::pair<nostd::shared_ptr<SynchronousInstrument<double>>, double>>{values.begin(), values.end()});
  }



};
}  // namespace metrics
OPENTELEMETRY_END_NAMESPACE
