#include <iostream>
#include <string>
#include <vector>

// Source: https://leetcode.com/problems/generate-parentheses/description/

/**
 * Generate Parentheses
 * This is a really cool combinatorics-esque problem. There are a few
 * ways to do this, but I think the below solution is one of the simplest
 * and most efficient. If we were to throw n pairs of parentheses down, disregarding
 * whether they are "valid" or "well-formed" or whatever, a good question to ask is how
 * many possible ways can we do this? Well, we know that we'll have 2n characters to write,
 * since each of the n paris of parens is composed of 2 characters. Now lets dig into the
 * combinatorics side of this. For each of the 2n characters, we can choose to place a "(" or
 * ")". We're saying that any given "(" is indistinguisable from another "(". So we have 2 choices
 * at 2n places, thus giving us 2^(2n) possible ways to spill n pairs of parenthesis. We could generate
 * all of these and simply check to see if each formation is well-formed or not, and add it to some master
 * list of well-formed parentheses strings, but that's pretty tedious. Instead, just thinking the problem
 * through can be really beneficial.
 *
 * If we were to try and generate all "valid" or well-formed pairs of 1 pairs of parentheses, there's really
 * just one way to do that: "()". If we were to try n = 2, we see we have some options after the first character:
 * "(", here we can either:
 *   1.) Put another open paren "("
 *   2.) Put another close paren ")"
 *
 *       "("
 *       / \
 *      /   \
 *   "(("   "()"
 *
 * Given the left child of the tree, we ran out of "open" parens to use, so we should know at this point that we
 * have to use a ")". Given the right child of the tree, we know we can't use a close, because we don't have a
 * matching open, so we simply have to revert back to the n = 1 case, and finish it off with another "()". But the
 * point here is that we can easily see, that at any given "general-case" time, we have two options! The only time
 * we are limited to one option is when we _have_ to use a ")" paren, really because we ran out of opens to use.
 *
 * We can see a similar expansion with n = 3, just a bit larger. It's a nice problem that breaks down into smaller
 * subproblems, lending itself to a nice recursive solution. We just need to keep track, at any given frame, the number
 * of open and closed parens we can use. As long as we maintain the invariant of making only valid moves, we know that when
 * we're _all out_ of parens period, the sequence is exhausted, and balanced, and we can thus save it. In the implementation
 * below, I choose to maintain a list of strings passed by reference through each recursive frame that we add to when we're
 * at our base case (no more parens to use), as well as a string passed by reference through each frame that we push parens
 * to and pop from, so that it follows the sequence our recursion is doing.
 *
 * Complexity analysis:
 * Time complexity: Leetcode is saying that the complexity is O(Cat(n)), where Cat(n) is the nth Catalan number. Alrighty then,
 * that's certainly non-obvious and I'll have to read more about that
 * Space complexity: ^same as above^
 */

void parenCombinationsHelper(int numOpensLeft, int numClosedLeft, std::string& tmp, std::vector<std::string>& vec) {
  // Base case
  if (numOpensLeft == 0 && numClosedLeft == 0) {
    vec.push_back(tmp);
    return;
  }

  if (numOpensLeft < numClosedLeft) {
    // Have to use a ")"
    tmp.append(")");
    parenCombinationsHelper(numOpensLeft, numClosedLeft - 1, tmp, vec);
    tmp.pop_back();
  }

  if (numOpensLeft != 0) {
    tmp.append("(");
    parenCombinationsHelper(numOpensLeft - 1, numClosedLeft, tmp, vec);
    tmp.pop_back();
  }
}

std::vector<std::string> parenCombinations(int n) {
  std::vector<std::string> returnVec;
  std::string tmp;
  parenCombinationsHelper(n, n, tmp, returnVec);

  return returnVec;
}

int main() {
  std::vector<std::string> parens;
  for (int n = 1; n <= 5; n++) {
    std::cout << "Trying with n = " << n << std::endl;
    parens = parenCombinations(n);

    for (int i = 0; i < parens.size(); ++i) {
     std::cout << parens[i] << std::endl;
    }

    std::cout << std::endl;
  }

  return 0;
}
