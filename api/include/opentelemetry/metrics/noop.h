#pragma once
#include "opentelemetry/metrics/async_instruments.h"
#include "opentelemetry/metrics/sync_instruments.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace metrics
{

class NoopIntValueObserver : public IntValueObserver
{

public:
  NoopIntValueObserver(nostd::string_view /*name*/,
                       nostd::string_view /*description*/,
                       nostd::string_view /*unit*/,
                       bool /*enabled*/,
                       void (*callback)(ObserverResult))
  {}
};

class NoopDoubleValueObserver : public DoubleValueObserver
{

public:
  NoopDoubleValueObserver(nostd::string_view /*name*/,
                          nostd::string_view /*description*/,
                          nostd::string_view /*unit*/,
                          bool enabled,
                          void (*callback)(ObserverResult))
  {}
};

class NoopIntSumObserver : public IntSumObserver
{

public:
  NoopIntSumObserver(nostd::string_view /*name*/,
                     nostd::string_view /*description*/,
                     nostd::string_view /*unit*/,
                     bool /*enabled*/,
                     void (*callback)(ObserverResult))
  {}
};

class NoopDoubleSumObserver : public DoubleSumObserver
{

public:
  NoopDoubleSumObserver(nostd::string_view /*name*/,
                        nostd::string_view /*description*/,
                        nostd::string_view /*unit*/,
                        bool /*enabled*/,
                        void (*callback)(ObserverResult))
  {}
};

class NoopIntUpDownSumObserver : public IntUpDownSumObserver
{

public:
  NoopIntUpDownSumObserver(nostd::string_view /*name*/,
                           nostd::string_view /*description*/,
                           nostd::string_view /*unit*/,
                           bool /*enabled*/,
                           void (*callback)(ObserverResult))
  {}
};

class NoopDoubleUpDownSumObserver : public DoubleUpDownSumObserver
{

public:
  NoopDoubleUpDownSumObserver(nostd::string_view /*name*/,
                              nostd::string_view /*description*/,
                              nostd::string_view /*unit*/,
                              bool /*enabled*/,
                              void (*callback)(ObserverResult))
  {}
};

class BoundNoopIntCounter : public BoundIntCounter
{

public:
  BoundNoopIntCounter() = default;

  BoundNoopIntCounter(nostd::string_view /*name*/,
                      nostd::string_view /*description*/,
                      nostd::string_view /*unit*/,
                      bool /*enabled*/)
  {}

  virtual void add(int value) override {}
};

class NoopIntCounter : public IntCounter
{

public:
  NoopIntCounter() = default;

  NoopIntCounter(nostd::string_view /*name*/,
                 nostd::string_view /*description*/,
                 nostd::string_view /*unit*/,
                 bool /*enabled*/)
  {}

  nostd::shared_ptr<BoundNoopIntCounter> bind(const nostd::string_view & /*labels*/)
  {
    return nostd::shared_ptr<BoundNoopIntCounter>(new BoundNoopIntCounter());
  }

  virtual void add(int value, const nostd::string_view & /*labels*/) override {}
};

class BoundNoopDoubleCounter : public BoundDoubleCounter
{

public:
  BoundNoopDoubleCounter() = default;

  BoundNoopDoubleCounter(nostd::string_view /*name*/,
                         nostd::string_view /*description*/,
                         nostd::string_view /*unit*/,
                         bool /*enabled*/)
  {}

  virtual void add(double value) override {}
};

class NoopDoubleCounter : public DoubleCounter
{

public:
  NoopDoubleCounter() = default;

  NoopDoubleCounter(nostd::string_view /*name*/,
                    nostd::string_view /*description*/,
                    nostd::string_view /*unit*/,
                    bool /*enabled*/)
  {}

  nostd::shared_ptr<BoundNoopDoubleCounter> bind(const nostd::string_view & /*labels*/)
  {
    return nostd::shared_ptr<BoundNoopDoubleCounter>(new BoundNoopDoubleCounter());
  }

  virtual void add(double value, const nostd::string_view & /*labels*/) override {}
};

class BoundNoopIntUpDownCounter : public BoundIntUpDownCounter
{

public:
  BoundNoopIntUpDownCounter() = default;

  BoundNoopIntUpDownCounter(nostd::string_view /*name*/,
                            nostd::string_view /*description*/,
                            nostd::string_view /*unit*/,
                            bool /*enabled*/)
  {}

  virtual void add(int value) override {}
};

class NoopIntUpDownCounter : public IntUpDownCounter
{

public:
  NoopIntUpDownCounter() = default;

  NoopIntUpDownCounter(nostd::string_view /*name*/,
                       nostd::string_view /*description*/,
                       nostd::string_view /*unit*/,
                       bool /*enabled*/)
  {}

  nostd::shared_ptr<BoundNoopIntUpDownCounter> bind(const nostd::string_view & /*labels*/)
  {
    return nostd::shared_ptr<BoundNoopIntUpDownCounter>(new BoundNoopIntUpDownCounter());
  }

  virtual void add(int value, const nostd::string_view & /*labels*/) override {}
};

class BoundNoopDoubleUpDownCounter : public BoundDoubleUpDownCounter
{

public:
  BoundNoopDoubleUpDownCounter() = default;

  BoundNoopDoubleUpDownCounter(nostd::string_view /*name*/,
                               nostd::string_view /*description*/,
                               nostd::string_view /*unit*/,
                               bool /*enabled*/)
  {}

  virtual void add(double value) override {}
};

class NoopDoubleUpDownCounter : public DoubleUpDownCounter
{

public:
  NoopDoubleUpDownCounter() = default;

  NoopDoubleUpDownCounter(nostd::string_view /*name*/,
                          nostd::string_view /*description*/,
                          nostd::string_view /*unit*/,
                          bool /*enabled*/)
  {}

  nostd::shared_ptr<BoundNoopDoubleUpDownCounter> bind(const nostd::string_view & /*labels*/)
  {
    return nostd::shared_ptr<BoundNoopDoubleUpDownCounter>(new BoundNoopDoubleUpDownCounter());
  }

  virtual void add(double value, const nostd::string_view & /*labels*/) override {}
};

class BoundNoopIntValueRecorder : public BoundIntValueRecorder
{

public:
  BoundNoopIntValueRecorder() = default;

  BoundNoopIntValueRecorder(nostd::string_view /*name*/,
                            nostd::string_view /*description*/,
                            nostd::string_view /*unit*/,
                            bool /*enabled*/)
  {}

  virtual void record(int value) override {}
};

class NoopIntValueRecorder : public IntValueRecorder
{

public:
  NoopIntValueRecorder() = default;

  NoopIntValueRecorder(nostd::string_view /*name*/,
                       nostd::string_view /*description*/,
                       nostd::string_view /*unit*/,
                       bool /*enabled*/)
  {}

  nostd::shared_ptr<BoundNoopIntValueRecorder> bind(const nostd::string_view & /*labels*/)
  {
    return nostd::shared_ptr<BoundNoopIntValueRecorder>(new BoundNoopIntValueRecorder());
  }

  virtual void record(int value, const nostd::string_view & /*labels*/) override {}
};

class BoundNoopDoubleValueRecorder : public BoundDoubleValueRecorder
{

public:
  BoundNoopDoubleValueRecorder() = default;

  BoundNoopDoubleValueRecorder(nostd::string_view /*name*/,
                               nostd::string_view /*description*/,
                               nostd::string_view /*unit*/,
                               bool /*enabled*/)
  {}

  virtual void record(double value) override {}
};

class NoopDoubleValueRecorder : public DoubleValueRecorder
{

public:
  NoopDoubleValueRecorder() = default;

  NoopDoubleValueRecorder(nostd::string_view /*name*/,
                          nostd::string_view /*description*/,
                          nostd::string_view /*unit*/,
                          bool /*enabled*/)
  {}

  nostd::shared_ptr<BoundNoopDoubleValueRecorder> bind(const nostd::string_view & /*labels*/)
  {
    return nostd::shared_ptr<BoundNoopDoubleValueRecorder>(new BoundNoopDoubleValueRecorder());
  }

  virtual void record(double value, const nostd::string_view & /*labels*/) override {}
};

}  // namespace metrics
OPENTELEMETRY_END_NAMESPACE