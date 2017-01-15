// Source: http://www.practice.geeksforgeeks.org/problem-page.php?pid=700071
/* Linked list Node structure
struct Node
{
    char c;
    Node *next;
}; */

int compare(Node *a, Node *b) {
  if (!a || !b) {
    if (a) return 1;
    if (b) return -1;
    else return 0;
  } else {
    if (a->c > b->c) return 1;
    if (a->c < b->c) return -1;
    else return compare(a->next, b->next);
  }
}
