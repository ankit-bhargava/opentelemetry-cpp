#!/bin/bash

set -e

bazel build //sdk/test/metrics:controller_test
for (( c=1; c<=100000; c++ ))
do  
   bazel-bin/sdk/test/metrics/controller_test
   echo "$c  ################################################"
done
