# algorithm\_practice

The purpose of this folder is to hold well-documented solutions to both classic computer science
problems and algorithmic problems appearing on various online judge platforms. A lot of the algorithms
in this folder are great for technical interview practice, and as such should be documented to describe
things that would be relevant in a technical interview such as:

 - Any assumptions the solution makes
 - Alternative solutions and their tradeoffs/drawbacks
 - Performance/complexity analysis and how using slightly different mechanics might affect current performance

# Categorization

The folders appearing here sort the algorithms by the main concept or technique they employ.
For example, consider an algorithmic problem whose description is:

> Rotate function
> Given an array of integers A and let n to be its length.
> Assume Bk to be an array obtained by rotating the array
> A k positions clock-wise, we define a "rotation function"
> F on A as follow: F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1].
> Calculate the maximum value of F(0), F(1), ..., F(n-1).

Since the primary datastructure and concept involved in this algorithm is agility with the Array or Vector ADT,
it will appear in the [`Array_Algorithms`](https://github.com/domfarolino/algorithms/tree/master/src/algorithm_practice/Array_Algorithms)
folder. Inside this folder there is a folder for each problem of this category.

Often a problem may be representative of multiple categories. For example, an algorithm that requires a dynamic programming solution
that utilizes an array clearly represents both the
[`Dynamic_Programming`](https://github.com/domfarolino/algorithms/tree/master/src/algorithm_practice/Dynamic_Programming) and
[`Array_Algorithms`](https://github.com/domfarolino/algorithms/tree/master/src/algorithm_practice/Array_Algorithms) categories. Choosing
the more specific category generally makes the most since, since it likely best describes the problem. If necessary, file an issue to
make a new category.

# Adding a problem to the repository

Once categorized, the folder name for a specific problem should be a camelcase name or short description of
the problem. In this example it's `rotateFunction`, and inside `rotateFunction` there might be as many as the
following files:

 - Source file to be compiled and demonstrate the algorithm. Name doesn't really matter, but the file should contain
   the title of the problem, a description, and a detailed explanation of the solution (see the list in the first section
   of this README)
 - OJ answer file (`ojAns.cpp`) which should be a file consisting of exactly the code that yields the right answer on the
   online judge that hosts the problem. This typically won't compile on anything but the OJ machine but can be used to quickly
   verify that a correct solution is being submitted
 - Optionally a test input file (`test.in`) to feed test cases into the executable (via stdin) produced by compiling the source file
 - Optionally a test output file (`test.out`) that contains a correct solution's output (from stdout) to the test cases in `test.in`
 - Optionally a `README.md` if you choose to put the documentation here instead of in the source file (doesn't matter)
