load("//bazel:otel_cc_benchmark.bzl", "otel_cc_benchmark")


cc_test(
    name = "noop_instrument_test",
    srcs = [
        "noop_instrument_test.cc",
    ],
    linkstatic = 1,
    deps = [
        "//api",
        "@com_google_googletest//:gtest_main",
    ],
)
