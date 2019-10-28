load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

# This library target doesn't actually produce anything. It is only to export
# vector.h to other targets and packages. See
# https://groups.google.com/forum/#!topic/bazel-discuss/x7c8HJ6dke8.
cc_library(
  name = "vector",
  hdrs = ["vector.h"],
)

cc_binary(
  name = "main_unittest",
  srcs = ["main_unittest.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":vector",
    "@gtest//:gtest",
    "@gtest//:gtest_main",
  ],
)
