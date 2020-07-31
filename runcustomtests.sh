#!/bin/bash

set -e

#bazel build --cxxopt='-std=c++17' //api/test/metrics:noop_instrument_test
#bazel-bin/api/test/metrics/noop_instrument_test
#bazel build --cxxopt='-std=c++17' //sdk/test/metrics:counter_aggregator_test
#bazel-bin/sdk/test/metrics/counter_aggregator_test
#bazel build --cxxopt='-std=c++17' //sdk/test/metrics:histogram_aggregator_test
#bazel-bin/sdk/test/metrics/histogram_aggregator_test
bazel build --cxxopt='-std=c++17' //sdk/test/metrics:metric_instrument_test
bazel-bin/sdk/test/metrics/metric_instrument_test
