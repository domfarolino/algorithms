/*
This is a implementation of the famous matrix chain multiplication problem.
Problem:Given a sequence of matrices, find the most efficient way to multiply these matrices together.
 The problem is not actually to perform the multiplications, but merely to decide in which order to perform the multiplications.

Any Dynamic Programming algorithm should be made up of two sections:
1>Look for optimal substructure(If the solution can be made up of smaller subproblems)
    In this case,A simple solution is to place parenthesis at all possible places, calculate the cost for each placement and return the minimum value.
    In a chain of matrices of size n, we can place the first set of parenthesis in n-1 ways. 
    For example, if the given chain is of 4 matrices. let the chain be ABCD, then there are 3 way to place first set of parenthesis: A(BCD), (AB)CD and (ABC)D.
    So when we place a set of parenthesis, we divide the problem into subproblems of smaller size. 
    Therefore, the problem has optimal substructure property and can be easily solved using recursion.

**Minimum number of multiplication needed to multiply a chain of size n = Minimum of all n-1 placements (these placements create subproblems of smaller size)
2>Check if we are calculating the same subproblems multiple times if we use recursion
    Thus,we can save time by saving the results and thus compensating time with space.

    **-----------
        
        Time Complexity:-O(n^3)
        Space Complexity:-O(n^2)

    **----------


*/

#include<bits/stdc++.h>

using namespace std;

/*
The matrix chain multiplication fuction,takes as input the array containing the size of matrix and the number of matrices and outputs the
minimum number of scalar multiplications required.

*/
int matrixchain(int a[],int n){
    //Array containing minimum number of scalar multiplications required for corresponding p[i][i](Matrix of size ixi)
    int p[n+1][n+1];
    //Set the 2-D array to zeroes
    for(int i =0;i<n+1;i++){
        p[i][i]=0;
    }
    int poptimal;
    for(int L=2;L<=n;L++){
        for(int i=1;i<=n-L+1;i++){
            poptimal=999999;
                for(int j=i;j<i+L-1;j++){
                    /*
                    Each matrix of size i x (i+L-1) can be broken into two matrices (i x j) and (j+1 x (i+L-1))
                    We vary j from i to i+L-1 to find out which one gives the minimum scalar multiplication by the formula given below:
                    */
                    if(poptimal>p[i][j]+p[j+1][i+L-1]+a[i-1]*a[j]*a[i+L-1]){
                        poptimal=p[i][j]+p[j+1][i+L-1]+a[i-1]*a[j]*a[i+L-1];
                    }
                    }
                    p[i][i+L-1]=poptimal;

            }

        }
        return p[1][n];

    }

int main(){
    int n;

    cout<<"Enter the number of matrices:";
    cin>>n;
    int a[n+1];


    //Size of ith matrix is stored in a[i-1]xa[i] 
    cout<<endl<<"Enter the size of matrices:";
    for(int i=0;i<n+1;i++){
        cin>>a[i];
        }



    cout<<matrixchain(a,n)<<endl;


}
