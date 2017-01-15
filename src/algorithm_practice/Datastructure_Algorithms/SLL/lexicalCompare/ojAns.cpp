// Source: http://www.practice.geeksforgeeks.org/problem-page.php?pid=700071
/* Linked list Node structure
struct Node
{
    char c;
    Node *next;
}; */

int compare(Node *a, Node *b) {
  Node *currA = a, *currB = b;

  while (currA && currB) {
    if (currA->c > currB->c) return 1;
    else if (currB->c > currA->c) return -1;
    else {
      currA = currA->next;
      currB = currB->next;
    }
  }

  if (currA) return 1;
  else if (currB) return -1;
  else return 0;
}
