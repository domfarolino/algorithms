#=======================================================================
#  Statement:
#  Given a disordered list of integers (or any other items),
#  rearrange the integers in natural order.
#
#  Sample Input: [8,5,3,1,9,6,0,7,4,2,5]
#
#  Sample Output: [0,1,2,3,4,5,5,6,7,8,9]
#
#  Time Complexity of Solution:
#  Best = Average = Worst = O(nlog(n)).
#
#  Approach:
#   Merge sort is a divide and conquer algorithm. In the divide and
#   conquer paradigm, a problem is broken into pieces where each piece
#   still retains all the properties of the larger problem -- except
#   its size. To solve the original problem, each piece is solved
#   individually; then the pieces are merged back together.
#
#   For illustration, imagine needing to sort an array of 200 elements
#   using selection sort. Since selection sort takes O(n^2), it would
#   take about 40,000 time units to sort the array. Now imagine
#   splitting the array into ten equal pieces and sorting each piece
#   individually still using selection sort. Now it would take 400
#   time units to sort each piece; for a grand total of 10400 = 4000.
#   Once each piece is sorted, merging them back together would take
#   about 200 time units; for a grand total of 200+4000 = 4,200.
#   Clearly 4,200 is an impressive improvement over 40,000. Now
#   imagine greater. Imagine splitting the original array into
#   groups of two and then sorting them. In the end, it would take about
#   1,000 time units to sort the array. That's how merge sort works.
#
#  NOTE to the Python experts:
#     While it might seem more "Pythonic" to take such approach as
#
#         mid = len(aList) / 2
#         left = mergesort(aList[:mid])
#         right = mergesort(aList[mid:])
#
#     That approach take too much memory for creating sublists.
#======================================================================= 
def mergesort( aList ):
  _mergesort( aList, 0, len( aList ) - 1 )
 
 
def _mergesort( aList, first, last ):
  # break problem into smaller structurally identical pieces
  mid = ( first + last ) / 2
  if first < last:
    _mergesort( aList, first, mid )
    _mergesort( aList, mid + 1, last )
 
  # merge solved pieces to get solution to original problem
  a, f, l = 0, first, mid + 1
  tmp = [None] * ( last - first + 1 )
 
  while f <= mid and l <= last:
    if aList[f] < aList[l] :
      tmp[a] = aList[f]
      f += 1
    else:
      tmp[a] = aList[l]
      l += 1
    a += 1
 
  if f <= mid :
    tmp[a:] = aList[f:mid + 1]
 
  if l <= last:
    tmp[a:] = aList[l:last + 1]
 
  a = 0
  while first <= last:
    aList[first] = tmp[a]
    first += 1
    a += 1