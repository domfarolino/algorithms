load("@rules_cc//cc:defs.bzl", "cc_library")

# This library target doesn't actually produce anything. It is only to export
# queue.h to other targets and packages. See
# https://groups.google.com/forum/#!topic/bazel-discuss/x7c8HJ6dke8.
cc_library(
  name = "queue",
  hdrs = ["queue.h"],
  deps = ["//stack:stack"],
  visibility = ["//visibility:public"],
)
