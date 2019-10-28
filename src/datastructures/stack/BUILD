load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

# This library target doesn't actually produce anything. It is only to export
# stack.h to other targets and packages. See
# https://groups.google.com/forum/#!topic/bazel-discuss/x7c8HJ6dke8.
cc_library(
  name = "stack",
  hdrs = ["stack.h"],
  deps = ["//linked_list:linked_list"]
)

cc_binary(
  name = "main_unittest",
  srcs = ["main_unittest.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":stack",
    "@gtest//:gtest",
    "@gtest//:gtest_main",
  ],
)
