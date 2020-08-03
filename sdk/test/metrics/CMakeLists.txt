foreach(testname controller_test counter_aggregator_test histogram_aggregator_test
        meter_test metric_instrument_test record_test sketch_aggregator_test
        ungrouped_processor_test)
    add_executable(${testname} "${testname}.cc")
    target_link_libraries(${testname} ${GTEST_BOTH_LIBRARIES}
            ${CMAKE_THREAD_LIBS_INIT} opentelemetry_metrics opentelemetry_ostream_exporter)
    gtest_add_tests(TARGET ${testname} TEST_PREFIX metrics. TEST_LIST ${testname})
endforeach()
