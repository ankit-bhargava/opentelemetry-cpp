foreach(testname ostream_metrics_test ostream_span_test)
    add_executable(${testname} "${testname}.cc")
    target_link_libraries(${testname} ${GTEST_BOTH_LIBRARIES}
            ${CMAKE_THREAD_LIBS_INIT} opentelemetry_ostream_exporter)
    gtest_add_tests(TARGET ${testname} TEST_PREFIX ostream_exporter. TEST_LIST ${testname})
endforeach()
