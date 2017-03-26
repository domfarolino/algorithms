#include <iostream>
#include <vector>
using namespace std;

//slection sorting function
void selection_sort(vector <double> &v)
{
	int i, j, minindex;
	double minval;


    //show your vector before its sorted
	for (j = 0; j < v.size(); j++) {
		printf("%4.2lf ", v[j]);
	}
	cout << endl;

    //selection sort
	for (i = 0; i < v.size()-1; i++) {
		minindex = i;
		minval = v[minindex];
		for (j = i+1; j < v.size(); j++) {
			if (v[j] < v[minindex]) {
				minindex = j;
				minval = v[j];
			}
		}
		v[minindex] = v[i];
		v[i] = minval;
        
        //show vector after every sort
		for (j = 0; j < v.size(); j++) {
			printf("%4.2lf ", v[j]);
		}
		cout << endl;
	}
}

//main gets all the numbers you want sorted and passes it to the function
int main(){
	double anum;
	vector <double> numbers;
	cout << "Enter all numbers you want sorted" << endl;
	cout << "Hit ctrl+d when done" << endl << endl;
	while(cin >> anum){
		numbers.push_back(anum);
	}

	selection_sort(numbers);
}
