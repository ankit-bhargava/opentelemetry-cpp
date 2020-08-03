//
//  main.cpp
//  playground
//
//  Created by Bhargava, Ankit on 6/30/20.
//  Copyright © 2020 Bhargava, Ankit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include <vector>
#include <unistd.h>
#include <typeinfo>
#include <variant>
#include <unordered_map>
#include <map>

#include "opentelemetry/sdk/metrics/controller.h"
#include "opentelemetry/sdk/metrics/meter.h"
#include "opentelemetry/sdk/metrics/ungrouped_processor.h"

namespace metrics_api = opentelemetry::metrics;
namespace metrics_sdk = opentelemetry::sdk::metrics;
namespace metrics_exporter = opentelemetry::exporter::metrics;

using namespace std;

void ObserverConstructorCallback(metrics_api::ObserverResult<int> result){
    std::map<std::string, std::string> labels = {{"key", "value"}};
    auto labelkv = opentelemetry::trace::KeyValueIterableView<decltype(labels)>{labels};
    result.observe(1,labelkv);
}

class MetricGenerator {
    
public:
    
    static void generateData() {
        std::cout <<"generating data" <<std::endl;
        
        // 1. Initialize exporter
        std::unique_ptr<metrics_sdk::MetricsExporter> e = std::unique_ptr<metrics_sdk::MetricsExporter>(new metrics_exporter::OStreamMetricsExporter);
        
        // 2. Initialize processor
        std::shared_ptr<metrics_sdk::MetricsProcessor> p = std::shared_ptr<metrics_sdk::MetricsProcessor>(new metrics_sdk::UngroupedMetricsProcessor(false));
        
        // 3. Initialize meter
        std::shared_ptr<metrics_api::Meter> m = std::shared_ptr<metrics_api::Meter>(new metrics_sdk::Meter("Test"));
        
        // 4. Initialize Controller
        metrics_sdk::PushController c(m, std::move(e),p, 5);
        c.start();
        
        // 5. use these to instrument some work
        doSomeSimulatedWork(m);
        
        // 6. shutdown metric collector
        c.stop();
        
    }
    
private:
    //    static void doSomeSimulatedWork(metrics::api::Meter &m){
    static map<string,string> str2map(string alpha){
        map<string,string> ret;
        while (alpha.find(',') != string::npos){
            string key = alpha.substr(0,alpha.find(','));
            alpha = alpha.substr(alpha.find(',')+2);
            string value = alpha.substr(0,alpha.find(','));
            alpha = alpha.substr(alpha.find(',')+2);
            ret[key] = value;
        }
        return ret;
    }
    
    static void doSomeSimulatedWork(std::shared_ptr<metrics_api::Meter> m){
        std::cout <<"simulating work" <<std::endl;
        ifstream goldenData;
        goldenData.open("sdk/test/data/RefData.csv");
        
        auto ctr= m->NewIntCounter("Counter","none", "none", true);
        auto udctr= m->NewIntUpDownCounter("upDownCounter","none", "none", true);
        auto vrec= m->NewIntValueRecorder("Recorder","none", "none", true);
        auto sobs= m->NewIntSumObserver("SumObserver","none", "none", true, &ObserverConstructorCallback);
        auto udobs= m->NewIntUpDownSumObserver("UpDownSumObserver","none", "none", true, &ObserverConstructorCallback);
        auto vobs= m->NewIntValueObserver("ValueObserver","none", "none", true, &ObserverConstructorCallback);
        
        std::string line;
        while (std::getline(goldenData,line)){
            std::string instrument = line.substr(0,line.find(','));
            int val = stoi(line.substr(line.find(',')+1,line.find('"')-line.find(',')-2));
            std::string labels = line.substr(line.find('"')+1, line.rfind('"')-line.find('"')-1);
            map<string,string> labelmap = str2map(labels);
            auto labelkv = opentelemetry::trace::KeyValueIterableView<decltype(labelmap)>{labelmap};
            
            if (instrument == "ctr"){
                printf("ctr->add(%i, \"%s\")\n", val, labels.c_str());
                ctr->add(val, labelkv);
            } else if (instrument == "udctr"){
                printf("udctr->add(%i, \"%s\")\n", val, labels.c_str());
                udctr->add(val, labelkv);
            }
            else if (instrument == "vrec"){
                printf("vrec->record(%i, \"%s\")\n", val, labels.c_str());
                vrec->record(val, labelkv);
            } else if (instrument == "sobs"){
                printf("sobs->observe(%i, \"%s\")\n", val, labels.c_str());
                sobs->observe(val, labelkv);
            } else if (instrument == "udobs"){
                printf("udobs->observe(%i, \"%s\")\n", val, labels.c_str());
                udobs->observe(val, labelkv);
            } else if (instrument == "vobs"){
                printf("voobs->observe(%i, \"%s\")\n", val, labels.c_str());
                vobs->observe(val, labelkv);
            } else {
                printf("bad entry");
            }
//            usleep(.1*1000000);
        }
        
    }
};


int main(int argc, const char * argv[]) {
    std::cout <<"working" <<std::endl;
    MetricGenerator::generateData();
}
