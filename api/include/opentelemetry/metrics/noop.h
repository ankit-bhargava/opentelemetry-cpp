#pragma once
#include "opentelemetry/metrics/sync_instruments.h"
#include "opentelemetry/metrics/async_instruments.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace metrics 
{

class NoopIntValueObserver : public IntValueObserver {

public:

    NoopIntValueObserver(nostd::string_view /*name*/, 
                         nostd::string_view /*description*/, 
                         nostd::string_view /*unit*/, 
                         bool /*enabled*/, 
                         void (*callback)(IntObserverResult)) {}

};

class NoopDoubleValueObserver : public DoubleValueObserver {

public:

    NoopDoubleValueObserver(nostd::string_view /*name*/, 
                            nostd::string_view /*description*/, 
                            nostd::string_view /*unit*/, 
                            bool enabled, void (*callback)(DoubleObserverResult)) {}

};

class NoopIntSumObserver : public IntSumObserver {

public:

    NoopIntSumObserver(nostd::string_view /*name*/, 
                       nostd::string_view /*description*/, 
                       nostd::string_view /*unit*/, 
                       bool /*enabled*/, 
                       void (*callback)(IntObserverResult)) {}

};

class NoopDoubleSumObserver : public DoubleSumObserver {

public:

    NoopDoubleSumObserver(nostd::string_view /*name*/, 
                          nostd::string_view /*description*/, 
                          nostd::string_view /*unit*/, 
                          bool /*enabled*/, 
                          void (*callback)(DoubleObserverResult)) {}

};

class NoopIntUpDownSumObserver : public IntUpDownSumObserver {

public:

    NoopIntUpDownSumObserver(nostd::string_view /*name*/, 
                             nostd::string_view /*description*/, 
                             nostd::string_view /*unit*/, 
                             bool /*enabled*/, 
                             void (*callback)(IntObserverResult)) {}

};

class NoopDoubleUpDownSumObserver : public DoubleUpDownSumObserver {

public:

    NoopDoubleUpDownSumObserver(nostd::string_view /*name*/, 
                                nostd::string_view /*description*/, nostd::string_view /*unit*/, 
                                bool /*enabled*/, 
                                void (*callback)(DoubleObserverResult)) {}

};

class BoundNoopIntCounter : public BoundIntCounter {

public:

    BoundNoopIntCounter() = default;

    BoundNoopIntCounter(nostd::string_view /*name*/, 
                        nostd::string_view /*description*/, 
                        nostd::string_view /*unit*/, 
                        bool /*enabled*/){}

    void add(int value){}
};

class NoopIntCounter : public IntCounter {

public:

    NoopIntCounter() =  default;

    NoopIntCounter(nostd::string_view /*name*/, 
                   nostd::string_view /*description*/, 
                   nostd::string_view /*unit*/, 
                   bool /*enabled*/) {}
    

    BoundNoopIntCounter bind(const nostd::string_view & /*labels*/){
        return BoundNoopIntCounter();
    }

    void add(int value, const nostd::string_view & /*labels*/){}

};


class BoundNoopDoubleCounter : public BoundDoubleCounter {

public:

    BoundNoopDoubleCounter() = default;

    BoundNoopDoubleCounter(nostd::string_view /*name*/, 
                           nostd::string_view /*description*/, nostd::string_view /*unit*/, 
                           bool /*enabled*/){}

    void add(double value){}

};

class NoopDoubleCounter : public DoubleCounter {

public:

    NoopDoubleCounter()=default;

    NoopDoubleCounter(nostd::string_view /*name*/, 
                      nostd::string_view /*description*/, 
                      nostd::string_view /*unit*/, 
                      bool /*enabled*/) {}
    

    BoundNoopDoubleCounter bind(const nostd::string_view & /*labels*/){
        return BoundNoopDoubleCounter();
    }

    void add(double value, const nostd::string_view & /*labels*/){}

};

class BoundNoopIntUpDownCounter : public BoundIntUpDownCounter {

public:

    BoundNoopIntUpDownCounter() = default;

    BoundNoopIntUpDownCounter(nostd::string_view /*name*/, 
                              nostd::string_view /*description*/, nostd::string_view /*unit*/, 
                              bool /*enabled*/) {}

    void add(int value){}

};

class NoopIntUpDownCounter : public IntUpDownCounter {

public:

    NoopIntUpDownCounter()=default;

    NoopIntUpDownCounter(nostd::string_view /*name*/, 
                         nostd::string_view /*description*/,
                         nostd::string_view /*unit*/, 
                         bool /*enabled*/) {}
    

    BoundNoopIntUpDownCounter bind(const nostd::string_view & /*labels*/){
        return BoundNoopIntUpDownCounter();
    }

    void add(int value, const nostd::string_view & /*labels*/){}
};

class BoundNoopDoubleUpDownCounter : public BoundDoubleUpDownCounter {

public:

    BoundNoopDoubleUpDownCounter() = default;

    BoundNoopDoubleUpDownCounter(nostd::string_view /*name*/,
                                 nostd::string_view /*description*/, nostd::string_view /*unit*/, 
                                 bool /*enabled*/){}

    void add(double value){}

};

class NoopDoubleUpDownCounter : public DoubleUpDownCounter {

public:

    NoopDoubleUpDownCounter()=default;

    NoopDoubleUpDownCounter(nostd::string_view /*name*/, 
                            nostd::string_view /*description*/, nostd::string_view /*unit*/, 
                            bool /*enabled*/) {}
    

    BoundNoopIntUpDownCounter bind(const nostd::string_view & /*labels*/){
        return BoundNoopIntUpDownCounter();
    }

    void add(double value, const nostd::string_view & /*labels*/){}
};

class BoundNoopIntValueRecorder : public BoundIntValueRecorder {

public:

    BoundNoopIntValueRecorder() = default;

    BoundNoopIntValueRecorder(nostd::string_view /*name*/, 
                              nostd::string_view /*description*/, nostd::string_view /*unit*/, 
                              bool /*enabled*/){}

    void record(int value){}

};

class NoopIntValueRecorder : public IntValueRecorder {

public:

    NoopIntValueRecorder()=default;

    NoopIntValueRecorder(nostd::string_view /*name*/, 
                         nostd::string_view /*description*/, 
                         nostd::string_view /*unit*/, 
                         bool /*enabled*/) {}
    

    BoundNoopIntValueRecorder bind(const nostd::string_view & /*labels*/){
        return BoundNoopIntValueRecorder();
    }

    void record(int value, const nostd::string_view & /*labels*/){}
};

class BoundNoopDoubleValueRecorder : public BoundDoubleValueRecorder {

public:

    BoundNoopDoubleValueRecorder() = default;

    BoundNoopDoubleValueRecorder(nostd::string_view /*name*/, 
                                 nostd::string_view /*description*/, nostd::string_view /*unit*/, 
                                 bool /*enabled*/){}

    void record(double value){}

};

class NoopDoubleValueRecorder : public DoubleValueRecorder {

public:

    NoopDoubleValueRecorder()=default;

    NoopDoubleValueRecorder(nostd::string_view /*name*/, 
                            nostd::string_view /*description*/, nostd::string_view /*unit*/, 
                            bool /*enabled*/) {}
    

    BoundNoopDoubleValueRecorder bind(const nostd::string_view & /*labels*/){
        return BoundNoopDoubleValueRecorder();
    }

    void record(double value, const nostd::string_view & /*labels*/){}
};

}
OPENTELEMETRY_END_NAMESPACE