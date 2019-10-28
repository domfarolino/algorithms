load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

# This library target doesn't actually produce anything. It is only to export
# min_heap.h to other targets and packages. See
# https://groups.google.com/forum/#!topic/bazel-discuss/x7c8HJ6dke8.
cc_library(
  name = "min_heap",
  hdrs = ["min_heap.h"],
  deps = ["//vector:vector"],
)

cc_binary(
  name = "main_unittest",
  srcs = ["main_unittest.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":min_heap",
    "@gtest//:gtest",
    "@gtest//:gtest_main",
  ],
)
