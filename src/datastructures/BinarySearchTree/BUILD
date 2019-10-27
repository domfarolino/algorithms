load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

#cc_binary(
#  name = "main",
#  srcs = ["main.cc",],
#  deps = [],
#)

cc_binary(
  name = "main_unittest",
  srcs = ["main_unittest.cc", "BinarySearchTree.h"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    "@gtest//:gtest",
    "@gtest//:gtest_main",
    #":main",
  ],
)
