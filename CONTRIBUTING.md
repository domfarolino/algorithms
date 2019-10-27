# Contributing

If you'd like to contribute to this repository, great! If you have found any
issues or would like to submit a PR follow, the instructions below:

## Submission Guidelines

### Submitting an Issue

If you find a bug in the source code of one of the algorithms or test files you
can help by submitting an issue, or even better you can submit a PR. Issue
format is fairly relaxed just be very descriptive.

### Submitting a Pull Request (PR)

 - Make your changes in a new branch:
```shell
     git checkout -b new-branch-name master
```
 - Try and adhere to the Google Style Guide's formatting section for the
   language you're using
    * *[C++](https://google.github.io/styleguide/cppguide.html#Formatting)*
    * *[Java](https://google.github.io/styleguide/javaguide.html#s4-formatting)*
    * *[Python](https://google.github.io/styleguide/pyguide.html#Python_Style_Rules)*
    * *[JavaScript](https://google.github.io/styleguide/javascriptguide.xml#JavaScript_Style_Rules)*
    * *[etc...](https://github.com/google/styleguide)*

If the formatting doesn't match the guide perfectly, it's fine, just try to consistent.

 - Push your branch to GitHub:
```shell
     git push origin new-branch-name
```
 - Open up a PR on GitHub and that's it!

When adding an algorithm or datastructure to the repository, providing `test.in`
and `test.out` stdin/stdout files demonstrating a procedure's correct output is
a plus! These don't need to be crazy extensive, just enough to demonstrate some
edge cases if necessary. Rigorous testing is not required because most
algorithms in this repository are checked in after passing some online judge's
extensive tests.
