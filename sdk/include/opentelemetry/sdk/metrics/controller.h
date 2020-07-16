#pragma once

#include "opentelemetry/version.h"
#include "opentelemetry/metrics/instrument.h"

#include <unistd.h>
#include <thread>
#include <sstream>
#include <vector>
#include <iostream>

namespace metrics_api = opentelemetry::metrics;
namespace trace_api = opentelemetry::trace;

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics 
{

std::string vec2str(std::vector<int> conv){
    std::stringstream ss;
    ss <<"(";
    for (int i:conv){
        ss <<i <<", ";
    }
    ss <<")";
    return ss.str();
}

class Record {
    
public:
    Record() = default;
    
    Record(std::vector<int> values, std::string name, std::string description, std::string units):
    values_(values), name_(name), description_(description), units_(units) {}
    
    std::vector<int> values_;
    std::string name_;
    std::string description_;
    std::string units_;
};

class Meter {
    
public:
    Meter() = default;
    
    Meter(std::vector<Record> collected): collected_(collected) {}
    
    std::vector<Record> collect() {
        return collected_;
    }
    
    std::vector<Record> collected_;
};



class Processor {
    
public:
    Processor() = default;
    
    std::vector<Record> checkpointSet(){
        return returnSet_;
    }
    
    void process(std::vector<Record> input){
        returnSet_ = input;
    }
    
    void startCollection(){}
    
    void finishCollection(){}
    
    std::vector<Record> returnSet_;
};

class Exporter {
    
public:
    Exporter() = default;
    
    void export_records(std::vector<Record> records){
        for (auto i: records){
            std::cout <<i.name_ <<", " <<i.description_ <<", " <<i.units_ <<", " <<vec2str(i.values_) <<std::endl;
        }
    }
};

class PushController {
    
public:
 
    // Ask hudson -- the meter provider is initializes with the exporter and processor like tracing or do we use the conroller as
    // the container for all of that
    PushController(Meter & meter, Exporter & exporter, Processor & processor,
                            double period, int timeout) {
        meter_ = meter;
        exporter_ = exporter;
        processor_ = processor;
        timeout_ = timeout;
        period_ = (unsigned int)(period * 1000000); //convert to microseconds
        std::cout <<"constructor" <<std::endl;
    }
    
    /*
    * Used to check if the metrics pipeline is currecntly active
    *
    * @param none
    * @return true when active, false when on standby
    */
    bool isActive() {
        return active_;
    }

   /*
    * Begins the data processing and export pipeline.  The function first ensures that the pipeline
    * is not already running.  If not, it begins and detaches a new thread for the Controller's run function
    * which periodically polls the instruments for their data.
    *
    * @param none
    * @return a boolean which is true when the pipeline is successfully started and false when already active
    */
    bool start(){
        if (!active_){
            active_ = true;
            std::cout <<"spawning new thread" <<std::endl;
            std::thread runner (&PushController::run, this);
            runner.detach();
            std::cout <<"thread detached; start function terminated" <<std::endl;
            // as far as I know, there's no way to kill a thread once detached, but detaching is necessary.
            return true;
        }
        return false;
    }
    
   /*
    * Ends the processing and export pipeline then exports metrics one last time
    * before returning.
    *
    * @param none
    * @return none
    */
    void stop(){ //make this blocking
        active_ = false;
        usleep(period_);
        tick(); //flush metrics sitting in the processor
    }
    
   /*
    * Run
    *
    * Used to wait between collection intervals.
    *
    */
    void run(){
        std::cout <<"started running" <<std::endl;
        while (active_){
            tick();
            usleep(period_);
        }
        std::cout <<"finished running" <<std::endl;
    }
    
   /*
    * Tick (THREAD SAFE)
    *
    * Called at regular intervals, this function collects all values from the
    * member variable meter_, then sends them to the processor_ for
    * processing. After the records have been processed they are sent to the
    * exporter_ to be exported.
    *
    */
    void tick(){
        std::cout <<"tick" <<std::endl;
        processor_.startCollection();
        
        // processor stores the collection of records
        //clarify the pipeline, does
        processor_.process(meter_.collect());
        exporter_.export_records(processor_.checkpointSet());
        
        processor_.finishCollection();
    }
    
    Meter meter_;
    Exporter exporter_;
    Processor processor_;
    bool active_ = false;
    unsigned int period_;
    unsigned int timeout_;
};

} // namespace metrics
} // namespace sdk
OPENTELEMETRY_END_NAMESPACE


// does the controller have to stop immediately, or can it wait until the collection interval is over
// how do we maintain a steady ticking (or do we need to), can't use sleep because the actual collection and exporting will take time
