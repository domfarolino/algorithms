load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
  name = "main_unittest",
  srcs = ["main_unittest.cc", "binary_search_tree.h"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    "@gtest//:gtest",
    "@gtest//:gtest_main",
  ],
)
