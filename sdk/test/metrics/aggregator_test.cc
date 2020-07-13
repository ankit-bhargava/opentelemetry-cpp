#include "opentelemetry/sdk/metrics/aggregator.h"

#include <gtest/gtest.h>
#include <thread>
#include <numeric>
//#include <chrono>

namespace metrics_api = opentelemetry::metrics;

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

TEST(CounterAggregator, NoUpdates)
{
    CounterAggregator alpha(metrics_api::BoundInstrumentKind::BoundIntCounter);

    EXPECT_EQ(alpha.get_checkpoint().size(), 1); 
    EXPECT_EQ(alpha.get_checkpoint()[0], 0);

    alpha.checkpoint();
    EXPECT_EQ(alpha.get_checkpoint().size(), 1); 
    EXPECT_EQ(alpha.get_checkpoint()[0], 0);
}

TEST(CounterAggregator, Update)
{
    CounterAggregator alpha(metrics_api::BoundInstrumentKind::BoundIntCounter);
    CounterAggregator beta(metrics_api::BoundInstrumentKind::BoundIntCounter);
    
    for (int i = 0; i<123456; i++){
        alpha.update(1);
    }

    int sum = 0;
    for (int i = 0; i < 100; i++){
        int tmp = std::rand();
        beta.update(tmp);
        sum+=tmp;
    }

    EXPECT_EQ(alpha.get_checkpoint()[0], 0); // checkpoint shouldn't change even with updates
    EXPECT_EQ(beta.get_checkpoint()[0], 0);

    alpha.checkpoint();
    beta.checkpoint();

    EXPECT_EQ(alpha.get_checkpoint()[0], 123456);
    EXPECT_EQ(beta.get_checkpoint()[0], sum);

    alpha.update(15);
    alpha.checkpoint();
    EXPECT_EQ(alpha.get_checkpoint()[0], 15); //reset to 0 after first checkpoint call
}

void incrementingCallback(Aggregator & agg) // move to top, leave here for readability
{
    for (int i = 0; i< 1000000; i++){
        agg.update(1);
    }
}

TEST(CounterAggregator, Concurrency){
    CounterAggregator alpha(metrics_api::BoundInstrumentKind::BoundIntCounter);

    std::thread first (incrementingCallback, std::ref(alpha));     // spawn new threads that call the callback
    std::thread second (incrementingCallback, std::ref(alpha));

    // synchronize threads:
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes

    alpha.checkpoint();
    EXPECT_EQ(alpha.get_checkpoint()[0], 2*1000000);
}

TEST(CounterAggregator, Merge)
{
    CounterAggregator alpha(metrics_api::BoundInstrumentKind::BoundIntCounter);
    CounterAggregator beta(metrics_api::BoundInstrumentKind::BoundIntCounter);
    
    alpha.merge(beta);

    alpha.checkpoint();
    EXPECT_EQ(alpha.get_checkpoint()[0], 0); //merge with no updates

    for (int i = 0; i<500; i++){
        alpha.update(1);
    }

    for (int i = 0; i<700; i++){
        beta.update(1);
    }

    alpha.merge(beta);
    alpha.checkpoint();
    EXPECT_EQ(alpha.get_checkpoint()[0], 1200);

    //HistogramAggregator gamma(metrics_api::BoundInstrumentKind::BoundValueRecorder);
    //ASSERT_THROW(alpha.merge(gamma), AggregatorMismatch);
}

TEST(Histogram, Uniform)
{
    std::vector<int> boundaries{10,20,30,40,50};
    HistogramAggregator alpha(metrics_api::BoundInstrumentKind::BoundIntCounter, boundaries);

    alpha.checkpoint();
    EXPECT_EQ(alpha.get_checkpoint().size(),2);
    EXPECT_EQ(alpha.get_counts().size(),6);

    for (int i = 0; i< 60; i++){
        alpha.update(i);
    }

    alpha.checkpoint();

    EXPECT_EQ(alpha.get_checkpoint()[0], 1770);
    EXPECT_EQ(alpha.get_checkpoint()[1], 60);

    std::vector<int> correct = {10,10,10,10,10,10};
    EXPECT_EQ(alpha.get_counts(), correct);
}

TEST(Histogram, Normal)
{
    std::vector<int> boundaries{2,4,6,8,10,12};
    HistogramAggregator alpha(metrics_api::BoundInstrumentKind::BoundIntCounter, boundaries);

    std::vector<int> vals{1,3,3,5,5,5,7,7,7,7,9,9,9,11,11,13};
    for (int i : vals){
        alpha.update(i);
    }

    alpha.checkpoint();

    EXPECT_EQ(alpha.get_checkpoint()[0], std::accumulate(vals.begin(),vals.end(),0));
    EXPECT_EQ(alpha.get_checkpoint()[1], vals.size());

    std::vector<int> correct = {1,2,3,4,3,2,1};
    EXPECT_EQ(alpha.get_counts(), correct);
}

TEST(Histogram, Merge){
    std::vector<int> boundaries{2,4,6,8,10,12};
    HistogramAggregator alpha(metrics_api::BoundInstrumentKind::BoundIntCounter, boundaries);
    HistogramAggregator beta(metrics_api::BoundInstrumentKind::BoundIntCounter, boundaries);

    std::vector<int> vals{1,3,3,5,5,5,7,7,7,7,9,9,9,11,11,13};
    for (int i : vals){
        alpha.update(i);
    }

    std::vector<int> otherVals{1,1,1,1,11,11,13,13,13,15};
    for (int i : otherVals){
        beta.update(i);
    }
    alpha.merge(beta);
    alpha.checkpoint();

    EXPECT_EQ(alpha.get_checkpoint()[0], std::accumulate(vals.begin(),vals.end(),0)+std::accumulate(otherVals.begin(), otherVals.end(), 0));
    EXPECT_EQ(alpha.get_checkpoint()[1], vals.size()+otherVals.size());

    std::vector<int> correct = {5,2,3,4,3,4,5};
    EXPECT_EQ(alpha.get_counts(), correct);
}

void histogramUpdateCallback(Aggregator & agg, std::vector<int> vals){
    for (int i: vals){
        agg.update(i);
    }
}

int randVal(){
    return rand() % 15;
}

TEST(Histogram, Concurrency){
    std::vector<int> boundaries{2,4,6,8,10,12};
    HistogramAggregator alpha(metrics_api::BoundInstrumentKind::BoundIntCounter, boundaries);

    std::vector<int> vals1(1000);
    std::generate(vals1.begin(),vals1.end(),randVal);

    std::vector<int> vals2(1000);
    std::generate(vals2.begin(),vals2.end(),randVal);

    std::thread first (histogramUpdateCallback, std::ref(alpha), vals1);     // spawn new threads that call the callback
    std::thread second (histogramUpdateCallback, std::ref(alpha), vals2);

    // synchronize threads:
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes

    HistogramAggregator beta(metrics_api::BoundInstrumentKind::BoundIntCounter, boundaries);


    //auto start = std::chrono::system_clock::now();
    for (int i: vals1){
        beta.update(i);
    }
    for (int i: vals2){
        beta.update(i);
    }
    //auto end = std::chrono::system_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    //std::cout <<"Update time: " <<elapsed.count() <<std::endl;

    alpha.checkpoint();
    beta.checkpoint();

    EXPECT_EQ(alpha.get_checkpoint(), beta.get_checkpoint());
    EXPECT_EQ(alpha.get_counts(), beta.get_counts());
}


}  // namespace sdk
}  // namespace metrics
OPENTELEMETRY_END_NAMESPACE
