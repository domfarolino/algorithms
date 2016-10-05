/*
  Implementation of quicksort algorithm.

  It works by choosing a midpoint in the array
  and recursively calls itself on each half.

  Time Complexity
  ---------------
  Ω(n log(n))   Best case
  Θ(n log(n))   Average
  O(n^2)        Worst case

*/

#include <fstream>


void quicksort(int array[], int left, int right) {
    int i = left;
    int j = right;
    int temp;
    int pivot = array[(left + right) / 2]; 

    while (i <= j) {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }   
    }   

    if (left < j)
        quicksort(array, left, j); 
    if (i < right)
        quicksort(array, i, right);
}

int main(int argc, char **argv) {
    
    // test setup.
    std::ifstream input_file("test.in");
    std::ofstream output_file("test.out");
    
    int numbers[10];
    
    int n, index = 0;
    while (input_file >> n) {
        numbers[index] = n;
        index++;
    }
    
    quicksort(numbers, 0, 10);

    for (int i = 0; i < 10; i++) {
        output_file << numbers[i] << std::endl;
    }

    return 0;
}
