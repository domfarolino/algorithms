load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

cc_library(
  name = "directed_graph",
  srcs = ["directed_graph.cc"],
  hdrs = ["directed_graph.h"],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "main_unittest",
  srcs = ["main_unittest.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":directed_graph",
    "@gtest//:gtest",
    "@gtest//:gtest_main",
  ],
)
